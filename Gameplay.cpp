//
// Created by 7996832 on 07.05.2021.
//

#include "Gameplay.h"
#include<iostream>
using namespace std;

float kof(int rad) {
    float c=0;
    if (rad >= 20)		c = 3.8;
    if (rad >= 50)		c = 3.5;
    if (rad >= 100)		c = 3;
    if (rad >= 150)		c = 2.8;
    if (rad >= 200)		c = 2.5;
    if (rad >= 250)		c = 2;
    if (rad >= 300)		c = 1.8;
    if (rad >= 380)		c = 1.5;
    if (rad >= 500)		c = 1;
    if (rad >= 600)		c = 0.5;
    return c;
}

float speed_of(unsigned int a, int rad, int L) {
    int sh = a - L / 2;
    if (sh < 0)	sh *= -1;
    if (sh<=100)		return 0.5;
    else	return 1;

}

int distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


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

}

void GamePlay ::Init()
{
    bg.draw_rectangle(0, 0, D, H, grey);
    Field new_pole;
    pole = new_pole;
    counter = 0;
    //points init
    points.clear();
    for(int i = 0; i < n; i++)
    {
        point new_point(0,0,i);
        new_point.random_generate(pole);
        points.push_back(new_point);
    }

    // traps init
    traps.clear();
    for(int i = 0; i < nt; i++)
    {
        trap new_trap(0,0);
        new_trap.random_generate(pole);
        traps.push_back(new_trap);
    }

    // bots init
    bots.clear();
    for(int i = 0; i < nb; i ++)
    {
        bot new_bot(0,0,i);
        new_bot.random_generate(pole);
        bots.push_back(new_bot);
    }
}

void GamePlay ::startMenu_animation()
{
    int x, y;
    while (start_menu->is_open() == false && dsp.is_closed()==false) {
        x = dsp.mouse_x();
        y = dsp.mouse_y();
        img = bg;
        start_menu->process(x, y, img, dsp);
        draw();
    }

    k = 2, k1x = 2, k1y = 2;
    delete start_menu;

    start_menu = nullptr;
    setPlayerColour(c);
    user_name = new Player(c);
    Init();

}

void GamePlay :: point_animation()
{

        img = bg;
        pole.draw(img);
        for(auto it = points.begin(); it != points.end(); ++it)
        {
            if ((it->getX() - x0) * (it->getX() - x0) + (it->getY() - yy0) * (it->getY() - yy0) <= pow(user_name->getSize(), 2)) {
                user_name->changeMass(1);
                while(it->getSize() != 0)
                {
                    it->changeMass(-1);
                    it->Animate(0,0);
                    it->draw(img);
                }
                it->setMass(10);
                it->random_generate(pole);
            }

            for (auto bit = bots.begin(); bit != bots.end(); ++bit) {
                if (bit->isAlive() == true) {
                    int xb = bit->getX(), yb = bit->getY();
                    if (pow((it->getX() - xb),2) + pow((it->getY() - yb),2)  <= pow(bit->getSize(), 2)) {
                        bit->changeMass(1);

                        it->random_generate(pole);
                    }
                    int lon = distance(xb, yb, it->getX(), it->getY());
                    if (lon <= bit->getDist()) {
                        bit->setPoint(&(*it));
                        bit->setDist(lon);
                    }
                }
            }


            it->Animate(vx, vy);
            it->draw(img);

        }

}


void GamePlay :: player_animation()
{
    user_name->Animate(vx,vy);
    user_name->draw(img);
    if (user_name->getCurrentSize() < 20) {
        img.draw_text(x0 - 200, yy0 - 100, "YOU LOSE", white, black, 1, 100);
        img.draw_text(x0 - 250, yy0 - 300, "click here to back to start menu", white, black, 1, 40);
        while (dsp.button()==false) {
            dsp.display(img);
        }
        start_menu = new StartMenu;
        user_name->setMass(20);

    }
    //dsp.display(img);
}

