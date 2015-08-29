#include <vector>
#include <iostream>

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

  const int width = 10;
  const int height = 30;

  bool CallBack() {
    if (moving_figure_ == nullptr) {
      BoardFigure f(GetRandomFigure(), 0, 0);
      if (CanPlaceAt(f.figure, 0, 0)) {
        Add(f);
      } else {
        return false;
      }
    }

    return false;
  }

  bool At(int row, int column) const { return cells_[row][column]; }

 private:
  bool CanPlaceAt(const Figure& figure, int row, int column) {
    for (int f_row = 0; f_row < figure.size(); ++f_row) {
      for (int f_column = 0; f_column < figure[0].size(); ++f_column) {
        if (row + f_row >= height || column + f_column >= width) {
          return false;
        }
        if (figure[f_row][f_column] && cells_[row + f_row][column + f_column]) {
          return false;
        }
      }
    }
    return true;
  }

  void Add(const BoardFigure& figure) {
    figures_.push_back(figure);
    for (int i = 0; i < figure.height(); ++i) {
      for (int j = 0; j < figure.width(); ++j) {
        cells_[figure.top_left_row + i][figure.top_left_column + j] =
            figure.figure[i][j];
      }
    }
  }

  Figure GetRandomFigure() {
    int index = std::rand() % FIGURES.size();
    return FIGURES[index];
  }

  bool cells_[30][10];
  BoardFigure* moving_figure_ = nullptr;
  std::vector<BoardFigure> figures_;
};

void DrawBoard(const Board* board) {
  for (int j = 0; j < board->width; ++j) {
    std::cout << "---";
  }
  std::cout << std::endl;
  for (int i = 0; i < board->height; ++i) {
    for (int j = 0; j < board->width; ++j) {
      if (board->At(i, j)) {
        std::cout << " X ";
      } else {
        std::cout << "   ";
      }
    }
    std::cout << std::endl;
  }
}

int main() {
  Board b;
  DrawBoard(&b);
  b.CallBack();
  DrawBoard(&b);
  b.CallBack();
  DrawBoard(&b);
}
