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
#include<process.h>
#include<windows.h>
#endif

#define author joe1256joe
#define title monster_farm

using namespace std;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int GAME_STATE_NOW=1;
//

int choice(int sx,int sy,int e,int step=2);
int digit(int x);
int experience(int);

void printstat (int y,int x,int nownum,int maxnum,short);

void init();
#ifdef MUSIC
void music();
#endif

class Monster
{
public:
    int maxhp()
    {
        return basehp+strength*5;
    }
    int maxmp()
    {
        return basemp+intelligence*2;
    }
    int nextexp()
    {
        return level*level*10;
    }
    //set
    Monster& exp_increase(int i)
    {
        nowexp+=i;
        if(nowexp >= this->nextexp())
        {
            nowexp-=this->nextexp();
            level++;
        }
        return *this;
    }
    Monster& hp_increase(int i)
    {
        nowhp+=i;
        return *this;
    }
    Monster& hp_recover()
    {
        nowhp=this->maxhp();
        return *this;
    }
    Monster& mp_increase(int i)
    {
        nowmp+=i;
        return *this;
    }
    Monster& mp_recover()
    {
        nowmp=this->maxmp();
        return *this;
    }
    Monster& readname(char x[])
    {
        strcpy(name,x);
        return *this;
    }
private:
    char name[50];
    int strength=10;
    int agility=10;
    int intelligence=10;
    int level=1;
    int nowexp=0;
    int nowhp=10,basehp=10;
    int nowmp=10,basemp=10;
    int equipment[10];
};

class panel
{
private:
    int height;
    int width;
    int startx;
    int starty;
    int endx;
    int endy;
public:
    panel(int sx=0,int sy=0,int ex=0,int ey=0):startx(sx),starty(sy),endx(ex),endy(ey)
                                      ,width(ex-sx),height(ey-sy){}

    void midprintw(char* x,int y)
    {
        mvprintw(y,(width-strlen(x))/2,x);
    }
    void drawpanel()
    {
        for(int i=startx;i<=endx;i++)
            mvaddch(starty,i,'-');
        for(int i=startx;i<=endx;i++)
            mvaddch(endy,i,'-');
        for(int i=starty;i<=endy;i++)
            mvaddch(i,startx,'|');
        for(int i=starty;i<=endy;i++)
            mvaddch(i,endx,'|');
        mvaddch(starty,startx,'#');
        mvaddch(endy,startx,'#');
        mvaddch(starty,endx,'#');
        mvaddch(endy,endx,'#');
        refresh();
    }

};


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
/*
struct panel
{
    int height;
    int width;
    int startx;
    int starty;
    int endx;
    int endy;
};*/

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


#ifdef MUSIC
void music(void*)
{
    while(1)
    {
        Beep(220,100);

        Beep(440,100);

        Beep(880,100);
    }
}
#endif//MUSIC
#endif // MONSTERFARM_H_INCLUDED
