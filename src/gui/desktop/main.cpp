
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QPaintEvent>
#include <QPainter>
#include <QTextStream>
#include <QTimer>
#include <QWidget>

#include "../../backend/snake_controller.h"
#include "mainwindow.h"

namespace s21 {
class Snake : public QWidget {
 private:
  s21::SnakeController *controller;
  QTimer *timer;
  bool gameOver = false;

 public:
  Snake(SnakeController *c, QWidget *parent = nullptr)
      : QWidget(parent), controller(c) {
    setFixedSize(512, 612);
    setWindowTitle("Snake Game");
    controller->SetRecord(ReadRecord(":/snake_record.txt"));
    timer = new QTimer;
    timer->setInterval(controller->GetSpeed() - 50);
    connect(timer, &QTimer::timeout, this, &Snake::UpdateGame);
    timer->start();
  }

 protected:
  void UpdateGame() {
    controller->StatesHandle();
    if (controller->GetState() == LOSS) {
      gameOver = true;
      timer->stop();
    } else if (controller->GetScore() > controller->GetRecord()) {
      controller->SetRecord(controller->GetScore());
      WriteRecord(":/snake_record.txt");
    }
    update();
  }

  int ReadRecord(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Cannot open file for reading";
      return -1;
    }

    QTextStream in(&file);
    int number;
    in >> number;

    if (in.status() == QTextStream::ReadPastEnd) {
      qDebug() << "File does not contain a number";
    }

    file.close();
    return number;
  }
  void WriteRecord(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Cannot open file for writing";
      return;
    }

    QTextStream out(&file);
    out << controller->GetScore();
    file.close();
  }

  void EndWindowPrint() {
    QPainter painter(this);
    QFont font = painter.font();
    font.setPointSize(30);
    painter.setFont(font);
    painter.setPen(Qt::red);
    if (controller->GetState() == WIN)
      painter.drawText(rect(), Qt::AlignCenter, "YOU WIN");
    else
      painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
  }
  void ApplePrint() {
    QPen pen;
    QPainter painter(this);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(Qt::red);
    int x = controller->GetFood().second;
    int y = controller->GetFood().first;
    painter.drawRect(30 * x + 7, 30 * y + 7, 30, 30);
  }
  void BordersPrint() {
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawRect(5, 5, 302, 602);
  }
  void SnakePrint() {
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(Qt::green);

    for (int i = 0; i < controller->GetSnakeSize(); ++i) {
      painter.drawRect(30 * controller->GetSnake()[i].second + 7,
                       30 * controller->GetSnake()[i].first + 7, 30, 30);
    }
  }
  void ParamsPrint() {
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawRect(307, 5, 202, 200);

    QFont font = painter.font();
    font.setPointSize(20);
    painter.setFont(font);
    painter.drawText(350, 50, "SCORE:");
    painter.drawText(450, 50, QString::number(controller->GetScore()));
    painter.drawText(350, 90, "LEVEL:");
    painter.drawText(450, 90, QString::number(controller->GetLevel()));
    painter.drawText(350, 130, "RECORD:");
    painter.drawText(450, 130, QString::number(controller->GetRecord()));
  }
  void keyPressEvent(QKeyEvent *event) override {
    int key = event->key();
    switch (key) {
      case Qt::Key_Left:
        if (controller->GetDirection() != RIGHT)
          controller->ChangeDirection(LEFT);
        break;
      case Qt::Key_Right:
        if (controller->GetDirection() != LEFT)
          controller->ChangeDirection(RIGHT);
        break;
      case Qt::Key_Up:
        if (controller->GetDirection() != DOWN) controller->ChangeDirection(UP);
        break;
      case Qt::Key_Down:
        if (controller->GetDirection() != UP) controller->ChangeDirection(DOWN);
        break;
      case Qt::Key_Q:
        controller->SetState(LOSS);
        break;
      case ' ':
        controller->Shift();
    }
  }
  void paintEvent(QPaintEvent *) override {
    if (gameOver)
      EndWindowPrint();
    else {
      BordersPrint();
      ApplePrint();
      SnakePrint();
      ParamsPrint();
    }
  }
};
}  // namespace s21

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::SnakeModel model;
  s21::SnakeController controller(&model);
  s21::Snake widget(&controller);
  widget.show();
  return app.exec();
}
