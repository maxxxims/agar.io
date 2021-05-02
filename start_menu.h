//
// Created by 7996832 on 30.04.2021.
//

#ifndef AGARIO_V2_START_MENU_H
#define AGARIO_V2_START_MENU_H
#include "Cimg.h"
using namespace cimg_library;


class StartMenu{
private:
    int x, y,q, clr;
    bool start, smart_bot;

public:
    StartMenu();
    void process(int x, int y, CImg<unsigned char>& img, CImgDisplay& dsp);
    bool is_open() const;
    bool what_bots() const;
    int what_colour() const;

};

#endif //AGARIO_V2_START_MENU_H
