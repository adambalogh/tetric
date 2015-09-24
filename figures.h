#ifndef TETRIS_FIGURES_H_
#define TETRIS_FIGURES_H_

#include <map>
#include <vector>

namespace tetris {

typedef bool CellType;
typedef std::vector<std::vector<CellType>> FigureShape;
typedef enum { I, SQUARE, L, T, SKEW_RIGHT, SKEW_LEFT, NUM_TYPES } FigureType;

class ShapeRepository {
 public:
  const FigureShape& GetShape(const FigureType type, int orientation) const {
    return shapes_.at(orientation).at(type);
  }

 private:
  static FigureShape Rotate(const FigureShape& shape);
  static std::vector<std::map<FigureType, FigureShape>> MakeShapes();

  static const std::vector<std::map<FigureType, FigureShape>> shapes_;
};

struct Figure {
  const FigureType type;
  const FigureShape& shape;
  int orientation;

  Figure(FigureType type, int orientation)
      : type(type),
        shape(shape_repository_.GetShape(type, orientation)),
        orientation(orientation) {}

  int Height() const { return shape.size(); }
  int Width() const { return shape[0].size(); }

  ShapeRepository shape_repository_;
};
}
#endif
