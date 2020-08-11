#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

#include "playground.h"

char get_team(char id) {
  if (id == EMPTY)
    return EMPTY;
  if (id < 6)
    return TEAM_WHITE;
  return TEAM_BLACK;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }
  start_color();
  init_pair(BLACK_TILE, COLOR_BLACK, COLOR_BLUE);
  init_pair(WHITE_TILE, COLOR_BLACK, COLOR_WHITE);

  plg_playground plg = plg_new();
  plg_draw(&plg);

  getch();
  endwin();

  return EXIT_SUCCESS;
}
