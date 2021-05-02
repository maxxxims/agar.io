//
// Created by 7996832 on 01.05.2021.
//

#include "traps.h"

traps :: traps(int x, int y) : PlayerInterface(x, y) {
    this->trapLengt = 100;
}

void traps ::Animate(int vx, int vy)
{
    this->x += vx;
    this->y += vy;
}

int traps ::trap_lengt() const
{
    return this->trap_lengt();
}