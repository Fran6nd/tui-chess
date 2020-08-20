#ifndef POSITION_H
#define POSITION_H

typedef struct position position;
struct position{
char x, y, null;
};

position pos_new(char x, char y);
position pos_sum(position p1, position p2);
position pos_zero();
position pos_up();
position pos_down();
position pos_right();
position pos_left();
#endif