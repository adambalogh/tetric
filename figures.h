#include <cstdlib>
#include <map>
#include <vector>

namespace tetris {

typedef bool CellType;
typedef std::vector<std::vector<CellType>> FigureShape;
typedef enum { I, SQUARE, L, T, SKEW_RIGHT, SKEW_LEFT, NUM_TYPES } FigureType;

struct Figure {
  const FigureType type;
  const FigureShape& shape;
  int orientation;

  Figure(FigureType type, FigureShape& shape, int orientation)
      : type(type), shape(shape), orientation(orientation) {}

  int Height() const { return shape.size(); }
  int Width() const { return shape[0].size(); }
};

class FigureManager {
 public:
  FigureManager();

  inline Figure GetRandomUpFigure() {
    auto type = static_cast<FigureType>(std::rand() % NUM_TYPES);
    return Figure{type, shapes_[0][type], 0};
  }

  Figure GetRotated(const Figure& f) {
    int new_orientation = (f.orientation + 1) % 4;
    return Figure{f.type, shapes_[new_orientation][f.type], new_orientation};
  }

  // private:
  FigureShape Rotate(const FigureShape& shape);

  std::vector<std::map<FigureType, FigureShape>> shapes_;
};
}
