#include <iostream>

#include "board.h"

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
