#ifndef PIECE_H
#define PIECE_H

#define KING 0x010
#define QUEEN 0x020
#define ROOK 0x030
#define BISHOP 0x040
#define KNIGHT 0x050
#define PAWN 0x060
#define HAS_MOVED 0x100

#define TEAM_WHITE 0x002
#define TEAM_BLACK 0x001

#define WHITE_KING (TEAM_WHITE | KING)
#define WHITE_QUEEN (TEAM_WHITE | QUEEN)
#define WHITE_ROOK (TEAM_WHITE | ROOK)
#define WHITE_BISHOP (TEAM_WHITE | BISHOP)
#define WHITE_KNIGHT (TEAM_WHITE | KNIGHT)
#define WHITE_PAWN (TEAM_WHITE | PAWN)
#define BLACK_KING (TEAM_BLACK | KING)
#define BLACK_QUEEN (TEAM_BLACK | QUEEN)
#define BLACK_ROOK (TEAM_BLACK | ROOK)
#define BLACK_BISHOP (TEAM_BLACK | BISHOP)
#define BLACK_KNIGHT (TEAM_BLACK | KNIGHT)
#define BLACK_PAWN (TEAM_BLACK | PAWN)
#define EMPTY 0x000

int get_team(int pc);
int has_moved(int pc);
int get_type(int pc);

#endif