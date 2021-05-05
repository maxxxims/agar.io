//
// Created by 7996832 on 30.04.2021.
//

#include "start_menu.h"


StartMenu ::StartMenu() {
    start = false;
    smart_bot = false;
    clr = 1;
}

void StartMenu :: process(int x, int y, CImg<unsigned char>& img, CImgDisplay& dsp )
{
    this->x = x;
    this->y = y;
    this->q = 250;
    img.draw_circle(x0, yy0, 100, blue);
    img.draw_circle(x0+q, yy0, 100, red);
    img.draw_circle(x0-q, yy0, 100, green);
    img.draw_text(x0 - 500, yy0 - 350, "Choose your colour and click", black, grey, 1, 100);
    img.draw_text(x0 + 300, yy0 + 300, "Bots ignore traps", black, grey, 1, 20);
    if (((x - x0 - 270) * (x - x0 - 270) + (y - yy0 - 300) * (y - yy0 - 300) <= 10 * 10) && dsp.button() == true) {
        if(smart_bot == true)	smart_bot = false;
        if (smart_bot == false)	smart_bot = true;
    }


    if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= 100 * 100) && dsp.button()==true) {
        clr = 1;
        start = true;
    }
    if ((x - x0 +q) * (x - x0+q) + (y - yy0) * (y - yy0) <= 100 * 100 && dsp.button() == true ) {
        clr = 2;
        start = true;
    }
    if ((x - x0 - q) * (x - x0 - q) + (y - yy0) * (y - yy0) <= 100 * 100 && dsp.button()==true) {
        clr = 0;
        start = true;
    }
    if(smart_bot==false)	img.draw_circle(x0 + 270, yy0 + 300, 10, green);
    else	img.draw_circle(x0 + 270, yy0 + 300, 10, red);


}



bool StartMenu :: what_bots() const
{
    return this->smart_bot;
}

bool StartMenu :: is_open() const
{
    return start;
}

int StartMenu :: what_colour() const
{
    return this->clr;
}


