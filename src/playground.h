#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#define WHITE_KING 0x12
#define WHITE_QUEEN 0x22
#define WHITE_ROOK 0x32
#define WHITE_BISHOP 0x42
#define WHITE_KNIGHT 0x52
#define WHITE_PAWN 0x62
#define BLACK_KING 0x11
#define BLACK_QUEEN 0x21
#define BLACK_ROOK 0x31
#define BLACK_BISHOP 0x41
#define BLACK_KNIGHT 0x51
#define BLACK_PAWN 0x61
#define EMPTY 0x00

#define KING 0x10
#define QUEEN 0x20
#define ROOK 0x30
#define BISHOP 0x40
#define KNIGHT 0x50
#define PAWN 0x60

#define TEAM_WHITE 0x02
#define TEAM_BLACK 0x01

#define BLACK_TILE 1
#define WHITE_TILE 2
#define SELECTED_TILE 3
#define POSSIBILITY 4

#define MVT_MUST_EAT 0x00
#define MVT_CAN_EAT 0x01
#define MVT_CANT_EAT 0x02

typedef struct position plg_pos;
struct position {
  int x, y;
};

typedef struct possibilities plg_possibilities;
struct possibilities {
  int size;
  plg_pos *list;
};

typedef struct playground plg_playground;
struct playground {
  char table[8][8];
  char turn;
  plg_pos selection;
  plg_possibilities possibilities;
  char top_team;
};
plg_playground plg_new();
void plg_draw(plg_playground *);
void plg_possibilities_get_at(plg_playground *);
void plg_select(plg_playground *, plg_pos);
void plg_possibilities_free(plg_possibilities *);
void plg_move(plg_playground * plg, plg_pos from, plg_pos to);

#endif