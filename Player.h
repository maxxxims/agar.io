//
// Created by 7996832 on 06.05.2021.
//

#ifndef AGARIO_V2_PLAYER_H
#define AGARIO_V2_PLAYER_H
#include "PlayerInterface.h"

class Player: public PlayerInterface{
public:
    Player(int player_colour);
    virtual void draw(CImg<unsigned char>& img) const override;
};

#endif //AGARIO_V2_PLAYER_H
