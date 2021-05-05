//
// Created by 7996832 on 06.05.2021.
//

#include "point.h"


point :: point(int x, int y, int random_parameter): PlayerInterface(x,y,random_parameter % colour)
{
    this->R = 10;
}

void point ::  draw(CImg<unsigned char>& img) const
{
    img.draw_circle(x, y, R, colours[clr_parameter]);
}