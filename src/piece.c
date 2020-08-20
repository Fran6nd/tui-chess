#include "piece.h"

int get_team(int id){
    if (id & TEAM_WHITE)
        return TEAM_WHITE;
    if (id & TEAM_BLACK)
        return TEAM_BLACK;
    return EMPTY;
}
int has_moved(int pc){
    return pc & HAS_MOVED;
}
int get_type(int pc)
{
    return pc & 0xf0;
}