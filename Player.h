//
// Created by 7996832 on 06.05.2021.
//

#ifndef AGARIO_V2_PLAYER_H
#define AGARIO_V2_PLAYER_H
#include "PlayerInterface.h"

class Player: public PlayerInterface{
protected:
    int player_colour;
public:
    Player(int player_colour);
    void eat(int mass);
    virtual void draw(CImg<unsigned char>& img) const;
};

#endif //AGARIO_V2_PLAYER_H