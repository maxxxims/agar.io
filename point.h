//
// Created by 7996832 on 06.05.2021.
//

#ifndef AGARIO_V2_POINT_H
#define AGARIO_V2_POINT_H
#include "PlayerInterface.h"

class point: public PlayerInterface{
protected:
    const unsigned char *pclr[colour] = {&colours[0][0], &colours[1][0], &colours[2][0]};
    int random_parameter;
public:
    point(int x, int y, int random_parameter);
    void draw(CImg<unsigned char>& img) const;
};

#endif //AGARIO_V2_POINT_H
