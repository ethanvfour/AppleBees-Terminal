#include <iostream>
#include <queue>
#include <filesystem> //gonna be used to open db and see if another executable is currenly opening
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
//  #include "outsideFunctions/coolFunctions.h"
using namespace std;

int main()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    timeout(1000);
    while(getch() == ERR)
    {
        cout<<"\rWaiting for input\n"<<flush;
        //waitThisLong(4);
    }

    endwin();
}