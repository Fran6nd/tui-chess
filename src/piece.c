#include "piece.h"

int get_team(int pc){
    return pc & 0xf;
}
int has_moved(int pc){
    return pc & HAS_MOVED;
}
int get_type(int pc)
{
    return pc & 0xf0;
}