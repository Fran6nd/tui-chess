#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#include "playground.h"
#include "piece.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

position selection;

static const char *plg_get_symbol(int id)
{
  switch (id & 0x0FF)
  {
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

void plg_draw(plg_playground *plg)
{
  int x, y;
  move(LINES / 2 - 4 - 2, COLS / 2 - 4 * 3);
  printw(plg->turn == TEAM_WHITE ? "TEAM WHITE      " : "TEAM BLACK      ");
  for (y = 0; y < 8; y++)
  {
    move(LINES / 2 - 4 + y, COLS / 2 - 4 * 3);
    // move(LINES / 2 + 4 - y, COLS / 2 - 4 * 3);
    for (x = 0; x < 8; x++)
    {
      int color;
      if (selection.y == y && x == selection.x && (!selection.null))
      {
        color = SELECTED_TILE;
      }
      else if ((y % 2 == 1 && x % 2 == 0) || (y % 2 == 0 && x % 2 == 1))
      {
        color = WHITE_TILE;
      }
      else
      {
        color = BLACK_TILE;
      }
      int i;
      if (plg->possibilities.size > 0)
      {

        for (i = 0; i < plg->possibilities.size; i++)
        {
          if (x == plg->possibilities.list[i]->pos_end.x &&
              y == plg->possibilities.list[i]->pos_end.y &&
              !selection.null &&
              plg->possibilities.list[i]->pos_start.y == selection.y &&
              plg->possibilities.list[i]->pos_start.x == selection.x)
          {
            color = POSSIBILITY;
            break;
          }
        }
      }
      attron(COLOR_PAIR(color));
      printw(" ");
      printw(plg_get_symbol(plg->table[x][y]));
      printw(" ");
      attroff(COLOR_PAIR(color));
    }
  }
}

int main(int argc, char *argv[])
{
  selection = pos_new(-1, -1);
  selection.null = 1;
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  printf("\033[?1003h\n");
  curs_set(0);
  if (has_colors() == FALSE)
  {
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
  do
  {
    if (c != ERR)
    {
      if (c == KEY_MOUSE)
      {
        MEVENT event;
        if (getmouse(&event) == OK)
        {
          if (event.bstate & (0x4 | 0x8))
          {
            if (event.y >= LINES / 2 - 4 && event.y < LINES / 2 + 4)
            {
              if (event.x >= COLS / 2 - 4 * 3 && event.x < COLS / 2 + 4 * 3)
              {
                int i;
                int j = 0;
                for (i = event.x - 2; i > COLS / 2 - 4 * 3; i -= 3)
                {
                  j += 3;
                }
                position tmp = {.x = j / 3, .y = event.y - (LINES / 2 - 4)};
                if (get_team(plg.table[tmp.x][tmp.y]) == plg.turn )
                {
                  selection = tmp;
                  selection.null = 0;
                  possibilities_get(&plg, 0);
                }
                else if(!selection.null)
                {
                  for (i = 0; i < plg.possibilities.size; i++)
                  {
                    if (plg.possibilities.list[i]->pos_end.x == tmp.x &&
                        plg.possibilities.list[i]->pos_end.y == tmp.y &&
                        plg.possibilities.list[i]->pos_start.y == selection.y &&
                        plg.possibilities.list[i]->pos_start.x == selection.x)
                    {
                      plg_move(&plg, selection, tmp);
                      if(plg.possibilities.list[i]->has_dependancy){
                        plg_move(&plg, plg.possibilities.list[i]->dependancy->pos_start, plg.possibilities.list[i]->dependancy->pos_end);
                      }
                      break;
                    }
                  }
                    selection.null = 1;
                }
              }
            }
          }
          else
          {
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
