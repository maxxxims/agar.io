//
// Created by maxxxims on 01.05.2021.
//

#ifndef AGARIO_V2_PLAYERINTERFACE_H
#define AGARIO_V2_PLAYERINTERFACE_H
#include "Cimg.h"
using namespace cimg_library;

class PlayerInterface{
protected:
    int x, y;
public:
    PlayerInterface(int x, int y):x(x), y(y){}
    void random_generate(){

    }
    virtual void Animate(int vx, int vy) = 0;
    //virtual void animation();
    virtual void draw() const = 0;

};

#endif //AGARIO_V2_PLAYERINTERFACE_H
