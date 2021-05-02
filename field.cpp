//
// Created by 7996832 on 30.04.2021.
//

#include "field.h"
#include "constances.h"
#include "field.h"

Field ::  Field()
{
    this->x_max = Xm / 2;
    this->x_min = -1 * x_max;
    this->y_max = Ym / 2;
    this->y_min = -1 * y_max;
}

void Field :: Animate(int v_x, int v_y)
{
    this->x_max += v_x;
    this->x_min += v_x;
    this->y_max += v_y;
    this->y_min += v_y;
}

void Field :: draw(CImg<unsigned char>& img) const
{
    img.draw_line(getx1(), gety1(), 0, getx2(), gety1(), 0, black);
    img.draw_line(getx1(), gety2(), 0, getx2(),gety2(), 0, black);
    img.draw_line(getx1(), gety1(), 0, getx1(), gety2(), 0, black);
    img.draw_line(getx2(), gety1(), 0, getx2(), gety2(), 0, black);

}

int Field :: getx1() const
{
    return this->x_min;
}
int Field :: getx2() const
{
    return this->x_max;
}
int Field :: gety1() const
{
    return this->y_min;
}
int Field :: gety2() const
{
    return this->y_max;
}
