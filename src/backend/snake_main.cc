#include "../../gui/cli/snake_view.h"

int main() {
  s21::SnakeModel model;
  s21::SnakeController controller(&model);
  s21::SnakeView view(&controller);
  view.GameLoop();
  return 0;
}