#include "../brick_game/snake/snake_model.h"
#include "gtest/gtest.h"
#include "iostream"

TEST(Shift, Shift1) {
  s21::SnakeModel model;
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().first, 0);
}

TEST(Shift, Shift2) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.ChangeDirection(DOWN);
  model.SetState(SHIFTING);
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().first, 1);
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().first, 2);
}

TEST(Shift, Shift3) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.ChangeDirection(DOWN);
  model.SetState(SHIFTING);
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().second, 3);
  model.ChangeDirection(LEFT);
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().second, 2);
}

TEST(Shift, Shift4) {
  s21::SnakeModel model;
  model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().second, 3);
  model.Shift();
  EXPECT_EQ(model.GetSnake().front().second, 4);
}

TEST(Loss, Loss1) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.SetState(SHIFTING);
  for (int i = 0; i < 9; ++i) model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().second, 9);
  EXPECT_EQ(model.GetState(), LOSS);
}

TEST(Loss, Loss2) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.SetState(SHIFTING);
  model.ChangeDirection(DOWN);
  for (int i = 0; i < 20; ++i) model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().first, 19);
  EXPECT_EQ(model.GetState(), LOSS);
}

TEST(Loss, Loss3) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.SetState(SHIFTING);
  model.ChangeDirection(DOWN);
  model.StatesHandle();
  model.ChangeDirection(LEFT);
  EXPECT_EQ(model.GetSnake().front().second, 3);
  for (int i = 0; i < 4; ++i) model.StatesHandle();
  EXPECT_EQ(model.GetSnake().front().second, 0);
  EXPECT_EQ(model.GetState(), LOSS);
}

TEST(Loss, Loss4) {
  s21::SnakeModel model;
  model.StatesHandle();
  model.SetState(SHIFTING);
  model.ChangeDirection(DOWN);
  model.StatesHandle();
  model.ChangeDirection(RIGHT);
  model.StatesHandle();
  model.ChangeDirection(UP);
  model.Shift();
  EXPECT_EQ(model.GetSnake().front().first, 0);
  model.StatesHandle();
  EXPECT_EQ(model.GetState(), LOSS);
}

TEST(Start, Start1) {
  s21::SnakeModel model;
  EXPECT_EQ(model.GetDirection(), RIGHT);
  EXPECT_EQ(model.GetScore(), 0);
  EXPECT_EQ(model.GetState(), START);
  EXPECT_EQ(model.GetLevel(), 1);
  EXPECT_EQ(model.GetSpeed(), 350);
}

TEST(Start, Start2) {
  s21::SnakeModel model;
  model.StatesHandle();
  EXPECT_EQ(model.GetSnakeSize(), 4);
  EXPECT_EQ(model.GetSnake().front().first, 0);
  EXPECT_EQ(model.GetSnake().front().second, 3);
  EXPECT_EQ(model.GetState(), APPLE_SPAWN);
  EXPECT_EQ(model.GetFood().first, 0);
  EXPECT_EQ(model.GetFood().second, 0);
}

TEST(GameOver, GameOver1) {
  s21::SnakeModel model;
  EXPECT_EQ(model.IsGameOver(), false);
  model.SetState(LOSS);
  model.StatesHandle();
  EXPECT_EQ(model.IsGameOver(), true);
}

TEST(GameOver, GameOver2) {
  s21::SnakeModel model;
  EXPECT_EQ(model.IsGameOver(), false);
  model.SetState(WIN);
  model.StatesHandle();
  EXPECT_EQ(model.IsGameOver(), true);
}
TEST(Record, Record1) {
  s21::SnakeModel model;
  model.SetRecord(100);
  EXPECT_EQ(model.GetRecord(), 100);
}

TEST(Apple, Apple1) {
  s21::SnakeModel model;
  model.SetState(APPLE_SPAWN);
  model.StatesHandle();
  EXPECT_LE(model.GetFood().first, 19);
  EXPECT_LE(model.GetFood().second, 9);
}

TEST(Apple, Apple2) {
  s21::SnakeModel model;
  model.SetState(EATING);
  model.StatesHandle();
  EXPECT_LE(model.GetSnakeSize(), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
