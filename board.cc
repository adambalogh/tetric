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

void Board::ClearFullRows() {
  bool is_full[height];
  for (int i = 0; i < height; ++i) {
    bool full = true;
    for (int j = 0; j < width; ++j) {
      if (!cells_[i][j]) {
        full = false;
      }
    }
    is_full[i] = full;
  }

  int index = height - 1;
  for (int i = height - 1; i >= 0; --i) {
    if (is_full[i]) continue;
    for (int j = 0; j < width; ++j) {
      cells_[index][j] = cells_[i][j];
    }
    index--;
  }

  for (int i = index - 1; i >= 0; --i) {
    for (int j = 0; j < width; ++j) {
      cells_[i][j] = 0;
    }
  }
}

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
    } else {
      ClearFullRows();
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

bool Board::Rotate() {
  if (!figures_.size()) {
    return false;
  }
  auto& figure = figures_.back();
  auto rotated_shape = figure_manager_.GetRotated(figure.figure);
  BoardFigure rotated_figure{rotated_shape, figure.top_left_row,
                             figure.top_left_column};
  RemoveFromCells(figure);
  if (CanPlace(rotated_figure)) {
    figures_.pop_back();
    figures_.push_back(rotated_figure);
    AddToCells(rotated_figure);
    return true;
  } else {
    AddToCells(figure);
    return false;
  }
}
}
