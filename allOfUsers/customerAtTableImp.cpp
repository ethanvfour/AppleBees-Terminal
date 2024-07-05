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

void LinkedListItems::clearList()
{
    while (head != nullptr)
    {
        node<Item> *temp = head;
        head = head->next;
        delete temp;
    }
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

void CustomerAtTable::addItem()
{
}

void CustomerAtTable::refreshItems()
{
    std::filesystem::path path;
    std::string filename = "";
    filename += "table" + std::to_string(thisTable.getTableNum()) + "ItemsSL.txt";
    std::string directory = "../dataBase/tableOrders/";
    directory.append(filename);
    path = directory;

    while (std::filesystem::exists(path))
    {
        // keep waiting till gone
    }

    std::ofstream makingSL(directory); // makes spin lock

    items.clearList();

    std::string toTextFile = "../dataBase/tableOrders/";
    toTextFile += "table" + std::to_string(thisTable.getTableNum()) + "Items.txt";

    std::ifstream itemsInFile(toTextFile);

    std::string line = "";
    while (getline(itemsInFile, line))
    {
        decryptString(&line[0], line.length());
        std::string name = line.substr(1, line.find('\"') - 1);
        line = line.substr(line.find('\"', 2) + 2);
        double price = std::stod(line.substr(1, line.find('\"') - 1));
        line = line.substr(line.find('\"', 2) + 2);
        std::string description = line.substr(1, line.find('\"') - 1);
        items.add(Item(name, price, description));
    }

    std::filesystem::remove(path); // removes spin lock
}

void CustomerAtTable::orderFoodOption()
{
}

void CustomerAtTable::playGamesOption()
{
}

void CustomerAtTable::payBillOption()
{
    clear();
    refreshItems(); // refreshes the items just in case cuz why not lol lmao :3 :3 :3
    move(1, 0);
    printw("*****************************************************************************************************");
    for (int i = 0, movePoint = 10; i <= items.getCount(); i++, movePoint++)
    {
        if (i == items.getCount())
        {
            move(movePoint, 0);
            printw("TOTAL: ");
            move(movePoint, 30);
            printw("%s", std::to_string(getBill()).c_str());
        }
        else
        {
            move(movePoint, 0);
            printw("%s", items.getNode(i)->data.getName().c_str());
            move(movePoint, 30);
            printw("%s", std::to_string(items.getNode(i)->data.getPrice()).c_str());
        }
    }

    move(items.getCount() + 10, 0);
    printw("Pay now? (y/n)");

    move(items.getCount() + 12, 0);
    printw("*****************************************************************************************************");
    refresh();

    timeout(20000); // if not atfer 20 seconds, like come on now
    int uChoice = -1;

    while ((char)uChoice != 'y' && (char)uChoice != 'Y' && (char)uChoice != 'n' && (char)uChoice != 'N')
    {
        uChoice = getch();
        if (uChoice == ERR)
        {
            // just a timout
            break; // just get out
        }
        else if ((char)uChoice == 'y' || (char)uChoice == 'Y')
        {
            // then pay
            
            char buffer[100]; // temp buffer
            bool goodCreditCard = false;
            while (!goodCreditCard)
            {
                timeout(-1);      // set indefinite timeout
                clear();
                std::string message = "Please enter your credit card number: ";
                std::string message1 = "Please follow the format **** **** **** ****";
                clear();
                move(1, 0);
                printw("*****************************************************************************************************");

                move(20, 0);
                printw("*****************************************************************************************************");
                echo();
                move(10, (100 / 2) - message.length() / 2);
                printw("%s", message.c_str());
                move(11, (100 / 2) - message1.length() / 2);
                printw("%s", message1.c_str());

                move(12, 50 - 8); // this where they put the credit card num
                refresh();
                getstr(buffer);
                std::string creditCard(buffer);
                if (creditCard.length() != 19)
                {
                    clear();
                    move(1, 0);
                    printw("*****************************************************************************************************");
                    move(10, 50 - 14);
                    printw("Invalid credit card number.");
                    move(11, 50 - 8);
                    printw("Please try again.");
                    move(20, 0);
                    printw("*****************************************************************************************************");
                    refresh();
                    waitThisLong(2);
                }
                else
                {
                    bool goodCreditCard = true;
                    for (int i = 0; i < creditCard.length() && goodCreditCard; i++)
                    {
                        if (i == 4 || i == 9 || i == 14)
                        {
                            if (creditCard[i] != ' ')
                            {
                                goodCreditCard = false;
                            }
                        }
                        else
                        {
                            if (creditCard[i] < 0x30 || creditCard[i] > 0x39)
                            {
                                goodCreditCard = false;
                            }
                        }
                    }
                    if (!goodCreditCard)
                    {
                        clear();
                        move(1, 0);
                        printw("*****************************************************************************************************");
                        move(10, 50 - 14);
                        printw("Invalid credit card number.");
                        move(11, 50 - 8);
                        printw("Please try again.");
                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();
                        waitThisLong(2);
                    }
                    else
                    {
                        clear();
                        move(1, 0);
                        printw("*****************************************************************************************************");
                        move(10, 50 - 8);
                        printw("Please wait...");
                        
                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();
                        waitThisLong(2);


                        clear();
                        move(1, 0);
                        printw("*****************************************************************************************************");
                        move(10, 50 - 9);
                        printw("Payment succesful!");
                        
                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();
                        waitThisLong(2);


                        clear();
                        printw("*****************************************************************************************************");
                        move(10, 50 - 14);
                        printw("Thank you for dining with us!");
                        
                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();
                        waitThisLong(2);

                        resetTable = true;
                    }
                }
            }
        }
        else if ((char)uChoice == 'n' || (char)uChoice == 'N')
        {
            clear();
            move(1, 0);
            printw("*****************************************************************************************************");

            move(10, (100 / 2) - 8);
            printw("Payment stopped.");

            move(11, 50 - 10);
            printw("No payment was made.");

            move(20, 0);
            printw("*****************************************************************************************************");
            refresh();
            // dont do anything
            waitThisLong(2);
        }
        else
        {
            // ignore input?
        }
    }
}


void CustomerAtTable::clearTable()
{
    
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

    // now open a db/textfile for this table
    std::string filename = "";
    filename += "table" + std::to_string(thisTable.getTableNum()) + "Items.txt";

    std::string directory = "../dataBase/tableOrders/";
    directory.append(filename);

    std::ofstream makingDB(directory);
    makingDB.close();
}




/*
CHECK IF resetTable is true!!!!!!!!!!!
*/
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
    bool weDone = false, firstTime = true, goingBack = false;

    int whichAdToPlay = 1; // there will be three ads
    while (!weDone)
    {
        if(resetTable)
        {
            clearTable();
            /*
            FIGURE OUT WHAT TO DO HERE
            */

            resetTable = false;
        }

        if (firstTime || goingBack)
        {
            firstTime = false;
            goingBack = false;
            uChoice = ERR;
        }
        else
        {
            timeout(6600);
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
            clear();
            std::string order = "(1) ORDER"; // the three options
            std::string order1 = "ORDER FOOD HERE";

            std::string play = "(2) PLAY";
            std::string play1 = "PLAY GAMES HERE";

            std::string pay = "(3) PAY";
            std::string pay1 = "PAY HERE";

            move(1, 0);
            printw("*****************************************************************************************************");

            move(10, (33 / 2) - order.length() / 2);
            printw("%s", order.c_str());
            move(12, (33 / 2) - order1.length() / 2);
            printw("%s", order1.c_str());

            for (int i = 2; i <= 19; i++)
            {
                move(i, 33);
                printw("|");
            }

            move(10, (66 - (33 / 2)) - play.length() / 2);
            printw("%s", play.c_str());
            move(12, (66 - (33 / 2)) - play1.length() / 2);
            printw("%s", play1.c_str());

            for (int i = 2; i <= 19; i++)
            {
                move(i, 66);
                printw("|");
            }

            move(10, (99 - (33 / 2)) - pay.length() / 2);
            printw("%s", pay.c_str());
            move(12, (99 - (33 / 2)) - pay1.length() / 2);
            printw("%s", pay1.c_str());

            move(20, 0);
            printw("*****************************************************************************************************");
            refresh();

            timeout(20000); // if not atfer 20 seconds, like come on now
            uChoice = getch();

            if (uChoice == ERR)
            {
                // then exit this
            }
            else if (uChoice == 27)
            {
                weDone = true;
                echo();
            }
            else
            {
                if ((char)uChoice == '1')
                {
                    // order
                    orderFoodOption();
                    goingBack = true;
                }
                else if ((char)uChoice == '2')
                {
                    // play
                    playGamesOption();
                    goingBack = true;
                }
                else if ((char)uChoice == '3')
                {
                    // pay
                    payBillOption();
                    goingBack = true;
                }
                else
                {
                    // dont even do anything if not one of these choices
                }
            }
        }
    }

    clear();
    echo();
}

CustomerAtTable::~CustomerAtTable()
{
    if (thisTable.getTableNum() != 0)
    {
        std::filesystem::path pathSL;
        { // have it a temp thing, spinlock

            std::string filename = "";
            filename += "table" + std::to_string(thisTable.getTableNum()) + "ItemsSL.txt";
            std::string directory = "../dataBase/tableOrders/";
            directory.append(filename);
            pathSL = directory;

            while (std::filesystem::exists(pathSL))
            {
                // keep waiting till gone
            }

            std::ofstream makingSpinLock(directory);
        }

        std::string filename = "";
        filename += "table" + std::to_string(thisTable.getTableNum()) + "Items.txt";

        std::string directory = "../dataBase/tableOrders/";
        directory.append(filename);
        std::filesystem::path path = directory;
        std::filesystem::remove(path);   // remove the table
        std::filesystem::remove(pathSL); // remove the table
    }
}