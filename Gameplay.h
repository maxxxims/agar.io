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
#include <array>
using std::array;
using std::vector;

class StartMenu;

class GamePlay{
private:
    CImg<unsigned char> img, bg;
    CImgDisplay dsp;
    StartMenu* start_menu;
    Field pole;
    Player* user_name;
    vector<bot> bots;
    vector<trap> traps;
    vector<point> points;
    bool smart_bot;
    static GamePlay* instance;
    int c;
public:
    GamePlay();
    void Init();
    void MainProcess();
    void setPlayerColour(int c);
    bool isOpen()const;
    static GamePlay* get_instance();
};

#endif //AGARIO_V2_GAMEPLAY_H
