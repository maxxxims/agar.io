//
// Created by 7996832 on 06.05.2021.
//

#include "bot.h"

bot ::bot(int x, int y, int clr): PlayerInterface(x,y, clr % colour)
{
    this->R = 20;
    this->Alive = true;
    this->vx = 0;
    this->vy = 0;
    this->bpoint = 0;
    this->short_dist = 10000;
}

void bot :: draw(CImg<unsigned char> &img) const
{
    img.draw_circle(x, y, R, bot_colours[clr_parameter]);
    img.draw_text(x - 15, y - 10, "I'm bot", black);
}

void bot :: Animate(int vx, int vy)
{
    this->x += vx + this->vx;
    this->y += vy + this->vy;
}

bool bot :: isAlive() const
{
    return this->Alive;
}

void bot :: killBot()
{
    this->Alive = false;
}

void bot :: setPoint(int i)
{
    this->bpoint = i;
}
int bot :: getPoint() const
{
    return this->bpoint;
}

void bot :: setDist(int i)
{
    this->short_dist = i;
}
int bot :: getDist() const
{
    return this->short_dist;
}

void bot :: setVx(int vx)
{
    this->vx = vx;
}
void bot :: setVy(int vy)
{
    this->vy = vy;
}