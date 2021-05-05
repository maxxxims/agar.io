//
// Created by 7996832 on 06.05.2021.
//

#include "point.h"


point :: point(int x, int y, int random_parameter): PlayerInterface(x,y)
{
    this->random_parameter = random_parameter;
}

void point ::  draw(CImg<unsigned char>& img) const
{
    img.draw_circle(x, y, 10, pclr[random_parameter%colour]);
}