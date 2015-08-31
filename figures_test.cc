#include <gtest/gtest.h>
#include <vector>

#include "figures.h"

using namespace tetris;

TEST(FigureManager, MakeFigureUpOrientation) {
  auto fm = FigureManager();
  auto figure = fm.MakeFigure(I, 0);

  ASSERT_EQ(I, figure.type);
  ASSERT_EQ(0, figure.orientation);
  auto i_shape = FigureShape{{1, 1, 1, 1}};
  ASSERT_EQ(i_shape, figure.shape);
}

TEST(FigureManager, MakeFigureRotatedOrientation) {
  auto fm = FigureManager();
  auto figure = fm.MakeFigure(I, 1);

  ASSERT_EQ(I, figure.type);
  ASSERT_EQ(1, figure.orientation);
  auto i_shape = FigureShape{{1}, {1}, {1}, {1}};
  ASSERT_EQ(i_shape, figure.shape);
}

TEST(FigureManager, Rotate) {
  auto fm = FigureManager();
  auto figure = fm.MakeFigure(I, 0);
  auto rotated = fm.GetRotated(figure);

  ASSERT_EQ(I, rotated.type);
  ASSERT_EQ(1, rotated.orientation);
  auto i_shape = FigureShape{{1}, {1}, {1}, {1}};
  ASSERT_EQ(i_shape, rotated.shape);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}
