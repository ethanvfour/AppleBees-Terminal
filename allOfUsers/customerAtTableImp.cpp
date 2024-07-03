#include "customerAtTable.h"
#include <filesystem>
#include <fstream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "../outsideFunctions/coolFunctions.h"

template <class T>
node<T>::node()
{
    next = nullptr;
}

template <class T>
node<T>::node(T data)
{
    this->data = data;
    next = nullptr;
}

LinkedListItems::LinkedListItems()
{
    head = nullptr;
    count = 0;
}

LinkedListItems::LinkedListItems(Item data)
{
    head = new node<Item>(data);
    count = 1;
}

void LinkedListItems::add(Item data)
{
    if (head == nullptr)
    {
        head = new node<Item>(data);
    }
    else
    {
        node<Item> *goer = head;
        while (goer->next != nullptr)
        {
            goer = goer->next;
        }
        goer->next = new node<Item>(data);
    }
    count++;
}

int LinkedListItems::getCount()
{
    return count;
}

node<Item> *LinkedListItems::getNode(int index)
{
    if (index < 0 || index >= count)
    {
        return nullptr;
    }
    node<Item> *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

LinkedListItems::~LinkedListItems()
{
    while (head != nullptr)
    {
        node<Item> *temp = head;
        head = head->next;
        delete temp;
    }
}

double CustomerAtTable::getBill()
{
    double total = 0;
    for (int i = 0; i < items.getCount(); i++)
    {
        total += items.getNode(i)->data.getPrice();
    }
    return total;
}

void CustomerAtTable::initizalizeTable(int tableNum)
{
    std::filesystem::path path = "../dataBase/tablesInfoSL.txt";

    while (std::filesystem::exists(path))
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/tablesInfoSL.txt"); // spinlock

    std::ifstream openDb("../dataBase/tablesInfo.txt");

    bool foundTable = false;
    std::string temp = "";
    while (!foundTable && !openDb.eof())
    {
        int possTableNum = 0;
        bool isOccupied = false;
        int numOfPeople = 0;
        bool isCleaned = false;
        getline(openDb, temp);
        decryptString(&temp[0], temp.length());
        possTableNum = std::stoi(temp.substr(1, temp.find('\"') - 1));
        if (tableNum == possTableNum)
        {
            foundTable = true;
            temp = temp.substr(temp.find('\"', 2) + 2, temp.length());
            if (temp.substr(1, temp.find('\"') - 1) == "true")
            {
                isOccupied = true;
            }
            else
            {
                isOccupied = false;
            }
            temp = temp.substr(temp.find('\"', 2) + 2, temp.length());

            numOfPeople = std::stoi(temp.substr(1, temp.find('\"') - 1));

            temp = temp.substr(temp.find('\"', 2) + 2, temp.length());

            if (temp.substr(1, temp.find('\"') - 1) == "true")
            {
                isCleaned = true;
            }
            else
            {
                isCleaned = false;
            }
            thisTable = Table(possTableNum, isOccupied, numOfPeople, isCleaned);
        }
    }
    if (!foundTable)
    {
        std::cerr << "Table not found" << std::endl;
        exit(-1);
    }
    openDb.close();
    std::filesystem::remove(path);
}

CustomerAtTable::CustomerAtTable()
{
    title = "customer";
    thisTable = Table(); // should not be called ?
    items = LinkedListItems();
}

CustomerAtTable::CustomerAtTable(int tableNum)
{
    title = "customer";
    initizalizeTable(tableNum);
    items = LinkedListItems();
}

void CustomerAtTable::run()
{
    endwin();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();
    noecho();
    timeout(1);
    getch(); // done for something weird going on

    int uChoice = -1;
    bool weDone = false, firstTime = true;

    int whichAdToPlay = 1; // there will be three ads
    while (!weDone)
    {
        if (firstTime)
        {
            firstTime = false;
            uChoice = ERR;
        }
        else
        {
            timeout(10000);
            uChoice = getch();
        }

        if (uChoice == ERR)
        {
            if (whichAdToPlay == 1)
            {
                clear();
                std::string message1 = "TRY OUT NEW DELICIOUS BURGER MEAL!";
                std::string message2 = "ONLY FOR $11.99!";
                move(1, 0);
                printw("*****************************************************************************************************");

                move(8, (101 / 2) - message1.length() / 2);
                printw("%s", message1.c_str());

                move(12, (101 / 2) - message2.length() / 2);
                printw("%s", message2.c_str());

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();
                whichAdToPlay++;
            }
            else if (whichAdToPlay == 2)
            {
                clear();
                std::string message1 = "HAPPY HOUR STARTS AFTER 5PM AND ENDS AT 7PM EVERYDAY!";
                std::string message2 = "CHECK OUT THE HAPPY HOUR MENU!";
                move(1, 0);
                printw("*****************************************************************************************************");

                move(8, (101 / 2) - message1.length() / 2);
                printw("%s", message1.c_str());

                move(12, (101 / 2) - message2.length() / 2);
                printw("%s", message2.c_str());

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();
                whichAdToPlay++;
            }
            else if (whichAdToPlay == 3)
            {
                clear();
                std::string message1 = "THIS SATURDAY, ENJOY A FREE DESSERT WITH ANY MEAL!";
                std::string message2 = "TALK TO YOUR SERVER FOR MORE DETAILS!";
                move(1, 0);
                printw("*****************************************************************************************************");

                move(8, (101 / 2) - message1.length() / 2);
                printw("%s", message1.c_str());

                move(12, (101 / 2) - message2.length() / 2);
                printw("%s", message2.c_str());

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();
                whichAdToPlay++;
            }
            else
            {
                clear();
                std::string message1 = "WHO WANTS PANCAKES?!? PANCAKES ARE NOW ON THE MENU!";
                std::string message2 = "ONLY AVAILABLE DURING 12PM TO 2PM!";
                move(1, 0);
                printw("*****************************************************************************************************");

                move(8, (101 / 2) - message1.length() / 2);
                printw("%s", message1.c_str());

                move(12, (101 / 2) - message2.length() / 2);
                printw("%s", message2.c_str());

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();
                whichAdToPlay = 1;
            }
        }
        else // meaning user clicked something
        {
             
        }
    }

    clear();
    echo();
}