#include <termios.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>

#include "board.h"

void DrawBoard(const tetris::Board* board) {
  attron(COLOR_PAIR(1));

  for (int j = 0; j < board->width; ++j) {
    mvwprintw(stdscr, 0, 1 * j, "---");
  }
  for (int i = 0; i < board->height; ++i) {
    mvwprintw(stdscr, 1 + i, 0, "|");
    for (int j = 0; j < board->width; ++j) {
      if (board->At(i, j)) {
        mvwprintw(stdscr, 1 + i, 1 + 1 * j, "O");
      } else {
        mvwprintw(stdscr, 1 + i, 1 + 1 * j, " ");
      }
      mvwprintw(stdscr, 1 + i, 1 * board->width + 1, "|");
    }
  }
  for (int j = 0; j < board->width; ++j) {
    mvwprintw(stdscr, 1 + board->height, 1 * j, "---");
  }
  wrefresh(stdscr);

  attroff(COLOR_PAIR(1));
}

int main() {
  initscr();
  clear();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  tetris::Board b;

  std::thread loop([&]() {
    while (b.CallBack()) {
      DrawBoard(&b);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  char c;
  while (true) {
    auto key = getch();
    if (key == 'a') {
      b.Move(tetris::Board::LEFT);
    }
    if (key == 'd') {
      b.Move(tetris::Board::RIGHT);
    }
    if (key == 's') {
      b.Move(tetris::Board::DOWN);
    }
    DrawBoard(&b);
  }
  loop.join();
}
