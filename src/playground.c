#include "playground.h"
#include <ncurses.h>
#include <stdlib.h>

plg_playground plg_new() {
  plg_playground pl;
  pl.turn = TEAM_WHITE;
  pl.table[0][0] = WHITE_ROOK;
  pl.table[1][0] = WHITE_KNIGHT;
  pl.table[2][0] = WHITE_BISHOP;
  pl.table[3][0] = WHITE_QUEEN;
  pl.table[4][0] = WHITE_KING;
  pl.table[5][0] = WHITE_BISHOP;
  pl.table[6][0] = WHITE_KNIGHT;
  pl.table[7][0] = WHITE_ROOK;

  pl.table[0][1] = WHITE_PAWN;
  pl.table[1][1] = WHITE_PAWN;
  pl.table[2][1] = WHITE_PAWN;
  pl.table[3][1] = WHITE_PAWN;
  pl.table[4][1] = WHITE_PAWN;
  pl.table[5][1] = WHITE_PAWN;
  pl.table[6][1] = WHITE_PAWN;
  pl.table[7][1] = WHITE_PAWN;

  int x, y;
  for (x = 0; x < 8; x++) {
    for (y = 2; y < 6; y++) {
      pl.table[x][y] = EMPTY;
    }
  }
  pl.table[0][6] = BLACK_PAWN;
  pl.table[1][6] = BLACK_PAWN;
  pl.table[2][6] = BLACK_PAWN;
  pl.table[3][6] = BLACK_PAWN;
  pl.table[4][6] = BLACK_PAWN;
  pl.table[5][6] = BLACK_PAWN;
  pl.table[6][6] = BLACK_PAWN;
  pl.table[7][6] = BLACK_PAWN;

  pl.table[0][7] = BLACK_ROOK;
  pl.table[1][7] = BLACK_KNIGHT;
  pl.table[2][7] = BLACK_BISHOP;
  pl.table[3][7] = BLACK_QUEEN;
  pl.table[4][7] = BLACK_KING;
  pl.table[5][7] = BLACK_BISHOP;
  pl.table[6][7] = BLACK_KNIGHT;
  pl.table[7][7] = BLACK_ROOK;
  return pl;
}

static const char *plg_get_symbol(char id) {
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

void plg_draw(plg_playground *plg) {
  int x, y;
  move(LINES / 2 - 4-2, COLS / 2 - 4*3);
  printw(plg->turn == TEAM_WHITE ? "TEAM WHITE      " : "TEAM BLACK      ");
  for (y = 0; y < 8; y++) {
    move(LINES / 2 - 4 + y, COLS / 2 - 4*3);
    for (x = 0; x < 8; x++) {
      char color;
      if ((y % 2 == 1 && x % 2 == 0) || (y % 2 == 0 && x % 2 == 1)) {
        color = WHITE_TILE;
      } else {
        color = BLACK_TILE;
      }
      attron(COLOR_PAIR(color));
      printw(" ");
      printw(plg_get_symbol(plg->table[x][y]));
      printw(" ");
      attroff(COLOR_PAIR(color));
    }
  }
}

plg_possibilities *plg_possibilities_new() {
  plg_possibilities *possibilities =
      (plg_possibilities *)malloc(sizeof(plg_possibilities));
  possibilities->size = 0;
  return possibilities;
}

void plg_possibilities_add(plg_possibilities *possibilities, plg_pos p) {
  possibilities->size++;
  if (possibilities->size == 0) {
    void plg_possibilities_add(plg_possibilities * possibilities, plg_pos p) {
      possibilities->list = (plg_pos *)malloc(sizeof(plg_pos));
    }
  } else {
    possibilities->list = (plg_pos *)realloc(
        possibilities->list, possibilities->size * sizeof(plg_pos));
  }
}

plg_possibilities *plg_possibilities_get_at(plg_playground *plg, plg_pos p) {
  plg_possibilities *possibilities = plg_possibilities_new();
}
void plg_possibilities_free(plg_possibilities *possibilities) {
  free(possibilities->list);
  free(possibilities);
}