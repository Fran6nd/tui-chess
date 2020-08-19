#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#define BLACK_TILE 1
#define WHITE_TILE 2
#define SELECTED_TILE 3
#define POSSIBILITY 4

#include "position.h"

typedef struct possibilities positionsibilities;
struct possibilities {
  int size;
  position *list;
};

typedef struct playground plg_playground;
struct playground {
  int table[8][8];
  int turn;
  position selection;
  positionsibilities possibilities;
  int top_team;
};
plg_playground plg_new();
void plg_draw(plg_playground *);
void positionsibilities_get_at(plg_playground *, int);
void plg_select(plg_playground *, position);
void positionsibilities_free(positionsibilities *);
void plg_move(plg_playground * plg, position from, position to);

#endif