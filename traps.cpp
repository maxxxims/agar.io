//
// Created by 7996832 on 01.05.2021.
//

#include "traps.h"
#include "constances.h"

trap :: trap(int x, int y) : PlayerInterface(x, y) {
    this->trapLengt = 100;
}

void trap ::draw(CImg<unsigned char> &img) const
{
    img.draw_triangle(x, y, x + trapLengt, y, x + trapLengt/2, y - trapLengt/2, black);
}

int trap ::trap_lengt() const
{
    return this->trap_lengt();
}

int trap :: getX() const
{
    return this->x;
}

int trap :: getY() const
{
    return this->y;
}