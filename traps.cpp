//
// Created by 7996832 on 01.05.2021.
//

#include "traps.h"

trap :: trap(int x, int y) : PlayerInterface(x, y, 0) {
    this->R = 100;
}

void trap ::draw(CImg<unsigned char> &img) const
{
    img.draw_triangle(x, y, x + R, y, x + R/2, y - R/2, black);
}

int trap ::trap_lengt() const
{
    return this->R;
}
