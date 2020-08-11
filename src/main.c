#include <curses.h>
#include <locale.h>
#include <stdlib.h>

#define WHITE_KING 0
#define WHITE_QUEEN 1
#define WHITE_ROOK 2
#define WHITE_BISHOP 3
#define WHITE_KNIGHT 4
#define WHITE_PAWN 5
#define BLACK_KING 6
#define BLACK_QUEEN 7
#define BLACK_ROOK 8
#define BLACK_BISHOP 9
#define BLACK_KNIGHT 10
#define BLACK_PAWN 11

const char *get_symbol(char id) {
  switch (id) {
  case WHITE_KING:
    return "\xe2\x99\x94";
  case WHITE_QUEEN:
    return "\xe2\x99\x95";
  case WHITE_ROOK:
    return "\xe2\x99\x96";
  case WHITE_BISHOP:
    return "\xe2\x99\x97";
  case WHITE_KNIGHT:
    return "\xe2\x99\x98";
  case WHITE_PAWN:
    return "\xe2\x99\x99";
  case BLACK_KING:
    return "\xe2\x99\x9a";
  case BLACK_QUEEN:
    return "\xe2\x99\x9b";
  case BLACK_ROOK:
    return "\xe2\x99\x9c";
  case BLACK_BISHOP:
    return "\xe2\x99\x9d";
  case BLACK_KNIGHT:
    return "\xe2\x99\x9e";
  case BLACK_PAWN:
    return "\xe2\x99\x9f";
  default:
    return "\xE2\x9D\x8C";
  }
}

char table[8][8];

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  initscr();
  printw(get_symbol(WHITE_KING));
  printw("\n");
  printw(get_symbol(47));
  printw("\n");

  getch();
  endwin();

  return EXIT_SUCCESS;
}
