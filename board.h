#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "figures.h"

namespace tetris {

// Directions we can move figures to
typedef enum { LEFT, RIGHT, DOWN } Direction;

class Board {
 public:
  const int height = 12;
  const int width = 8;

 private:
  struct BoardFigure {
    Figure figure;
    int top_left_row;
    int top_left_column;

    BoardFigure(Figure figure, int top_left_row, int top_left_column)
        : figure(figure),
          top_left_row(top_left_row),
          top_left_column(top_left_column) {}

    int Height() const { return figure.Height(); }
    int Width() const { return figure.Width(); }
    const FigureShape& Shape() const { return figure.shape; }
  };

 public:
  Board() {
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        cells_[i][j] = false;
      }
    }
  }

  // Should be called periodically to move the current figure down
  bool CallBack();

  // Should be called when player wants to move the current figure
  bool Move(Direction d);

  // Should be called when player wants to rotate the current figure
  bool Rotate();

  // Returns whether there is a figure at the given location
  CellType At(int row, int column) const {
    std::lock_guard<std::mutex> lock(mu_);
    return cells_[row][column];
  }

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
    return CanPlace(figure.Shape(), row, column);
  }
  bool CanPlace(const BoardFigure& figure) const {
    return CanPlace(figure.Shape(), figure.top_left_row,
                    figure.top_left_column);
  }

  void AddFigure(const BoardFigure& figure);

  void AddToCells(const BoardFigure& figure);
  void RemoveFromCells(const BoardFigure& figure);

  void SetCells(const BoardFigure& figure, CellType value);

  // Guard public methods
  mutable std::mutex mu_;

  CellType cells_[12][8];
  std::vector<BoardFigure> figures_;
  FigureManager figure_manager_;
};
}

#endif
