#include <gtest/gtest.h>
#include <vector>

#include "board.h"

using namespace tetris;

std::vector<std::vector<CellType>> MakeEmptyCells() {
  std::vector<std::vector<CellType>> cells(Board::height);
  std::fill(cells.begin(), cells.end(), std::vector<CellType>(Board::width));
  return cells;
}

std::vector<std::vector<CellType>> GetCells(const Board& b) {
  auto cells = MakeEmptyCells();
  for (int i = 0; i < Board::height; i++) {
    for (int j = 0; j < Board::width; j++) {
      cells[i][j] = b.At(i, j);
    }
  }
  return cells;
}

class MockRandomFigureGenerator : public RandomFigureGenerator {
 public:
  MockRandomFigureGenerator(std::vector<FigureType> types) : types_(types) {}
  virtual BoardFigure Get() override {
    return BoardFigure{types_[i++], 0, 0, 0};
  }

 private:
  std::vector<FigureType> types_;
  int i{0};
};

TEST(Board, EmptyInitially) {
  Board b;
  ASSERT_EQ(GetCells(b), MakeEmptyCells());
}

TEST(Board, MoveBeforeCallBack) {
  Board b;
  b.Move(RIGHT);
  ASSERT_EQ(GetCells(b), MakeEmptyCells());
}

TEST(Board, RotateBeforeCallBack) {
  Board b;
  b.Rotate();
  ASSERT_EQ(GetCells(b), MakeEmptyCells());
}

TEST(Board, InitialCallBack) {
  Board b{
      std::make_unique<MockRandomFigureGenerator>(std::vector<FigureType>{L})};
  b.CallBack();
  auto expected = MakeEmptyCells();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}
