//
// Created by maxxxims on 01.05.2021.
//

#ifndef AGARIO_V2_PLAYERINTERFACE_H
#define AGARIO_V2_PLAYERINTERFACE_H
#include "Cimg.h"
#include "field.h"
#include <cstdlib>
using namespace cimg_library;
class PlayerInterface{
protected:
    int x, y, R, clr_parameter, delta_R, current_R;
public:
    PlayerInterface(int x, int y, int clr_parameter):x(x), y(y), clr_parameter(clr_parameter), delta_R(0), R(10){}

    void random_generate(Field& pole)
    {
        this->x = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
        this->y = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
    }

    int getX() const
    {
        return this->x;
    }
    int getY() const
    {
        return this->y;
    }

    void setMass(int mass)
    {
        changeMass(mass - this->R);
        //this->R = mass;
    }

    void changeMass(int mass)
    {
        this->delta_R += mass;
    }

    int getSize()
    {
        return this->R;
    }

    int getCurrentSize()
    {
        return this->current_R;
    }

    virtual void Animate(int vx, int vy)
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
    //virtual void animation();
    virtual void draw(CImg<unsigned char>& img) const = 0;

};

#endif //AGARIO_V2_PLAYERINTERFACE_H
