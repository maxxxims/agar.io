//
// Created by 7996832 on 06.05.2021.
//

#ifndef AGARIO_V2_BOT_H
#define AGARIO_V2_BOT_H
#include "PlayerInterface.h"

class bot: public PlayerInterface{
protected:
    bool Alive;
    int vx, vy, short_dist, bpoint;
    PlayerInterface* bots_point;
public:
    bot(int x, int y, int clr);
    virtual void Animate(int vx, int vy) override;
    virtual void draw(CImg<unsigned char>& img) const override;
    bool isAlive() const;
    void killBot();
    void setPoint(PlayerInterface* p);
    PlayerInterface* getPoint() const;
    void setDist(int i);
    int getDist() const;
    void setVx(int vx);
    void setVy(int vy);
};
#endif //AGARIO_V2_BOT_H
