#include <gtest/gtest.h>
#include <vector>

#include "figures.h"

using namespace tetris;

TEST(Figure, Shapes) {
  Figure zero_rotate{L, 0};
  Figure one_rotate{L, 1};
  Figure two_rotate{L, 2};
  Figure three_rotate{L, 3};

  FigureShape zero_shape{{1, 1, 1}, {1, 0, 0}};
  FigureShape one_shape{{1, 1}, {0, 1}, {0, 1}};
  FigureShape two_shape{{0, 0, 1}, {1, 1, 1}};
  FigureShape three_shape{{1, 0}, {1, 0}, {1, 1}};

  ASSERT_EQ(zero_rotate.shape, zero_shape);
  ASSERT_EQ(one_rotate.shape, one_shape);
  ASSERT_EQ(two_rotate.shape, two_shape);
  ASSERT_EQ(three_rotate.shape, three_shape);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}
