//
// Created by 7996832 on 07.05.2021.
//

#ifndef AGARIO_V2_GAMEPLAY_H
#define AGARIO_V2_GAMEPLAY_H
#include "Cimg.h"
#include <ctime>
#include <vector>
#include "constances.h"
#include "start_menu.h"
#include "PlayerInterface.h"
#include "traps.h"
#include "point.h"
#include "Player.h"
#include "bot.h"
#include <list>
using std::list;
using std::vector;

class StartMenu;

class GamePlay{
private:
    CImg<unsigned char> img, bg;
    CImgDisplay dsp;
    StartMenu* start_menu;
    Field pole;
    Player* user_name;
    list<bot> bots;
    vector<trap> traps;
    vector<point> points;
    bool smart_bot, start;
    static GamePlay* instance;
    int c, vx, vy, counter;
    float k, k1x, k1y;

    void Init();
    void manage_bots();
public:
    GamePlay();
    void MainProcess();

    void startMenu_animation();
    void point_animation();
    void player_animation();
    void traps_animation();
    void bots_animation();
    void draw();
    void setPlayerColour(int c);
    void setBotsBrain(bool f);

    bool isOpen()const;
    bool isStartMenu()const;

    static GamePlay* get_instance();
};

#endif //AGARIO_V2_GAMEPLAY_H
