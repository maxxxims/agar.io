#include <iostream>
#include "Cimg.h"
#include <cstdlib>
#include <ctime>
#include "start_menu.h"
#include <cmath>
#include "Gameplay.h"



int main()
{
    srand(time(0));
    GamePlay& game_play = *GamePlay::get_instance();


    while(game_play.isOpen())
    {
        if(game_play.isStartMenu())
        {
            game_play.startMenu_animation();
        }
        else
        {
            game_play.MainProcess();
            game_play.point_animation();
            game_play.player_animation();
            game_play.traps_animation();
            game_play.bots_animation();
            game_play.draw();
        }


    }
}



