//
// Created by maxxxims on 30.04.2021.
//
#ifndef AGARIO_V2_FIELD_H
#define AGARIO_V2_FIELD_H

#include "Cimg.h"
#include "PlayerInterface.h"
using namespace cimg_library;

class Field{
private:
    int x_min, x_max, y_min, y_max;
public:
    Field();
    void Animate(int v_x, int v_y);
    int getx1() const;
    int getx2() const;
    int gety1() const;
    int gety2() const;
    void draw(CImg<unsigned char>& img) const;
};


#endif //AGARIO_V2_FIELD_H
