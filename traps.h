//
// Created by 7996832 on 01.05.2021.
//

#ifndef AGARIO_V2_TRAPS_H
#define AGARIO_V2_TRAPS_H

#include "PlayerInterface.h"

class trap: public PlayerInterface{
private:
    int trapLengt;
public:
    trap(int x, int y);
    int trap_lengt() const;
    int getX() const;
    int getY() const;
    void draw(CImg<unsigned char>& img) const;
};


#endif //AGARIO_V2_TRAPS_H
