#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "allOfUsers/user.h"
#include "allOfUsers/customerAtLobby.h"
#include <ncurses.h>
int main(int argc, char ** args)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(2000);


    int k = getch();
    
    endwin();
    std::cout<<(char)k<<std::endl;

    

    return 0;

}