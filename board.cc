#include <iostream>
#include <thread>

#include "board.h"

namespace tetris {

void Board::AddFigure(const BoardFigure& figure) {
  figures_.push_back(figure);
  AddToCells(figure);
}

void Board::SetCells(const BoardFigure& figure, CellType value) {
  for (int i = 0; i < figure.Height(); ++i) {
    for (int j = 0; j < figure.Width(); ++j) {
      if (figure.Shape()[i][j]) {
        cells_[figure.top_left_row + i][figure.top_left_column + j] = value;
      }
    }
  }
}

void Board::AddToCells(const BoardFigure& figure) { SetCells(figure, 1); }
void Board::RemoveFromCells(const BoardFigure& figure) { SetCells(figure, 0); }

bool Board::CanPlace(const FigureShape& figure, int row, int column) const {
  if (row < 0 || column < 0) {
    return false;
  }
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

bool Board::MoveIfPossible(BoardFigure& figure, Direction d) {
  RemoveFromCells(figure);
  int new_row = figure.top_left_row;
  int new_column = figure.top_left_column;
  switch (d) {
    case LEFT:
      new_column--;
      break;
    case RIGHT:
      new_column++;
      break;
    case DOWN:
      new_row++;
      break;
  }
  bool can_move = CanPlace(figure, new_row, new_column);
  if (can_move) {
    figure.top_left_row = new_row;
    figure.top_left_column = new_column;
  }
  AddToCells(figure);

  return can_move;
}

bool Board::CallBack() {
  std::lock_guard<std::mutex> lock(mu_);
  if (figures_.size()) {
    auto& figure = figures_.back();
    if (MoveDownIfPossible(figure)) {
      return true;
    }
  }
  BoardFigure f(figure_manager_.GetRandomUpFigure(), 0, 0);
  if (CanPlace(f)) {
    AddFigure(f);
    return true;
  }

  return false;
}

bool Board::Move(Direction d) {
  std::lock_guard<std::mutex> lock(mu_);
  if (!figures_.size()) {
    return false;
  }
  auto& figure = figures_.back();
  return MoveIfPossible(figure, d);
}
}
