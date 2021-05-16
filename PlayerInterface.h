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
    void random_generate(Field& pole);
    int getX() const;
    int getY() const;
    void setMass(int mass);
    void changeMass(int mass);
    void setSpeed(int v);
    void changeSpeed(int v);
    int getSize();
    int getCurrentSize();
    virtual void Animate(int vx, int vy);
    virtual void draw(CImg<unsigned char>& img) const = 0;

};




#endif //AGARIO_V2_PLAYERINTERFACE_H
