#include <iostream>
#include <Windows.h>
#include "Cimg.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "constances.h"
#include "start_menu.h"
#include "PlayerInterface.h"
#include "field.h"
#include "traps.h"

using namespace std;
using namespace cimg_library;
int speed = 2;



struct bot {
	int bx;
	int bvx;
	int by;
	int bvy;
	int bR;
	int bcolour;
	int bpoint;
	int bdistance;
	bool alive;
};


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

int distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int generate(int a, int b, int o, int rad) {
	srand(time(0));
	int vol;
	vol = a+ rand() % (b - a + 1);
	if (abs(vol - a) <= 2 * rad) {
		generate(a, b, o, rad);
	}
	else	return vol;
}

float speed_of(unsigned int a, int rad, int L) {
	int sh = a - L / 2;
	if (sh < 0)	sh *= -1;
	if (sh<=100)		return 0.5;
	else	return 1;

}

int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);



	const unsigned char* pcolours[colour];
	for (int i = 0; i < colour; i++) {
		pcolours[i] = &colours[i][0];
	}

	const unsigned char* bots_pcolours[colour];
	for (int i = 0; i < colour; i++) {
		bots_pcolours[i] = &bot_colours[i][0];
	}


	int xb=0, yb=0, x, y, index;                                            // useful symbols
    int  R = 20;                                                            // parametrs
	int rmin = 10000, trap_lenght = 100;

	bool start = false;
	bool smart_bot = false;
	int c = 1;																// colour of player
	//int line[4] = { -Xm/2,Xm/2,-Ym/2,Ym/2 }; // x1,x2,y1,y2
	srand(time(0));

    Field pole;
	int points[n][3];
	for (int i = 0; i < n; i++) {
		points[i][1] = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
		points[i][2] = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
	}

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

///////////////////////////////////////////// MAIN BODY//////////////////////////////////////////////////////
	while (!dsp.is_closed()) {
		img = bg;

		if (dsp.mouse_x() - D/2 < R && dsp.mouse_y() - H/2 < R) {
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
			points[i][1] += vx; points[i][2] += vy;
			x = points[i][1], y = points[i][2];
			img.draw_circle(x, y, 10, pcolours[i%colour]);

			if ((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= R * R) {
				R += 1;


				points[i][1] = pole.getx1() + rand() % ( pole.getx2() - pole.getx1() + 1);
				points[i][2] = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
			}
			x = points[i][1], y = points[i][2];

			for (int j = 0; j < nb; j++) {
				if (bots[j].alive == true) {
					xb = bots[j].bx, yb = bots[j].by;
					if ((x - xb) * (x - xb) + (y - yb) * (y - yb) <= bots[j].bR * bots[j].bR) {
						bots[j].bR += 1;

						points[i][1] = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
						points[i][2] = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
					}
					int lon = distance(xb, yb, x, y);
					if (lon <= bots[j].bdistance) {
						bots[j].bpoint = i;
						bots[j].bdistance = lon;
					}


				}
			}
		}


		// BOTS ANIMATION
		for (int i = 0; i < nb; i++) {
			if (bots[i].alive == true) {
				index = bots[i].bpoint;
				x = bots[i].bx, y = bots[i].by;
				k = kof(bots[i].bR);
				if (x >= points[index][1]) {
					if (x == points[index][1])	bots[i].bvx = 0;
					else	bots[i].bvx = -1* speed * k;

				}
				else {
					bots[i].bvx = speed * k;
				}


				if (y >= points[index][2]) {
					if (y == points[index][2])	bots[i].bvy = 0;
					else	bots[i].bvy = -1* speed * k;

				}
				else {
					bots[i].bvy =  speed * k;
				}

				bots[i].bx += vx + bots[i].bvx; bots[i].by += vy + bots[i].bvy;
				x = bots[i].bx, y = bots[i].by;

				if ((x - points[index][1]) * (x - points[index][1]) + (y - points[index][2]) * (y - points[index][2]) <= bots[i].bR * bots[i].bR) {
					bots[i].bR += (mass / bots[i].bR);


					points[index][1] = pole.getx1() + rand() % (pole.getx2() - pole.getx1() + 1);
					points[index][2] = pole.gety1() + rand() % (pole.gety2() - pole.gety1() + 1);
				}

				img.draw_circle(x, y, bots[i].bR, bots_pcolours[bots[i].bcolour]);

				if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= R * R) && R > bots[i].bR) {
					R += bots[i].bR;
					bots[i].bR = 0;
					bots[i].alive = false;
				}
				if (((x - x0) * (x - x0) + (y - yy0) * (y - yy0) <= bots[i].bR * bots[i].bR) && R < bots[i].bR) {
					bots[i].bR += R;
					R = 10;
				}
				for (int j = i + 1; j < nb; j++) {
					if (bots[j].alive == true) {
						if (((x - bots[j].bx) * (x - bots[j].bx) + (y - bots[j].by) * (y - bots[j].by) <= bots[i].bR * bots[i].bR) && bots[i].bR >bots[j].bR) {
							bots[i].bR += bots[j].bR;
							bots[j].alive = false;
						}
						if (((x - bots[j].bx) * (x - bots[j].bx) + (y - bots[j].by) * (y - bots[j].by) <= bots[j].bR * bots[j].bR) && bots[j].bR > bots[i].bR) {
							bots[j].bR += bots[i].bR;
							bots[i].alive = false;
						}
					}

				}
			}
			img.draw_text(x - 15, y - 10, "I'm bot", black);
		}

		//TRAPS ANIMATION
		for (int i = 0; i < nt; i++) {
		    traps[i].Animate(vx, vy);
			//traps[i][1] += vx; traps[i][2] += vy;
			x = traps[i].getX(), y = traps[i].getY();
			traps[i].draw(img);

			if ((x + trap_lenght/2 - x0) * (x + trap_lenght/2 - x0) + (y - trap_lenght/2 - yy0) * (y - trap_lenght/2 - yy0) <= R*R) {
				R = R/2;

				traps[i].random_generate(pole);
			}
			if (smart_bot == true) {
				for (int j = 0; j < nb; j++) {
					xb = bots[j].bx;
					yb = bots[j].by;
					if ((x + trap_lenght / 2 - xb) * (x + trap_lenght / 2 - xb) + (y - trap_lenght / 2 - yb) * (y - trap_lenght / 2 - yb) <= bots[j].bR * bots[j].bR) {
						bots[j].bR = bots[j].bR / 2;
						if (bots[j].bR < 20)	bots[j].alive = false;
						traps[i].random_generate(pole);
					}
				}
			}

		}


		/* DRAW LINES
		img.draw_line(line[0], line[2], 0, line[1], line[2], 0, black);
		img.draw_line(line[0], line[3], 0, line[1], line[3], 0, black);
		img.draw_line(line[0], line[2], 0, line[0], line[3], 0, black );
		img.draw_line(line[1], line[2], 0, line[1], line[3], 0, black);*/

        pole.draw(img);


		img.draw_circle(x0, yy0, R, pcolours[c]);
		img.draw_text(x0-15, yy0 - 10, "Player", black);
		dsp.display(img);

		if (R < 20) {
			while (!dsp.button() && 1) {
				dsp.display(img);
				img.draw_text(x0 - 200, yy0 - 100, "YOU LOSE", white, black , 1, 100);
			}
			exit(0);
		}
	}
}



