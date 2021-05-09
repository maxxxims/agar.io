//
// Created by 7996832 on 07.05.2021.
//

#include "Gameplay.h"
#include<iostream>


GamePlay* GamePlay::instance = nullptr;
GamePlay* GamePlay::get_instance()
{
    if(instance != nullptr)     return instance;
    instance = new GamePlay;
    return instance;
}

GamePlay :: GamePlay(): bg(D, H, 1, 3, 255), dsp(D, H, "Agar.io", 0), pole()
{
    bg.draw_rectangle(0, 0, D, H, grey);
    dsp.display(bg);
    CImg<unsigned char> img(bg);
    start_menu = new StartMenu;

    points.reserve(n);
    for(int i = 0; i < n; i++)
    {
        point new_point(0,0,i);
        new_point.random_generate(pole);
        points.push_back(new_point);
    }
}

void GamePlay :: MainProcess()
{


    int x, y;
    while (start_menu->is_open() == false) {
        x = dsp.mouse_x();
        y = dsp.mouse_y();
        img = bg;
        start_menu->process(x, y, img, dsp);
        smart_bot = start_menu->what_bots();
        dsp.display(img);
    }
    setPlayerColour(c);
    user_name = new Player(c);

    while(!dsp.is_closed())
    {
        img = bg;
        pole.draw(img);
        user_name->draw(img);
        for(auto it = points.begin(); it != points.end(); ++it)
        {
            //it->Animate(15, 15);
            it->draw(img);
        }


        dsp.display(img);
    }
}


void GamePlay ::setPlayerColour(int c)
{
    this->c = c;
}