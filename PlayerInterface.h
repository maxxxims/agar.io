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
    int x, y;
public:
    PlayerInterface(int x, int y):x(x), y(y){}

    void random_generate(Field& pole)
    {
        this->x = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
        this->y = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
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
