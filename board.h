#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>

namespace tetris {

typedef enum { LEFT, RIGHT, DOWN } Direction;
class Board {
 public:
  const int height = 12;
  const int width = 8;

 private:
  // A Figure with it's position on the Board
  struct BoardFigure {
    Figure figure;
    int top_left_row;
    int top_left_column;
    int rotation = 0;
    int index;

    BoardFigure(Figure f, int top_left_row, int top_left_column) {
      this->figure = f;
      this->top_left_row = top_left_row;
      this->top_left_column = top_left_column;
    }

    Rotate() {
      rotation = (rotation + 1) % 4;
      figure = RotatedFigures[rotation];
    }

    int height() const { return figure.size(); }
    int width() const { return figure[0].size(); }
  };

 public:
  Board() {
    std::srand(std::time(0));
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        cells_[i][j] = false;
      }
    }
  }

  bool CallBack();
  bool Move(Direction d);

  CellType At(int row, int column) const {
    std::lock_guard<std::mutex> lock(mu_);
    return cells_[row][column];
  }

 private:
  // Returns true if we can move the given figure to the given direction
  bool MoveIfPossible(BoardFigure& figure, Direction d);
  // Returns treu if we can move the given figure down
  bool MoveDownIfPossible(BoardFigure& figure) {
    return MoveIfPossible(figure, DOWN);
  }

  bool CanPlace(const Figure& figure, int row, int column) const;
  bool CanPlace(const BoardFigure& figure, int row, int column) const {
    return CanPlace(figure.figure, row, column);
  }
  bool CanPlace(const BoardFigure& figure) const {
    return CanPlace(figure.figure, figure.top_left_row, figure.top_left_column);
  }

  void AddFigure(const BoardFigure& figure);

  void AddToCells(const BoardFigure& figure);
  void RemoveFromCells(const BoardFigure& figure);

  void SetCells(const BoardFigure& figure, CellType value);

  Figure GetRandomFigure() {
    int index = std::rand() % FIGURES.size();
    return FIGURES[index];
  }

  // Guard public methods
  mutable std::mutex mu_;

  CellType cells_[12][8];
  std::vector<BoardFigure> figures_;
};
}
