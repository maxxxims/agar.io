//
// Created by 7996832 on 17.05.2021.
//
#include "PlayerInterface.h"


void PlayerInterface::random_generate(Field& pole)
{
    this->x = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
    this->y = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
}

int PlayerInterface::getX() const
{
    return this->x;
}
int PlayerInterface::getY() const
{
    return this->y;
}

void PlayerInterface::setMass(int mass)
{
    changeMass(mass - this->R);
    //this->R = mass;
}

void PlayerInterface::changeMass(int mass)
{
    this->delta_R += mass;
}

void PlayerInterface::setSpeed(int v)
{

}

void PlayerInterface::changeSpeed(int v)
{

}

int PlayerInterface::getSize()
{
    return this->R;
}

int PlayerInterface::getCurrentSize()
{
    return this->current_R;
}

void PlayerInterface::Animate(int vx, int vy)
{
    current_R = R + delta_R;
    this->x += vx;
    this->y += vy;
    if(delta_R > 0)
    {
        this->R++;
        this->delta_R--;
    }
    if(delta_R < 0)
    {
        this->R--;
        this->delta_R++;
    }
}


