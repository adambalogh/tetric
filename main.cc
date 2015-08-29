#include <termios.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>

#include "board.h"

void DrawBoard(const Board* board) {
  for (int j = 0; j < board->width; ++j) {
    mvwprintw(stdscr, 0, 3 * j, "---");
  }
  for (int i = 0; i < board->height; ++i) {
    for (int j = 0; j < board->width; ++j) {
      if (board->At(i, j)) {
        mvwprintw(stdscr, 1 + i, 3 * j, " X ");
      } else {
        mvwprintw(stdscr, 1 + i, 3 * j, "   ");
      }
    }
  }
  for (int j = 0; j < board->width; ++j) {
    mvwprintw(stdscr, 1 + board->height, 3 * j, "---");
  }
  wrefresh(stdscr);
}

int main() {
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  Board b;

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
      b.Move(LEFT);
    }
    if (key == 'd') {
      b.Move(RIGHT);
    }
    if (key == 's') {
      b.Move(DOWN);
    }
    DrawBoard(&b);
  }
  loop.join();
}
