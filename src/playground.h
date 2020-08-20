#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#define BLACK_TILE 1
#define WHITE_TILE 2
#define SELECTED_TILE 3
#define POSSIBILITY 4

#include "position.h"
#include "movement.h"

typedef struct possibilities possibilities;
struct possibilities {
  int size;
  movement **list;
};

typedef struct playground plg_playground;
struct playground {
  int table[8][8];
  int turn;
  possibilities possibilities;
  int top_team;
};
plg_playground plg_new();
void possibilities_get(plg_playground *, int);
void possibilities_free(possibilities *);
void plg_move(plg_playground * plg, position from, position to);


movement * mov_new(plg_playground * plg, position pos_start, position pos_end, char type);
/* For rocking. */
movement * mov_new_complicated(plg_playground * plg, position pos_start, position pos_end,position pos_start_2,position pos_end_2);
void mov_free(movement * mv);

#endif