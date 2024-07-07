#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "allOfUsers/user.h"
#include "allOfUsers/customerAtLobby.h"
#include "allOfUsers/customerAtTable.h"
#include <ncurses.h>
int main(int argc, char **args)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(2000);

    /*
    coolOutput("booting...\n");
    waitThisLong(4);
    */
    int choice = -1;

    User *test;
    bool firstTime = true;


    
    while (choice != 54)
    {
        if (firstTime)
            firstTime = false;
        else
        {
            coolOutput("restarting...\n");
            waitThisLong(4);
        }
        timeout(60000);
        choice = getch();

        switch (choice)
        {
        case 49: // 1
            
            coolOutput("\n\rstarting tablet at entrance... ");
            //waitThisLong(2);
            coolOutputNoClear("\n\rstarting in ");
            for (int i = 3; i >= 1; i--)
            {
                coolOutputNoClear(std::to_string(i));
                coolOutputNoClear(" ");
                //waitThisLong(1);
            }
            test = new CustomerAtLobby();
            // endwin();
            test->run();
            delete test;
            test = nullptr;
            clear();
            break;
        case 50: // 2
            test = new CustomerAtTable();
            test->run();
            delete test;
            test = nullptr;
            break;
        case 51: // 3
            break;
        case 52: // 4
            break;
        case 53: // 5
            break;
        case 54: // 6
            continue;
        default:
            break;
        }

        
    }

    endwin();

    if(test != nullptr)
        delete test;
    

    return 0;
}