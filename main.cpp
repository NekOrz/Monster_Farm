#include"MonsterFarm.h"
monster mymonster;

int main()
{
#ifdef MUSIC
    _beginthread(music,0,NULL);
#endif // MUSIC

    //GAME_STATE_NOW=GAME_MAIN;
    init();
    panel entire(0,0,SCREEN_WIDTH-1,SCREEN_HEIGHT-2);
    panel moninfo(0,0,30,15);
    panel pic = {30,0,SCREEN_WIDTH-1,15};
    //int i=0;
    while(1){
        bool ex=0;

        //title
        if(GAME_STATE_NOW==GAME_TITLE)
        { //ok for now
            entire.midprintw("   /|   /|                                   ",2);
            entire.midprintw("  / |  / |   ____  ____  ____  _/_  __    __ ",3);
            entire.midprintw(" /  | /  |  /   / /   / /___   /   /__\\  /  \\",4);
            entire.midprintw("/   |/   | /___/ /   / ____/  /_/  \\__  /    ",5);
            entire.midprintw("    ______                 ",6);
            entire.midprintw("   /                      ",7);
            entire.midprintw("  /___   ___    __    ____",8);
            entire.midprintw(" /      /  /|  /  \\  / / /",9);
            entire.midprintw("/      /__/ | /     / / / ",10);
            entire.midprintw("Welcome to monster farm!",11);
            entire.midprintw("New game ",13);
            entire.midprintw("Load game",15);
            entire.midprintw("Help     ",17);
            entire.midprintw("Exit     ",19);
            refresh();
            switch (choice(30,13,19,2))
            {
            case 13:
                GAME_STATE_NOW = GAME_NEW; break;
            case 15:
                GAME_STATE_NOW = GAME_LOAD; break;
            case 17:
                GAME_STATE_NOW = GAME_HELP; break;
            case 19:
                ex = 1; break;
            default:
                break;
            }
        }
        //new game
        else if(GAME_STATE_NOW==GAME_NEW)
        { //TODO still need complement about the intro info
            entire.midprintw("In this world, there are many different kinds of monsters...",SCREEN_HEIGHT/2-2);
            refresh();
            while(getch()==ERR);
            erase();
            entire.midprintw("They are strong, but not very wise in the beginning.",SCREEN_HEIGHT/2-2);
            entire.midprintw("Bad guys may take advantage of them, and commit crimes.",SCREEN_HEIGHT/2);
            refresh();
            while(getch()==ERR);
            erase();
            entire.midprintw("So it's your job to direct them to justice.",SCREEN_HEIGHT/2-2);
            refresh();
            while(getch()==ERR);
            erase();
            mvprintw(2,5,"Please enter your monster's name:");
            curs_set(1);
            echo();
            refresh();

            char *k = new char[50];
            getstr(k);
            mymonster.name.assign(k);
            delete [] k;

            curs_set(0);
            noecho();
            mvprintw(6,5,"Strength(S)");
            mvprintw(8,5,"Agility(A)");
            mvprintw(10,5,"Intelligence(I)");
            mvprintw(4,5,"What main attribute does your monster have?");
            switch (choice(3,6,10,2))
            {
            case 6:
                mymonster.main_attribute='S';
                mymonster.strength+=5;
                break;
            case 8:
                mymonster.main_attribute='A';
                mymonster.agility+=5;
                break;
            case 10:
                mymonster.main_attribute='I';
                mymonster.intelligence+=5;
                break;
            default:
                break;
            }

            GAME_STATE_NOW = GAME_MAIN;
        }

        //load
        else if(GAME_STATE_NOW==GAME_LOAD)
        { //shouldn't reset 'o'  or i don't give a fuck
            FILE* input;
            entire.midprintw("LOAD MENU",2);
            //5 7 9 11 13 15 17 19 21 23
            //1 2 3 4  5  6  7  8  9  0
            char save[]="save0.sav";
            for(int i=0;i<=9;i++)
            {
                save[4]='0'+i;
                if((input=fopen(save,"r")))
                {
                    char *n = new char[50];
                    fscanf(input,"%s",n);
                    mvprintw(4+i*2,5,"%d: %s",i,n);
                    delete [] n;
                    fclose(input);
                }
                else
                    mvprintw(4+i*2,5,"%d: no save data.",i);
            }
            do
            {
                save[4]='0'+(choice(3,4,22,2)-4)/2;
                input = fopen(save,"r");
            }
            while(input==NULL);
            char buf[50];
            fscanf(input,"%s %d %d %d %d %d %d %d %d %d"
                   ,buf
                   ,&mymonster.strength
                   ,&mymonster.agility
                   ,&mymonster.intelligence
                   ,&mymonster.level
                   ,&mymonster.exp
                   ,&mymonster.hp,&mymonster.maxhp
                   ,&mymonster.mp,&mymonster.maxmp);
            mymonster.name.assign(buf);
            fclose(input);
            GAME_STATE_NOW=GAME_MAIN;

        }

        //help
        else if(GAME_STATE_NOW==GAME_HELP)
        { //that doesn't help.
            entire.midprintw("Help!",2);
            mvprintw(4,5,"Author: joe1256joe");
            mvprintw(6,5,"Use Space to select and Esc to go back");
            entire.midprintw("Press Any Key to Continue...",SCREEN_HEIGHT-3);
            while(getch()==ERR);
            GAME_STATE_NOW = GAME_TITLE;
        }

        //main
        else if (GAME_STATE_NOW == GAME_MAIN)
        { //need a looooooooot of improvement
            entire.drawpanel();
            moninfo.drawpanel();
            pic.drawpanel();
            mvprintw(1,1,"Name:%s",mymonster.name.c_str());
            mvprintw(2,1,"Lv  :%d",mymonster.level);
            mvprintw(3,1,"Exp :"); printstat(3,6,mymonster.exp,mymonster.level*mymonster.level*5+10,22,EXP_COLOR);
            mvprintw(4,1,"HP  :"); printstat(4,6,mymonster.hp,mymonster.maxhp,22,HP_COLOR);
            mvprintw(5,1,"MP  :"); printstat(5,6,mymonster.mp,mymonster.maxmp,22,MP_COLOR);
            mvprintw(6,1,"STR :%d",mymonster.strength);
            mvprintw(7,1,"INT :%d",mymonster.intelligence);
            mvprintw(8,1,"AGI :%d",mymonster.agility);
            //

            //



            refresh();
            napms(5000);
        }
        erase();
        if(ex)
            break;
    }
    clear();
    entire.midprintw("Good bye! Have a nice day!",SCREEN_HEIGHT/2);
    endwin();
    return 0;
}
