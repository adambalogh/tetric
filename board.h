#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>

class Board {
 public:
  typedef bool CellType;
  // Tetris game figures, made of blocks
  typedef std::vector<std::vector<CellType>> Figure;
  // Directions Figures can be moved in
  typedef enum { LEFT, RIGHT, DOWN } Direction;

  const int height = 12;
  const int width = 8;

 private:
  // All the figures that are in Tetris
  const std::vector<Figure> FIGURES{
      {{1, 1, 1, 1}},
      {{1, 1, 1}, {1, 0, 0}},
      {{1, 1}, {1, 1}},
      {{1, 1, 1}, {0, 1, 0}},
      {{0, 1, 1}, {1, 1, 0}},
      {{1, 1, 0}, {0, 1, 1}},
  };

  // A Figure with it's position on the Board
  struct BoardFigure {
    Figure figure;
    int top_left_row;
    int top_left_column;

    BoardFigure(Figure f, int top_left_row, int top_left_column) {
      this->figure = f;
      this->top_left_row = top_left_row;
      this->top_left_column = top_left_column;
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
  mutable std::mutex mu_;

  // Returns true if we can move the given figure to the given direction
  bool MoveIfPossible(BoardFigure& figure, Direction d);
  // Returns treu if we can move the given figure down
  bool MoveDownIfPossible(BoardFigure& figure) {
    return MoveIfPossible(figure, DOWN);
  }

  bool CanPlace(const Figure& figure, int row, int column);
  bool CanPlace(const BoardFigure& figure, int row, int column) {
    return CanPlace(figure.figure, row, column);
  }
  bool CanPlace(const BoardFigure& figure) {
    return CanPlace(figure.figure, figure.top_left_row, figure.top_left_column);
  }

  void Add(const BoardFigure& figure);

  void AddToCells(const BoardFigure& figure);
  void RemoveFromCells(const BoardFigure& figure);

  void SetCells(const BoardFigure& figure, CellType value);

  Figure GetRandomFigure() {
    int index = std::rand() % FIGURES.size();
    return FIGURES[index];
  }

  CellType cells_[12][8];
  std::vector<BoardFigure> figures_;
};
