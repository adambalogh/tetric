#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "figures.h"

namespace tetris {

// Directions we can move figures in
typedef enum { LEFT, RIGHT, DOWN } Direction;

class RandomNumberGenerator {
 public:
  RandomNumberGenerator() { std::srand(std::time(0)); }

  // Returns a random number in the range [min,max)
  virtual int Get(int min, int max) {
    return min + (std::rand() % (max - min));
  }
};

// TODO add tests
class Board {
 public:
  static const int height = 12;
  static const int width = 8;

 private:
  struct BoardFigure : Figure {
    int top_left_row;
    int top_left_column;

    BoardFigure(FigureType type, int orientation, int top_left_row,
                int top_left_column)
        : Figure(type, orientation),
          top_left_row(top_left_row),
          top_left_column(top_left_column) {}
  };

 public:
  Board(std::unique_ptr<RandomNumberGenerator> r =
            std::make_unique<RandomNumberGenerator>())
      : random_num_gen_(std::move(r)) {
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        cells_[i][j] = false;
      }
    }
  }

  // Should be called periodically to move the current figure down
  bool CallBack();

  // Should be called when player wants to move the current figure
  // If there is no current figure, nothing will happen.
  bool Move(Direction d);

  // Should be called when player wants to rotate the current figure
  // If there is no current figure, nothing will happen.
  bool Rotate();

  // Returns whether there is a figure at the given location
  CellType At(int row, int column) const { return cells_[row][column]; }

 private:
  void ClearFullRows();

  // Returns true if we can move the given figure to the given direction
  bool MoveIfPossible(BoardFigure& figure, Direction d);
  // Returns treu if we can move the given figure down
  bool MoveDownIfPossible(BoardFigure& figure) {
    return MoveIfPossible(figure, DOWN);
  }

  bool CanPlace(const FigureShape& figure, int row, int column) const;
  bool CanPlace(const BoardFigure& figure, int row, int column) const {
    return CanPlace(figure.shape, row, column);
  }
  bool CanPlace(const BoardFigure& figure) const {
    return CanPlace(figure.shape, figure.top_left_row, figure.top_left_column);
  }

  void AddFigure(const BoardFigure& figure);

  void AddToCells(const BoardFigure& figure);
  void RemoveFromCells(const BoardFigure& figure);
  void SetCells(const BoardFigure& figure, CellType value);

  std::unique_ptr<RandomNumberGenerator> random_num_gen_;
  CellType cells_[height][width];
  std::vector<BoardFigure> figures_;
};
}

#endif
