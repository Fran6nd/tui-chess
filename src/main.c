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
#define EMPTY 12

#define TEAM_WHITE 0
#define TEAM_BLACK 1

#define BLACK_TILE 1
#define WHITE_TILE 2

const char *get_symbol(char id, int x, int y) {
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
  case EMPTY:
    return " ";
  default:
    return "\xE2\x9D\x8C";
  }
}
char get_team(char id) {
  if (id == EMPTY)
    return EMPTY;
  if (id < 6)
    return TEAM_WHITE;
  return TEAM_BLACK;
}

char table[8][8];

void new_table(char t[8][8]) {
  t[0][0] = WHITE_ROOK;
  t[1][0] = WHITE_KNIGHT;
  t[2][0] = WHITE_BISHOP;
  t[3][0] = WHITE_QUEEN;
  t[4][0] = WHITE_KING;
  t[5][0] = WHITE_BISHOP;
  t[6][0] = WHITE_KNIGHT;
  t[7][0] = WHITE_ROOK;

  t[0][1] = WHITE_PAWN;
  t[1][1] = WHITE_PAWN;
  t[2][1] = WHITE_PAWN;
  t[3][1] = WHITE_PAWN;
  t[4][1] = WHITE_PAWN;
  t[5][1] = WHITE_PAWN;
  t[6][1] = WHITE_PAWN;
  t[7][1] = WHITE_PAWN;

  int x, y;
  for (x = 0; x < 7; x++) {
    for (y = 2; y < 6; y++) {
      t[x][y] = EMPTY;
    }
  }
  t[0][6] = BLACK_PAWN;
  t[1][6] = BLACK_PAWN;
  t[2][6] = BLACK_PAWN;
  t[3][6] = BLACK_PAWN;
  t[4][6] = BLACK_PAWN;
  t[5][6] = BLACK_PAWN;
  t[6][6] = BLACK_PAWN;
  t[7][6] = BLACK_PAWN;

  t[0][7] = BLACK_ROOK;
  t[1][7] = BLACK_KNIGHT;
  t[2][7] = BLACK_BISHOP;
  t[3][7] = BLACK_QUEEN;
  t[4][7] = BLACK_KING;
  t[5][7] = BLACK_BISHOP;
  t[6][7] = BLACK_KNIGHT;
  t[7][7] = BLACK_ROOK;
}

void draw_table(char t[8][8]) {
  int x, y;
  for (x = 0; x < 8; x++) {
    for (y = 0; y < 8; y++)
      printw(get_symbol(t[x][y], x, y));
    printw("\n");
  }
}

int main(int argc, char *argv[]) {
  /*if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }*/
  start_color();
  init_pair(BLACK_TILE, COLOR_WHITE, COLOR_BLACK);
  init_pair(WHITE_TILE, COLOR_BLACK, COLOR_WHITE);
  setlocale(LC_ALL, "");

  initscr();
  new_table(table);
  int x, y;
  for (x = 0; x < 8; x++) {
    for (y = 0; y < 8; y++) {
      char color;
      if ((y % 2 == 1 && x % 2 == 0) || (y % 2 == 0 && x % 2 == 1)) {
        color = WHITE_TILE;
      } else {
        color = BLACK_TILE;
      }
      attron(COLOR_PAIR(color));
      printw(get_symbol(table[x][y], x, y));
      attroff(COLOR_PAIR(color));
    }
    printw("\n");
  }

  getch();
  endwin();

  return EXIT_SUCCESS;
}