void GamePlay :: bots_animation()
{
    for(auto it = bots.begin(); it != bots.end(); ++it) {
        int x,y;
        PlayerInterface *goal = it->getPoint();
        if (it->isAlive() == true) {
            x = it->getX(), y = it->getY();
            k = kof(it->getSize());
            if (x >= goal->getX()) {
                if (x == goal->getX()) it->setVx(0);
                else it->setVx(-1 * speed * k);

            } else {
                it->setVx(speed * k);
            }


            if (y >= goal->getY()) {
                if (y == goal->getY()) it->setVy(0);
                else it->setVy(-1 * speed * k);

            } else {
                it->setVy(speed * k);
            }


            if ((x - goal->getX()) * (x - goal->getX()) +
                (y - goal->getY()) * (y - goal->getY()) <= pow(it->getSize(), 2)) {
                it->changeMass(mass / it->getSize()); // ???????????????????????????
                goal->random_generate(pole);
            }

            if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= pow(user_name->getSize(), 2)) &&
                user_name->getSize() > it->getSize()) {
                user_name->changeMass(it->getSize());
                it->setMass(0);
                it->killBot();
            }
            if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= pow(it->getSize(), 2)) &&
                user_name->getSize() < it->getSize()) {
                it->changeMass(user_name->getSize());
                user_name->setMass(10);
            }
            auto nit = it;
            ++nit;
            if (nit != bots.end()) {
                for (auto it2 = nit; it2 != bots.end(); ++it2) {
                    if (it2->isAlive() == true) {
                        if (((x - it2->getX()) * (x -it2->getX()) +
                             (y - it2->getY()) * (y - it2->getY()) <=
                                it->getSize() * it->getSize()) && it->getSize() > it2->getSize()) {
                            it->changeMass(it2->getSize());
                            it2->killBot();
                        }
                        if (((x - it2->getX()) * (x - it2->getX()) +
                             (y - it2->getY()) * (y - it2->getY()) <=
                                it2->getSize() * it2->getSize()) && it2->getSize() > it->getSize()) {
                            it2->changeMass(it->getSize());
                            it->killBot();
                        }
                    }
                }
            }


            it->Animate(vx, vy);
            it->draw(img);
        }
        delete goal;
    }
}

void GamePlay :: traps_animation()
{
    int trap_lenght = traps.begin()->trap_lengt();
    for(auto it = traps.begin(); it != traps.end(); ++it)
    {

        if (pow((it->getX() + trap_lenght/2 - x0),2 ) + pow((it->getY() - trap_lenght/2 - yy0), 2) <= pow(user_name->getSize(), 2)) {
            user_name->setMass(user_name->getSize()/2);
            it->random_generate(pole);
        }

        for(auto bit = bots.begin(); bit != bots.end(); ++bit)
        {
            int xb = bit->getX();
            int yb = bit->getY();
            if (pow((it->getX() + trap_lenght / 2 - xb),2) + pow((it->getY() - trap_lenght / 2 - yb),2) <= bit->getSize()* bit->getSize())
            {
                bit->setMass(bit->getSize() / 2);
                if (bit->getSize() < 20) 	bit->killBot();
                it->random_generate(pole);
             }
        }
        it->Animate(vx, vy);
        it->draw(img);
    }
}

void GamePlay ::draw()
{
    manage_bots();
    dsp.display(img);
    img = bg;
}

void GamePlay ::manage_bots()
{
    int x = x0 + 660, y = yy0 - 300;
    for(auto it = bots.begin(); it != bots.end();)
    {
        if(it->isAlive() == false)
        {
            //bg.draw_text(x, y + 100*counter, "bot die", black, grey, 1, 20);
            bg.draw_text(x, y - 10 * counter, "bot die", black);
            counter++;
            auto nit = it;
            ++it;
            bots.erase(nit);
        }
        else
        {
            ++it;
        }
    }
}

void GamePlay::MainProcess()
{
    float k = 2, k1x = 2, k1y = 2;

    int R = user_name->getSize();
    if (dsp.mouse_x() - D/2 < user_name->getSize() && dsp.mouse_y() - H/2 < R) {
        k1x = kof(R)* speed_of(dsp.mouse_x(), R, D);
        k1y = kof(R)* speed_of(dsp.mouse_y(), R, H);
    }
    else {
        k1x = kof(R);
        k1y = kof(R);
    }

    if (dsp.mouse_x() >= D / 2)	vx =  -1* speed * k1x;
    else    this->vx =  speed * k1x;
    if (dsp.mouse_y() >= H / 2)	vy = -1 * speed * k1y;
    else    this->vy = speed* k1y;

    if (x0 + R >= pole.getx1() && x0 + R >= pole.getx2() && vx<=0 )		vx *= -1;
    if (x0 - R <= pole.getx1() && x0 - R <= pole.getx2() && vx>=0)		vx *= -1;
    if (yy0 + R >= pole.gety1() && yy0 + R >= pole.gety2() && vy <= 0)		vy *= -1;
    if (yy0 - R <= pole.gety1() && yy0 - R <= pole.gety2() && vy >= 0)		vy *= -1;

    pole.Animate(vx,vy);

}





void GamePlay :: setPlayerColour(int c)
{
    this->c = c;
}

void GamePlay :: setBotsBrain(bool f)
{
    this->smart_bot = f;
}

bool GamePlay :: isOpen() const
{
    return !(dsp.is_closed());
}

bool GamePlay :: isStartMenu() const
{
    if(start_menu != nullptr)   return true;
    return false;
}