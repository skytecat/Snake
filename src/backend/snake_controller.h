#ifndef _SNAKE_CONTROLLER_H_
#define _SNAKE_CONTROLLER_H_

#include "snake_model.h"

namespace s21 {
class SnakeController {
 public:
  SnakeModel *model;
  SnakeController(SnakeModel *m) : model(m) {}
  int GetSpeed();
  int GetScore();
  int GetRecord();
  int GetState();
  void SetRecord(int newRecord);
  void StatesHandle();
  int GetSnakeSize();
  int GetLevel();
  void Shift();
  void SetState(GameStates newState);
  Direction GetDirection();
  void ChangeDirection(Direction newDirection);
  std::pair<int, int> GetFood();
  std::deque<std::pair<int, int>> GetSnake();
  bool IsGameOver();
};
}  // namespace s21

#endif