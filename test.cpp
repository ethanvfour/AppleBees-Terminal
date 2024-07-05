#include <iostream>
#include <queue>
#include <filesystem> //gonna be used to open db and see if another executable is currenly opening
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "outsideFunctions/coolFunctions.h"
using namespace std;

void waitThisLong(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(x));
}

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    timeout(-1);

    printw("Put something in me :)");
    move(0, 0);
    refresh();
    echo();
    char str[80];
    getstr(str);
    std::string j(str);
    clear();
    move(2,0);
    printw("You entered: %s", str);
    refresh();

    waitThisLong(2);

    echo();
    endwin();
}