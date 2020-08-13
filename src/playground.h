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
#define EMPTY 0x000

#define KING 0x010
#define QUEEN 0x020
#define ROOK 0x030
#define BISHOP 0x040
#define KNIGHT 0x050
#define PAWN 0x060

#define HAS_MOVED 0x100

#define TEAM_WHITE 0x002
#define TEAM_BLACK 0x001

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
  int table[8][8];
  int turn;
  plg_pos selection;
  plg_possibilities possibilities;
  int top_team;
};
plg_playground plg_new();
void plg_draw(plg_playground *);
void plg_possibilities_get_at(plg_playground *, int);
void plg_select(plg_playground *, plg_pos);
void plg_possibilities_free(plg_possibilities *);
void plg_move(plg_playground * plg, plg_pos from, plg_pos to);

#endif