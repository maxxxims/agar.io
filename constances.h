//
// Created by 7996832 on 30.04.2021.
//

#ifndef AGARIO_V2_CONSTANCES_H
#define AGARIO_V2_CONSTANCES_H

const int colour = 3; // number of colours don't change
const int n = 500; // number of points
const int nt = 10; // number of traps
const int nb = 7; // number of bots


const int D = 1600, H = 800, mass = 200;                     // size of area

const int yy0 = H / 2;
const int x0 = D / 2;
const int Xm = D * 4;
const int Ym = H * 4;         //parameters

const unsigned char black[] = { 0,0,0 };
const unsigned char white[] = { 255,255,255 };
const unsigned char red[] = { 255,20,20 };
const unsigned char grey[] = { 230,230,230 };
const  unsigned char blue[] = { 0,0,255 };
const  unsigned char green[] = { 6, 255, 6 };
const  unsigned char colours[colour][3] = { { 255,20,20 }, { 0,0,255 }, { 6, 255, 6 } };
const  unsigned char bot_colours[colour][3] = { { 255,138,0 }, { 0,255,255 }, { 255, 0, 255 } };
//const unsigned char *pcolours[colour] = {&colours[0][0], &colours[1][0], &colours[2][0]};



#endif //AGARIO_V2_CONSTANCES_H
