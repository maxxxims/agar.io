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
    int x, y, R, clr_parameter;
public:
    PlayerInterface(int x, int y, int clr_parameter):x(x), y(y), clr_parameter(clr_parameter){}

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
        this->R = mass;
    }

    void changeMass(int mass)
    {
        this->R += mass;
    }

    int getSize()
    {
        return this->R;
    }

    virtual void Animate(int vx, int vy)
    {
        this->x += vx;
        this->y += vy;
    }
    //virtual void animation();
    virtual void draw(CImg<unsigned char>& img) const = 0;

};

#endif //AGARIO_V2_PLAYERINTERFACE_H
