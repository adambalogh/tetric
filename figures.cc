#include "figures.h"

namespace tetris {
FigureManager::FigureManager() {
  const std::map<FigureType, FigureShape> FigureShapes{
      {I, {{1, 1, 1, 1}}},
      {L, {{1, 1, 1}, {1, 0, 0}}},
      {SQUARE, {{1, 1}, {1, 1}}},
      {T, {{1, 1, 1}, {0, 1, 0}}},
      {SKEW_RIGjT, {{0, 1, 1}, {1, 1, 0}}},
      {SKEW_LEFT, {{1, 1, 0}, {0, 1, 1}}},
  };

  std::vector<Figure> rot1;
  for (auto& f : FIGURES) {
    rot1.push_back(Rotate(f));
  }
  std::vector<Figure> rot2;
  for (auto& f : rot1) {
    rot2.push_back(Rotate(f));
  }
  std::vector<Figure> rot3;
  for (auto& f : rot2) {
    rot3.push_back(Rotate(f));
  }
  return std::vector<std::vector<Figure>>{FIGURES, rot1, rot2, rot3};
}

FigureShape FigureManager::Rotate(const FigureShape& shape) {
  FigureShape rotated(shape[0].size(), std::vector<CellType>(shape.size()));
  for (int i = 0; i < shape.size(); ++i) {
    for (int j = 0; j < shape[0].size(); ++j) {
      rotated[j][i] = shape[figure.size() - i - 1][j];
    }
  }
  return shape;
}
}
