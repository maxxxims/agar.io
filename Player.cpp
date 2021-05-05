//
// Created by 7996832 on 06.05.2021.
//

#include "Player.h"
Player :: Player(int player_colour): PlayerInterface(x0, yy0)
{
    this->player_colour = player_colour;
    this->R = 20;
}


void Player ::  draw(CImg<unsigned char>& img) const
{
    img.draw_circle(x0, yy0, R, colours[player_colour]);
    img.draw_text(x0-15, yy0 - 10, "Player", black);
}
