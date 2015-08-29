#include "board.h"
#include <iostream>

bool Board::CallBack() {
  if (figures_.size()) {
    auto& figure = figures_.back();
    if (CanMoveDown(figure)) {
      MoveDown(figure);
      return true;
    }
  }

  BoardFigure f(GetRandomFigure(), 0, 0);
  if (CanPlace(f.figure, 0, 0)) {
    Add(f);
    return true;
  }

  return false;
}

bool Board::CanMoveDown(const BoardFigure& figure) {
  RemoveFromCells(figure);
  bool can_move_down =
      CanPlace(figure, figure.top_left_row + 1, figure.top_left_column);
  AddToCells(figure);
  return can_move_down;
}

void Board::MoveDown(BoardFigure& figure) {
  RemoveFromCells(figure);
  figure.top_left_row++;
  AddToCells(figure);
}

bool Board::CanPlace(const Figure& figure, int row, int column) {
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
      cells_[figure.top_left_row + i][figure.top_left_column + j] =
          figure.figure[i][j];
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
