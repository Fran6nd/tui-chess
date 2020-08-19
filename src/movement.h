#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "position.h"
#include "playground.h"

#define MVT_MUST_EAT 0x00
#define MVT_CAN_EAT 0x01
#define MVT_CANT_EAT 0x02

typedef struct movement movement;
struct movement {
    position pos_start, pos_end;
    char type;
    int piece_moving;
    int piece_eaten;
    movement * dependancy;
};

movement * mov_new(plg_playground * plg, position pos_start, position pos_end, char type);
/* For rocking. */
movement * mov_new_complicated(plg_playground * plg, position pos_start, position pos_end,position pos_start_2,position pos_end_2);
void mov_free(movement * mv);
#endif