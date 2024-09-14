#include "snake_controller.h"

namespace s21 {

int SnakeController::GetSpeed() { return model->GetSpeed(); }
int SnakeController::GetScore() { return model->GetScore(); }
int SnakeController::GetRecord() { return model->GetRecord(); }
int SnakeController::GetState() { return model->GetState(); }
void SnakeController::StatesHandle() { model->StatesHandle(); }
void SnakeController::SetRecord(int newRecord) { model->SetRecord(newRecord); }
int SnakeController::GetSnakeSize() { return model->GetSnakeSize(); }
int SnakeController::GetLevel() { return model->GetLevel(); }
void SnakeController::Shift() { model->Shift(); }
void SnakeController::SetState(GameStates newState) {
  model->SetState(newState);
}
Direction SnakeController::GetDirection() { return model->GetDirection(); }
void SnakeController::ChangeDirection(Direction newDirection) {
  model->ChangeDirection(newDirection);
}
std::pair<int, int> SnakeController::GetFood() { return model->GetFood(); }
std::deque<std::pair<int, int>> SnakeController::GetSnake() {
  return model->GetSnake();
}
bool SnakeController::IsGameOver() { return model->IsGameOver(); }

}  // namespace s21
