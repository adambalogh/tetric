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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}
