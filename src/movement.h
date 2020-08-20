#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "playground.h"
#include "position.h"

#define MVT_MUST_EAT 0x00
#define MVT_CAN_EAT 0x01
#define MVT_CANT_EAT 0x02

typedef struct movement movement;
struct movement {
    position pos_start, pos_end;
    char type;
    int piece_moving;
    int piece_eaten;
    int has_dependancy;
    movement * dependancy;
};

#endif