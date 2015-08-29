#include <vector>
#include <cstdlib>
#include <ctime>

typedef enum { LEFT, RIGHT, NONE } Direction;

typedef std::vector<std::vector<bool>> Figure;

const std::vector<Figure> FIGURES{
    {{1, 1, 1, 1}},
    {{1, 1, 1}, {1, 0, 0}},
    {{1, 1}, {1, 1}},
    {{1, 1, 1}, {0, 1, 0}},
    {{0, 1, 1}, {1, 1, 0}},
    {{1, 1, 0}, {0, 1, 1}},
};

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

class Board {
 public:
  Board() {
    std::srand(std::time(0));
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        cells_[i][j] = false;
      }
    }
  }

  const int height = 30;
  const int width = 10;

  bool CallBack();

  bool At(int row, int column) const { return cells_[row][column]; }

 private:
  bool CanMoveDown(const BoardFigure& figure);
  void MoveDown(BoardFigure& figure);

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

  Figure GetRandomFigure() {
    int index = std::rand() % FIGURES.size();
    return FIGURES[index];
  }

  bool cells_[30][10];
  bool moving = false;
  std::vector<BoardFigure> figures_;
};
