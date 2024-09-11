#include "snake_view.h"

namespace s21 {
void SnakeView::GameLoop() {
  ReadRecord();
  while (!controller->IsGameOver()) {
    Input();
    Draw();
    controller->StatesHandle();
    if (controller->GetRecord() < controller->GetScore()) NewRecord();
    napms(controller->GetSpeed());
  }
  PrintEndWindow();
}

void SnakeView::NewRecord() {
  controller->SetRecord(controller->GetScore());
  std::fstream file("gui/cli/record.txt");
  if (file.is_open()) {
    file << controller->GetRecord();
    file.close();
  } else {
    throw std::runtime_error("File record.txt opening error");
  }
}
void SnakeView::ReadRecord() {
  std::fstream file("gui/cli/record.txt");
  if (file.is_open()) {
    int rec = 0;
    file >> rec;
    controller->SetRecord(rec);
    file.close();
  } else {
    throw std::runtime_error("File record.txt opening error");
  }
}

SnakeView::SnakeView(SnakeController *c) : controller(c) {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  raw();

  window = newwin(HEIGHT * 2 + 2, WIDTH * 4 + 2, 0, 0);
  param_window = newwin(HEIGHT - 3, WIDTH * 3 + 2, 0, 42);
  keypad(window, TRUE);
  nodelay(window, TRUE);

  srand(time(0));
}
void SnakeView::Draw() {
  wclear(window);
  box(window, 0, 0);
  box(param_window, 0, 0);
  PrintApple();
  PrintSnake();
  PrintParams();
  wrefresh(window);
  wrefresh(param_window);
}
int SnakeView::GetInput() { return wgetch(window); }

void SnakeView::PrintEndWindow() {
  if (controller->GetState() == LOSS)
    PrintLossWindow();
  else
    PrintWinWindow();
}
SnakeView::~SnakeView() {
  delwin(window);
  delwin(param_window);
  endwin();
}

void SnakeView::PrintLossWindow() {
  wclear(window);
  box(window, 0, 0);
  mvwprintw(window, 15, 18, "G A M E");
  mvwprintw(window, 19, 18, "O V E R");
  wrefresh(window);
  napms(2000);
}

void SnakeView::PrintWinWindow() {
  wclear(window);
  box(window, 0, 0);
  mvwprintw(window, 5, 5, "You win");
  wrefresh(window);
  napms(2000);
}

void SnakeView::PrintSnake() {
  for (int i = 0; i < controller->GetSnakeSize(); ++i) {
    for (int x = 0; x < 2; ++x)
      for (int j = 0; j < 4; ++j)
        mvwaddch(window, controller->GetSnake()[i].first * 2 + 1 + x,
                 controller->GetSnake()[i].second * 4 + 1 + j, ' ' | A_REVERSE);
  }
}

void SnakeView::PrintApple() {
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      mvwaddch(window, controller->GetFood().first * 2 + 1 + i,
               controller->GetFood().second * 4 + 1 + j, ' ' | A_REVERSE);
}

void SnakeView::PrintParams() {
  mvwprintw(param_window, 4, 10, "S C O R E : %d", controller->GetScore());
  mvwprintw(param_window, 7, 10, "L E V E L : %d", controller->GetLevel());
  mvwprintw(param_window, 10, 10, "R E C O R D : %d", controller->GetRecord());
}
void SnakeView::Input() {
  int ch = GetInput();
  switch (ch) {
    case KEY_LEFT:
      if (controller->GetDirection() != RIGHT)
        controller->ChangeDirection(LEFT);
      break;
    case KEY_RIGHT:
      if (controller->GetDirection() != LEFT)
        controller->ChangeDirection(RIGHT);
      break;
    case KEY_UP:
      if (controller->GetDirection() != DOWN) controller->ChangeDirection(UP);
      break;
    case KEY_DOWN:
      if (controller->GetDirection() != UP) controller->ChangeDirection(DOWN);
      break;
    case 'q':
      controller->SetState(LOSS);
      break;
    case ' ':
      controller->Shift();
  }
}
}  // namespace s21
