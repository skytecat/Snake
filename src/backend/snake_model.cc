#include "snake_model.h"

namespace s21 {
void SnakeModel::Shift() {
  std::pair<int, int> head = snake.front();
  switch (dir_) {
    case LEFT:
      head.second--;
      break;
    case RIGHT:
      head.second++;
      break;
    case UP:
      head.first--;
      break;
    case DOWN:
      head.first++;
      break;
  }
  if (!IsCrash(head)) {
    snake.push_front(head);
    AppleCheck();
  }
}

void SnakeModel::StatesHandle() {
  switch (GetState()) {
    case START:
      SnakeSpawn();
      break;
    case APPLE_SPAWN:
      AppleSpawn();
      break;
    case EATING:
      Eating();
      break;
    case SHIFTING:
      Shift();
      break;
    case LOSS:
    case WIN:
      End();
      break;
  }
}

void SnakeModel::SetState(GameStates newState) { state_ = newState; }

void SnakeModel::ChangeDirection(Direction newDir) { dir_ = newDir; }

Direction SnakeModel::GetDirection() { return dir_; }

int SnakeModel::GetRecord() { return record_; }

int SnakeModel::GetSpeed() { return speed; }

int SnakeModel::GetLevel() { return level_; }
int SnakeModel::GetSnakeSize() { return snake.size(); }
int SnakeModel::GetScore() { return score_; }
void SnakeModel::SetRecord(int newRecord) { record_ = newRecord; }
std::pair<int, int> SnakeModel::GetFood() { return food; }
std::deque<std::pair<int, int>> SnakeModel::GetSnake() { return snake; }

void SnakeModel::End() { gameOver = true; }

void SnakeModel::SpeedChange() { speed -= 25; }

void SnakeModel::AppleSpawn() {
  std::pair<int, int> place;
  do {
    place = {rand() % (height_ - 2) + 1, rand() % (width_ - 2) + 1};
  } while (std::count(snake.begin(), snake.end(), place) > 0);
  state_ = SHIFTING;
  food = place;
}

void SnakeModel::SnakeSpawn() {
  for (int i = 3; i >= 0; --i) snake.push_back({0, i});
  state_ = APPLE_SPAWN;
}

bool SnakeModel::IsCrash(std::pair<int, int> head) {
  state_ = SHIFTING;
  bool crash = false;
  if (head.first < 0 || head.first >= height_ || head.second < 0 ||
      head.second >= width_) {
    state_ = LOSS;
  }

  for (size_t i = 1; i < snake.size(); ++i) {
    if (head == snake[i]) {
      state_ = LOSS;
    }
  }
  if (state_ == LOSS) crash = true;
  return crash;
}

void SnakeModel::LevelChange() {
  level_++;
  SpeedChange();
}

void SnakeModel::Eating() {
  score_++;
  state_ = APPLE_SPAWN;
  if (snake.size() == 200) state_ = WIN;
  if (score_ % 5 == 0) LevelChange();
}

void SnakeModel::AppleCheck() {
  if (snake.front() == food) {
    state_ = EATING;
  } else {
    snake.pop_back();
  }
}

bool SnakeModel::IsGameOver() { return gameOver; }

GameStates SnakeModel::GetState() const { return state_; }
}  // namespace s21