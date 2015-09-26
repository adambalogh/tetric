#include <iostream>
#include <thread>

#include "board.h"

namespace tetris {

void Board::SetCells(const BoardFigure& figure, CellType value) {
  for (int i = 0; i < figure.height(); ++i) {
    for (int j = 0; j < figure.width(); ++j) {
      if (figure.shape[i][j]) {
        cells_[figure.top_left_row + i][figure.top_left_column + j] = value;
      }
    }
  }
}

void Board::AddToCells(const BoardFigure& figure) { SetCells(figure, 1); }

void Board::RemoveFromCells(const BoardFigure& figure) { SetCells(figure, 0); }

void Board::AddFigure(const BoardFigure& figure) {
  figures_.push_back(figure);
  AddToCells(figure);
}

void Board::ClearFullRows() {
  bool is_full[height];
  for (int i = 0; i < height; ++i) {
    is_full[i] = std::all_of(std::begin(cells_[i]), std::end(cells_[i]),
                             [](auto el) { return el == 1; });
  }

  int index = height - 1;
  for (int i = height - 1; i >= 0; --i) {
    if (is_full[i]) continue;
    cells_[index--] = cells_[i];
  }

  std::for_each(std::begin(cells_), std::begin(cells_) + ++index,
                [](auto& row) { row.fill(0); });
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
  if (figures_.size()) {
    auto& figure = figures_.back();
    if (MoveDownIfPossible(figure)) {
      return true;
    }
    ClearFullRows();
  }

  // Add new figure to board
  auto new_figure = figure_gen_->Get();
  if (CanPlace(new_figure)) {
    AddFigure(new_figure);
    return true;
  }

  return false;
}

bool Board::Move(Direction d) {
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
  const auto& figure = figures_.back();
  // TODO position should not be the same in all cases
  BoardFigure rotated_figure{figure.type, (figure.orientation + 1) % 4,
                             figure.top_left_row, figure.top_left_column};
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
