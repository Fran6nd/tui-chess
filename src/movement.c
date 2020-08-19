#include <stdlib.h>
#include "playground.h"
#include "movement.h"
#include "piece.h"

movement * mov_new(plg_playground * plg, position pos_start, position pos_end, char type)
{
    int start_tile = plg->table[pos_start.x][pos_start.y];
    int end_tile = plg->table[pos_end.x][pos_end.y];
    if(plg->table[pos_start.x][pos_start.y] == EMPTY)
        return NULL;
    movement * m = malloc(sizeof(movement));
    m->pos_start = pos_start;
    m->pos_end = pos_end;
    m->piece_moving = plg->table[pos_start.x][pos_start.y];
    m->piece_eaten = plg->table[pos_end.x][pos_end.y];
    m->dependancy = NULL;
    m->type = type;
    return m;
}
/* For rocking. */
movement * mov_new_complicated(plg_playground * plg, position pos_start, position pos_end,position pos_start_2,position pos_end_2){
    movement * m;
    m = mov_new(plg, pos_start, pos_end, MVT_CANT_EAT);
    m->dependancy = mov_new(plg, pos_start_2, pos_end_2, MVT_CANT_EAT);
    return m;
}
void mov_free(movement * mv)
{
    if(mv != NULL){
        if(mv->dependancy != NULL){
            mov_free(mv->dependancy);
        }
        free(mv);
    }
}