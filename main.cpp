#include <iostream>
#include "Cimg.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "constances.h"
#include "start_menu.h"
#include "PlayerInterface.h"
#include "traps.h"
#include "point.h"
#include "Player.h"
#include "bot.h"
#include <cmath>
#include "Gameplay.h"
using namespace std;
using namespace cimg_library;
//int speed = 2;



/*struct bot {
	int bx;
	int bvx;
	int by;
	int bvy;
	int bR;
	int bcolour;
	int bpoint;
	int bdistance;
	bool alive;
};*/



int generate(int a, int b, int o, int rad) {
	srand(time(0));
	int vol;
	vol = a+ rand() % (b - a + 1);
	if (abs(vol - a) <= 2 * rad) {
		generate(a, b, o, rad);
	}
	else	return vol;
}


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
    //GamePlay game_play;
    //game_play.MainProcess();
	/* ::ShowWindow(::GetConsoleWindow(), SW_HIDE);



	const unsigned char* pcolours[colour];
	for (int i = 0; i < colour; i++) {
		pcolours[i] = &colours[i][0];
	}

	const unsigned char* bots_pcolours[colour];
	for (int i = 0; i < colour; i++) {
		bots_pcolours[i] = &bot_colours[i][0];
	}


	int xb=0, yb=0, x=0, y=0, index = 0;                                            // useful symbols
    int  R = 20;                                                            // parametrs

	int rmin = 10000, trap_lenght = 100;



	bool start = false;
	bool smart_bot = false;
	int c = 1;																// colour of player
	//int line[4] = { -Xm/2,Xm/2,-Ym/2,Ym/2 }; // x1,x2,y1,y2
	srand(time(0));

    Field pole;
    vector<point> points;
    points.reserve(n);
    for(int i = 0; i < n; i++)
    {
        point new_point(0,0,i);
        new_point.random_generate(pole);
        points.push_back(new_point);
    }

	/*int points[n][3];
	for (int i = 0; i < n; i++) {
		points[i][1] = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
		points[i][2] = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
	}*/

    /*
	bot bots[nb];
	for (int i = 0; i < nb; i++) {
		bots[i].bx = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
		bots[i].by = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
		bots[i].bvx = 0;
		bots[i].bvy = 0;
		bots[i].bR = 20;
		bots[i].alive = true;
		bots[i].bcolour = i % colour;
		bots[i].bpoint = 0;
		bots[i].bdistance = rmin;
	}

    vector<bot> bots;
    for(int i = 0; i < nb; i++)
    {
        bot new_bot(0,0,i);
        new_bot.random_generate(pole);
        bots.push_back(new_bot);
    }

	srand(time(0) + 100);

    vector<trap> traps;
    traps.reserve(nt);
	for (int i = 0; i < nt; i++)
	{
        trap n_trap(0,0);
        n_trap.random_generate(pole);
        traps.push_back(n_trap);
	}


	CImg<unsigned char> bg(D, H, 1, 3, 255);
	bg.draw_rectangle(0, 0, D, H, grey);
	CImgDisplay dsp(D, H, "Agar.io", 0);
	dsp.display(bg);
	CImg<unsigned char> img(bg);


	StartMenu start_menu;
	//////////////////////////////////////start menu///////////////////////////////////
	while (start_menu.is_open() == false) {
        x = dsp.mouse_x();
        y = dsp.mouse_y();
	    img = bg;
	    start_menu.process(x, y, img, dsp);
	    smart_bot = start_menu.what_bots();
	    c = start_menu.what_colour();
		dsp.display(img);
	}


	int  vx, vy, z = 500;
	float k = 2, k1x = 2, k1y = 2;
	Player user_name(c);

///////////////////////////////////////////// MAIN BODY//////////////////////////////////////////////////////
	while (!dsp.is_closed()) {
		img = bg;
		R = user_name.getSize();
		if (dsp.mouse_x() - D/2 < user_name.getSize() && dsp.mouse_y() - H/2 < R) {
			k1x = kof(R)* speed_of(dsp.mouse_x(), R, D);
			k1y = kof(R)* speed_of(dsp.mouse_y(), R, H);
		}
		else {
			k1x = kof(R);
			k1y = kof(R);
		}

		if (dsp.mouse_x() >= D / 2)	vx =  -1* speed * k1x;
		else    vx =  speed * k1x;
		if (dsp.mouse_y() >= H / 2)	vy = -1 * speed * k1y;
		else    vy = speed* k1y;



		// GRANICI POLUA
		if (x0 + R >= pole.getx1() && x0 + R >= pole.getx2() && vx<=0 )		vx *= -1;
		if (x0 - R <= pole.getx1() && x0 - R <= pole.getx2() && vx>=0)		vx *= -1;
		if (yy0 + R >= pole.gety1() && yy0 + R >= pole.gety2() && vy <= 0)		vy *= -1;
		if (yy0 - R <= pole.gety1() && yy0 - R <= pole.gety2() && vy >= 0)		vy *= -1;
		//line[0] += vx;	line[1] += vx;	line[2] += vy, line[3] += vy;
        pole.Animate(vx, vy);


		// ANIMATION OF POINTS
		for (int i = 0; i <n; i++) {
		    points[i].Animate(vx, vy);
			//points[i][1] += vx; points[i][2] += vy;
			x = points[i].getX(), y = points[i].getY();
			points[i].draw(img);
			//img.draw_circle(x, y, 10, colours[i%colour]);

			if ((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= R * R) {
				user_name.changeMass(1);
                R = user_name.getSize();

				points[i].random_generate(pole);
			}
            x = points[i].getX(), y = points[i].getY();

			for (int j = 0; j < nb; j++) {
				if (bots[j].isAlive() == true) {
					xb = bots[j].getX(), yb = bots[j].getY();
					if ((x - xb) * (x - xb) + (y - yb) * (y - yb) <= pow(bots[j].getSize(),2)) {
						bots[j].changeMass(1);

						points[i].random_generate(pole);
					}
					int lon = distance(xb, yb, x, y);
					if (lon <= bots[j].getDist()) {
						bots[j].setPoint(i);
						bots[j].setDist(lon);
					}


				}
			}
		}


		// BOTS ANIMATION
		for (int i = 0; i < nb; i++) {
			if (bots[i].isAlive() == true) {
				index = bots[i].getPoint();
				x = bots[i].getX(), y = bots[i].getY();
				k = kof(bots[i].getSize());
				if (x >= points[index].getX()) {
					if (x == points[index].getX())	bots[i].setVx(0);
					else	bots[i].setVx(-1* speed * k);

				}
				else {
					bots[i].setVx(speed * k);
				}


				if (y >= points[index].getY()) {
					if (y == points[index].getY())	bots[i].setVy(0);
					else	bots[i].setVy(-1* speed * k);

				}
				else {
					bots[i].setVy(speed * k);
				}

				//bots[i].bx += vx + bots[i].bvx; bots[i].by += vy + bots[i].bvy;
				bots[i].Animate(vx, vy);
				x = bots[i].getX(), y = bots[i].getY();

				if ((x - points[index].getX()) * (x - points[index].getX()) + (y - points[index].getY()) * (y - points[index].getY()) <= pow(bots[i].getSize(),2)) {
					bots[i].changeMass(mass / bots[i].getSize());

					points[index].random_generate(pole);
				}

				//img.draw_circle(x, y, bots[i].bR, bots_pcolours[bots[i].bcolour]);
				bots[i].draw(img);

				if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= R * R) && R > bots[i].getSize()) {
					user_name.changeMass(bots[i].getSize());
					R = user_name.getSize();
					bots[i].setMass(0);
					bots[i].killBot();
				}
				if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= pow(bots[i].getSize(),2)) && R < bots[i].getSize()) {
					bots[i].changeMass(R);
					user_name.setMass(10);
					R = user_name.getSize();
				}
				for (int j = i + 1; j < nb; j++) {
					if (bots[j].isAlive() == true) {
						if (((x - bots[j].getX()) * (x - bots[j].getX()) + (y - bots[j].getY()) * (y - bots[j].getY()) <= bots[i].getSize() * bots[i].getSize()) && bots[i].getSize() >bots[j].getSize()) {
							bots[i].changeMass(bots[j].getSize());
							bots[j].killBot();
						}
						if (((x - bots[j].getX()) * (x - bots[j].getX()) + (y - bots[j].getY()) * (y - bots[j].getY()) <= bots[j].getSize() * bots[j].getSize()) && bots[j].getSize() > bots[i].getSize()) {
							bots[j].changeMass(bots[i].getSize());
							bots[i].killBot();
						}
					}

				}
			}
			//img.draw_text(x - 15, y - 10, "I'm bot", black);
		}

		//TRAPS ANIMATION
		for (int i = 0; i < nt; i++) {
		    traps[i].Animate(vx, vy);
			//traps[i][1] += vx; traps[i][2] += vy;
			x = traps[i].getX(), y = traps[i].getY();
			traps[i].draw(img);

			if ((x + trap_lenght/2 - x0) * (x + trap_lenght/2 - x0) + (y - trap_lenght/2 - yy0) * (y - trap_lenght/2 - yy0) <= R*R) {
                user_name.setMass(R/2);
                R = user_name.getSize();

				traps[i].random_generate(pole);
			}
			if (smart_bot == true) {
				for (int j = 0; j < nb; j++) {
					xb = bots[j].getX();
					yb = bots[j].getY();
					if ((x + trap_lenght / 2 - xb) * (x + trap_lenght / 2 - xb) + (y - trap_lenght / 2 - yb) * (y - trap_lenght / 2 - yb) <= bots[j].getSize()* bots[j].getSize()) {
						bots[j].setMass(bots[j].getSize() / 2);
						if (bots[j].getSize() < 20) 	bots[j].killBot();
						traps[i].random_generate(pole);
					}
				}
			}

		}


		/* DRAW LINES
        pole.draw(img);


		user_name.draw(img);
		dsp.display(img);

		if (R < 20) {
			while (!dsp.button() && 1) {
				dsp.display(img);
				img.draw_text(x0 - 200, yy0 - 100, "YOU LOSE", white, black , 1, 100);
			}
			exit(0);
		}
	}*/
}



