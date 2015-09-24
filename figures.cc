#include <map>

#include "figures.h"

namespace tetris {

const auto ShapeRepository::shapes_ = ShapeRepository::MakeShapes();

std::vector<std::map<FigureType, FigureShape>> ShapeRepository::MakeShapes() {
  const std::map<FigureType, FigureShape> up_shapes{
      {I, {{1, 1, 1, 1}}},
      {L, {{1, 1, 1}, {1, 0, 0}}},
      {SQUARE, {{1, 1}, {1, 1}}},
      {T, {{1, 1, 1}, {0, 1, 0}}},
      {SKEW_RIGHT, {{0, 1, 1}, {1, 1, 0}}},
      {SKEW_LEFT, {{1, 1, 0}, {0, 1, 1}}},
  };

  std::map<FigureType, FigureShape> rot1;
  for (const auto& f : up_shapes) {
    rot1[f.first] = Rotate(f.second);
  }
  std::map<FigureType, FigureShape> rot2;
  for (const auto& f : rot1) {
    rot2[f.first] = Rotate(f.second);
  }
  std::map<FigureType, FigureShape> rot3;
  for (const auto& f : rot2) {
    rot3[f.first] = Rotate(f.second);
  }
  return std::vector<std::map<FigureType, FigureShape>>{up_shapes, rot1, rot2,
                                                        rot3};
}

FigureShape ShapeRepository::Rotate(const FigureShape& shape) {
  FigureShape rotated(shape[0].size(), std::vector<CellType>(shape.size()));
  for (int i = 0; i < rotated.size(); ++i) {
    for (int j = 0; j < rotated[0].size(); ++j) {
      rotated[i][j] = shape[shape.size() - j - 1][i];
    }
  }
  return rotated;
}
}
