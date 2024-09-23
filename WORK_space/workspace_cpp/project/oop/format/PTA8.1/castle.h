#ifndef _CASTLE_H_
#define _CASTLE_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "castle.h"
using namespace std;

class castle
{
private:
    int  room[5][5];
    int x , y;

    struct princess
    {
        /* data */
        int x,y;
    }prin;
    
    struct monster
    {
        /* data */
        int x,y;
    }mon;
    
    string commmand;
public:
    void init();
    void set(int &x1, int &y1 , int &x2 , int &y2);
    void judge(int x,int y);
    int whether_safe(int num);
    void commmand_analy();
    void isprincess(int posx,int posy);
    void ismonster(int posx,int posy);
    void commmand_two();
    void game_cout(int posx , int posy);
    void game_print(int posx,int posy);
    void newstart();

};


#endif