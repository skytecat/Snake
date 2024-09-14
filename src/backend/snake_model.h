#ifndef _BRICK_GAME_SNAKE_SNAKE_MODEL_H_
#define _BRICK_GAME_SNAKE_SNAKE_MODEL_H_

#include "snake.h"

typedef enum { LEFT = 0, RIGHT, UP, DOWN } Direction;
typedef enum { START = 0, APPLE_SPAWN, SHIFTING, EATING, WIN, LOSS } GameStates;

namespace s21 {
class SnakeModel {
 public:
  GameStates state_;
  Direction dir_;
  SnakeModel() : state_(START), dir_(RIGHT), score_(0) {}
  GameStates GetState() const;

  void Shift();

  void StatesHandle();

  void SetState(GameStates newState);

  void ChangeDirection(Direction newDir);

  Direction GetDirection();

  int GetSpeed();

  int GetLevel();
  int GetSnakeSize();
  int GetScore();
  std::pair<int, int> GetFood();
  std::deque<std::pair<int, int>> GetSnake();
  int GetRecord();
  void SetRecord(int newRecord);

  bool IsGameOver();

 private:
  int score_;
  int speed = 350;
  int level_ = 1, record_ = 0, width_ = WIDTH, height_ = HEIGHT;
  bool gameOver = false;
  std::deque<std::pair<int, int>> snake;
  std::pair<int, int> food{0, 0};

  void End();

  void SpeedChange();

  void AppleSpawn();

  void SnakeSpawn();

  bool IsCrash(std::pair<int, int> head);

  void LevelChange();

  void Eating();

  void AppleCheck();
};
}  // namespace s21

#endif