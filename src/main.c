#include <locale.h>
#include <ncurses.h>
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
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  printf("\033[?1003h\n");
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

  int c = 0;
  do {

    plg_draw(&plg);
    if (c != ERR) {
      if (c == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
          if (event.y >= LINES / 2 - 4 && event.y < LINES / 2 + 4) {
            if (event.x >= COLS / 2 - 4*3 && event.x < COLS / 2 + 4*3) {
              move(event.y, event.x);
              addch('x');
            }
          }

        } else {
        }
      }
    }
    c = wgetch(stdscr);

  } while (c != (int)'q');
  endwin();

  return EXIT_SUCCESS;
}
