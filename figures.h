#include <vector>

namespace tetris {

typedef bool CellType;
typedef std::vector<std::vector<CellType>> FigureShape;
typedef enum { I, SQUARE, L, T, SKEW_RIGHT, SKEW_LEFT } FigureType;

struct Figure {
  const FigureType type;
  const FigureShape shape;
  const int orientation;

  Figure(FigureType type, FigureShape shape, int orientation)
      : type(type), shape(shape), orientation(orientation) {}
};

class FigureManager {
 public:
  GetRotated(const Figure& f) {
    int new_orientation = f.orientation + 1 % 4;
    return Figure{f.type, FigureShape[new_orientation][f.type],
                  new_orientation};
  }

 private:
  std::vector<std::vector<FigureShape>> shapes_;
}
}
