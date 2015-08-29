#include "board.h"
#include <iostream>
#include <thread>

bool Board::Move(Direction d) {
  std::lock_guard<std::mutex> lock(mu_);
  if (!figures_.size()) {
    return false;
  }
  auto& figure = figures_.back();
  if (CanMoveTo(figure, d)) {
    MoveTo(figure, d);
    return true;
  }

  return false;
}

bool Board::CallBack() {
  std::lock_guard<std::mutex> lock(mu_);
  if (figures_.size()) {
    auto& figure = figures_.back();
    if (CanMoveDown(figure)) {
      MoveDown(figure);
      return true;
    }
  }

  BoardFigure f(GetRandomFigure(), 0, 0);
  if (CanPlace(f)) {
    Add(f);
    return true;
  }

  return false;
}

bool Board::CanMoveTo(const BoardFigure& figure, Direction d) {
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
  bool can_move_to = CanPlace(figure, new_row, new_column);
  AddToCells(figure);
  return can_move_to;
}

void Board::MoveTo(BoardFigure& figure, Direction d) {
  RemoveFromCells(figure);
  switch (d) {
    case LEFT:
      figure.top_left_column--;
      break;
    case RIGHT:
      figure.top_left_column++;
      break;
    case DOWN:
      figure.top_left_row++;
      break;
  }
  AddToCells(figure);
}

bool Board::CanPlace(const Figure& figure, int row, int column) {
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

void Board::Add(const BoardFigure& figure) {
  figures_.push_back(figure);
  AddToCells(figure);
}

void Board::AddToCells(const BoardFigure& figure) {
  for (int i = 0; i < figure.height(); ++i) {
    for (int j = 0; j < figure.width(); ++j) {
      if (figure.figure[i][j]) {
        cells_[figure.top_left_row + i][figure.top_left_column + j] = 1;
      }
    }
  }
}

void Board::RemoveFromCells(const BoardFigure& figure) {
  for (int i = 0; i < figure.height(); ++i) {
    for (int j = 0; j < figure.width(); ++j) {
      if (figure.figure[i][j]) {
        cells_[figure.top_left_row + i][figure.top_left_column + j] = 0;
      }
    }
  }
}
