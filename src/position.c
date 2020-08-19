#include "position.h"

position pos_new(char x, char y){
    position p = {
        .x = x,
        .y = y,
        .null = 0,
    };
    return p;
}
position pos_zero(){
    return pos_new(0,0);
}
position pos_up(){
    return pos_new(0,1);
}
position pos_down(){
    return pos_new(0,-1);
}
position pos_right(){
    return pos_new(-1,0);
}
position pos_left(){
    return pos_new(1,0);
}
position pos_sum(position p1, position p2){
        position p = {
        .x = p1.x + p2.x,
        .y = p1.y + p2.y,
        .null = 0,
    };
    return p;
}