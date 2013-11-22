#ifndef MONSTERFARM_H_INCLUDED
#define MONSTERFARM_H_INCLUDED
/*
   /|   /|
  / |  / |   ____  ____  ____  _/_  __    __
 /  | /  |  /   / /   / /___   /   /__\  /  \
/   |/   | /___/ /   / ____/  /_/  \__  /
    ______
   /
  /_____  ___    __    ____
 /       /  /|  /  \  / / /
/       /__/ | /     / / /
Monster
Farm
*/
#define NMUSIC

#include<curses.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<curses.h>

#ifdef MUSIC
#include<boost/thread.hpp>
#include<windows.h>
#endif

#define author joe1256joe
#define title monster_farm

using namespace std;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int GAME_STATE_NOW=1;
int choice(int sx,int sy,int e,int step);
int digit(int x);
int experience(int);
void wait();
void midprintw(string x,int y);
void printstat (int y,int x,int nownum,int maxnum,short);
void mybox(int,int,int,int);
void allscreen();
void init();
#ifdef MUSIC
void music();
#endif

struct monster
{
    string name="default_name";
    char main_attribute='S';
    int strength=10;
    int agility=10;
    int intelligence=10;
    int level=1;
    int exp=0;
    int hp=10,maxhp=10;
    int mp=10,maxmp=10;
};

struct panel
{
    int height;
    int width;
    int startx;
    int starty;
    int endx;
    int endy;
};

void init()
{
    initscr();
    start_color();
    getmaxyx(stdscr, SCREEN_HEIGHT,SCREEN_WIDTH);
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
    noecho();
    curs_set(0);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);
    init_pair(1,COLOR_WHITE,COLOR_RED);
    init_pair(2,COLOR_WHITE,COLOR_BLUE);
    init_pair(3,COLOR_WHITE,COLOR_YELLOW);
}

enum GAME_STATE
{
    GAME_DEFAULT,
    GAME_TITLE,
    GAME_NEW,
    GAME_LOAD,
    GAME_MAIN,
    GAME_HELP
};

enum CHARCOLOR
{
    DEFAULT_COLOR,
    HP_COLOR=1,
    MP_COLOR,
    EXP_COLOR
};

int choice(int sx,int sy,int e,int step)
{
    int dotx=sx,doty=sy;
    while(1)
    {
        mvprintw(doty,dotx,"o");
        int con = getch();
        if(con==KEY_UP && doty >sy)
        {
            mvprintw(doty,dotx," ");
            doty -= 2;
        }
        else if(con==KEY_DOWN && doty <e)
        {
            mvprintw(doty,dotx," ");
            doty += 2;
        }
        else if(con == ' ')
        {
            mvprintw(doty,dotx," ");
            return doty;
        }
    }
}
int digit(int x)
{
    if(x==0)
        return 1;
    int i=0;
    while(x>0)
        i++,x/=10;
    return i;
}
int experience(int lvl)
{
    return lvl*lvl*10;
}
void printstat(int y,int x,int nownum,int maxnum,int barwidth,short col)
{
    int bar = (nownum*barwidth)/maxnum;
    int halfbarw = barwidth/2;
    /*
    101234567890123456789
              /1226
    */
    mvaddch(y,x++,'[');
    for(int i=x;i<x+bar;i++)
        mvaddch(y,i,' '|COLOR_PAIR(col));
    mvaddch(y,x+barwidth,']');
    int d=digit(nownum);
    for(int i=x+halfbarw-1;i>=x+halfbarw-d;i--)
    {
        if(i>bar+x)
            mvaddch(y,i,((nownum%10)+48));
        else
            mvaddch(y,i,((nownum%10)+48)|COLOR_PAIR(col));
        nownum/=10;
    }
    if(halfbarw>bar)
        mvaddch(y,x+halfbarw,'/');
    else
        mvaddch(y,x+halfbarw,'/'|COLOR_PAIR(col));
    d=digit(maxnum);
    for(int i=x+halfbarw+d;i>=x+halfbarw+1;i--)
    {
        if(i>bar+x)
            mvaddch(y,i,((maxnum%10)+48));
        else
            mvaddch(y,i,((maxnum%10)+48)|COLOR_PAIR(col));
        maxnum/=10;
    }
}

void midprintw(string x,int y)
{
    mvprintw(y,(SCREEN_WIDTH-x.length())/2,x.c_str());
}
void drawpanel(panel a)
{
    for(int i=a.startx;i<=a.endx;i++)
        mvaddch(a.starty,i,'-');
    for(int i=a.startx;i<=a.endx;i++)
        mvaddch(a.endy,i,'-');
    for(int i=a.starty;i<=a.endy;i++)
        mvaddch(i,a.startx,'|');
    for(int i=a.starty;i<=a.endy;i++)
        mvaddch(i,a.endx,'|');
    mvaddch(a.starty,a.startx,'#');
    mvaddch(a.endy,a.startx,'#');
    mvaddch(a.starty,a.endx,'#');
    mvaddch(a.endy,a.endx,'#');
    refresh();
}
#ifdef MUSIC
void music()
{
    while(1)
    {
        Beep(220,1000);

        Beep(440,1000);

        Beep(880,1000);
    }
}
#endif//MUSIC
#endif // MONSTERFARM_H_INCLUDED
