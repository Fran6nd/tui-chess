#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#include "playground.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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
  init_pair(SELECTED_TILE, COLOR_BLACK, COLOR_RED);
  init_pair(POSSIBILITY, COLOR_BLACK, COLOR_GREEN);

  plg_playground plg = plg_new();

  int c = 0;
  do {
    if (c != ERR) {
      if (c == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
          if (event.bstate & (0x4 | 0x8)) {
            if (event.y >= LINES / 2 - 4 && event.y < LINES / 2 + 4) {
              if (event.x >= COLS / 2 - 4 * 3 && event.x < COLS / 2 + 4 * 3) {
                int i;
                int j = 0;
                for (i = event.x - 2; i > COLS / 2 - 4 * 3; i -= 3) {
                  j += 3;
                }
                position tmp = {.x = j / 3, .y = event.y - (LINES / 2 - 4)};
                int done = 0;
                for (i = 0; i < plg.possibilities.size; i++) {
                  if (plg.possibilities.list[i]->pos_end.x == tmp.x &&
                      plg.possibilities.list[i]->pos_end.y == tmp.y) {
                    done = 1;
                    plg_move(&plg, plg.selection, tmp);
                  }
                }
                if (!done)
                  plg_select(&plg, tmp);
              }
            }

          } else {
          }
        }
      }
    }
    plg_draw(&plg);

    c = wgetch(stdscr);

  } while (c != (int)'q');
  endwin();

  return EXIT_SUCCESS;
}
