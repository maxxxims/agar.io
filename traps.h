//
// Created by 7996832 on 01.05.2021.
//

#ifndef AGARIO_V2_TRAPS_H
#define AGARIO_V2_TRAPS_H

#include "PlayerInterface.h"

class traps: public PlayerInterface{
private:
    int trapLengt;
public:
    traps(int x, int y);
    virtual void Animate(int vx, int vy);
    int trap_lengt() const;
};


#endif //AGARIO_V2_TRAPS_H
