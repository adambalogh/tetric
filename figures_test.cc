#include <gtest/gtest.h>
#include <vector>

#include "figures.h"

using namespace tetris;

TEST(FigureManager, MakeFigureUpOrientation) {
  FigureManager fm;
  auto figure = fm.MakeFigure(L, 0);

  FigureShape shape{{1, 1, 1}, {1, 0, 0}};

  ASSERT_EQ(L, figure.type);
  ASSERT_EQ(0, figure.orientation);
  ASSERT_EQ(shape, figure.shape);
}

TEST(FigureManager, OneRotate) {
  FigureManager fm;
  auto figure = fm.MakeFigure(L, 0);
  auto rotated = fm.GetRotated(figure);

  FigureShape shape{{1, 1}, {0, 1}, {0, 1}};

  ASSERT_EQ(L, rotated.type);
  ASSERT_EQ(1, rotated.orientation);
  ASSERT_EQ(shape, rotated.shape);
}

TEST(FigureManager, TwoRotate) {
  FigureManager fm;
  auto figure = fm.MakeFigure(L, 0);
  auto rotated = fm.GetRotated(fm.GetRotated(figure));

  FigureShape shape{{0, 0, 1}, {1, 1, 1}};

  ASSERT_EQ(L, rotated.type);
  ASSERT_EQ(2, rotated.orientation);
  ASSERT_EQ(shape, rotated.shape);
}

TEST(FigureManager, ThreeRotate) {
  FigureManager fm;
  auto figure = fm.MakeFigure(L, 0);
  auto rotated = fm.GetRotated(fm.GetRotated(fm.GetRotated(figure)));

  FigureShape shape{{1, 0}, {1, 0}, {1, 1}};

  ASSERT_EQ(L, rotated.type);
  ASSERT_EQ(3, rotated.orientation);
  ASSERT_EQ(shape, rotated.shape);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}
