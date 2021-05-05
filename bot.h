//
// Created by 7996832 on 06.05.2021.
//

#ifndef AGARIO_V2_BOT_H
#define AGARIO_V2_BOT_H
#include "PlayerInterface.h"

class bot: public PlayerInterface{
protected:
    bool isAlive;
    int vx, vy;
public:
    bot(int x, int y);
    virtual void draw(CImg<unsigned char>& img) const;
};
#endif //AGARIO_V2_BOT_H
