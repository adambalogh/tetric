#include "figures.h"

#include <map>
#include <ctime>

namespace tetris {

FigureManager::FigureManager() {
  std::srand(std::time(0));

  std::map<FigureType, FigureShape> up_shapes{
      {I, {{1, 1, 1, 1}}},
      {L, {{1, 1, 1}, {1, 0, 0}}},
      {SQUARE, {{1, 1}, {1, 1}}},
      {T, {{1, 1, 1}, {0, 1, 0}}},
      {SKEW_RIGHT, {{0, 1, 1}, {1, 1, 0}}},
      {SKEW_LEFT, {{1, 1, 0}, {0, 1, 1}}},
  };

  std::map<FigureType, FigureShape> rot1;
  for (auto& f : up_shapes) {
    rot1[f.first] = Rotate(f.second);
  }
  std::map<FigureType, FigureShape> rot2;
  for (auto& f : rot1) {
    rot2[f.first] = Rotate(f.second);
  }
  std::map<FigureType, FigureShape> rot3;
  for (auto& f : rot2) {
    rot3[f.first] = Rotate(f.second);
  }
  shapes_ = std::vector<std::map<FigureType, FigureShape>>{up_shapes, rot1,
                                                           rot2, rot3};
}

FigureShape FigureManager::Rotate(const FigureShape& shape) {
  FigureShape rotated(shape[0].size(), std::vector<CellType>(shape.size()));
  for (int i = 0; i < shape.size(); ++i) {
    for (int j = 0; j < shape[0].size(); ++j) {
      rotated[j][i] = shape[shape.size() - i - 1][j];
    }
  }
  return shape;
}
}
