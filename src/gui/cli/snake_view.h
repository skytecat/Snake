#ifndef _BRICK_GAME_SNAKE_SNAKE_VIEW_H_
#define _BRICK_GAME_SNAKE_SNAKE_VIEW_H_

#include "../../brick_game/snake/snake_controller.h"

namespace s21 {
class SnakeController;
class SnakeView {
  SnakeController *controller;

 public:
  SnakeView(SnakeController *c);
  void GameLoop();
  void Draw();
  int GetInput();
  void PrintEndWindow();
  ~SnakeView();

 private:
  WINDOW *window;
  WINDOW *param_window;

  void PrintLossWindow();
  void PrintWinWindow();

  void PrintSnake();

  void PrintApple();

  void PrintParams();

  void Input();
  void ReadRecord();
  void NewRecord();
};
}  // namespace s21

#endif
