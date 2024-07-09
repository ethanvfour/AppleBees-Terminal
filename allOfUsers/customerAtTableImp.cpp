#include "customerAtTable.h"
#include <filesystem>
#include <fstream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "../outsideFunctions/coolFunctions.h"
#include <sstream>
#include <vector>

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
    count = 0;
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

    std::string game = "1) Memory Game";
    std::string game1 = "2) Tic Tac Toe";
    std::string game2 = "Or press q to go back";
    clear();
    move(1, 0);
    printw("*****************************************************************************************************");

    move(5, 25 - game.length() / 2);
    printw("%s", game.c_str());

    for (int i = 2; i <= 9; i++)
    {
        move(i, 50);
        printw("|");
    }

    move(5, 75 - game1.length() / 2);
    printw("%s", game1.c_str());

    move(10, 0);
    printw("*****************************************************************************************************");

    move(15, 50 - (game2.length() / 2));
    printw("%s", game2.c_str());

    move(20, 0);
    printw("*****************************************************************************************************");
    refresh();

    timeout(20000); // if not atfer 20 seconds, like come on now
    int uChoice = -1;
    bool weDone = false;
    while (!weDone)
    {

        uChoice = getch();
        if (uChoice == ERR || (char)uChoice == 'q' || (char)uChoice == 'Q')
        {
            weDone = true;
            // timeout, go back to menu
        }
        else if ((char)uChoice == '1')
        {
            static int highScore = 0;
            std::string gameDescription = "Tap the correct arrow key as shown on scrren!";
            std::string gameDescription1 = "Are you ready? (press any button)";
            std::string gameDescription2 = "Press q at any time to end game";
            clear();
            move(1, 0);
            printw("*****************************************************************************************************");

            move(10, 50 - (game.substr(3).length() / 2));
            printw("%s", game.substr(3).c_str());
            move(11, 50 - (gameDescription.length() / 2));
            printw("%s", gameDescription.c_str());
            move(12, 50 - (gameDescription1.length() / 2));
            printw("%s", gameDescription1.c_str());
            move(13, 50 - (gameDescription2.length() / 2));
            printw("%s", gameDescription2.c_str());
            move(20, 0);
            printw("*****************************************************************************************************");
            refresh();

            timeout(-1);

            {
                int dummyInt = getch();
            }
            /*
            Notes section rq cuz lmaoo why not lmaoo

            int ch;
            printw("Press an arrow key (left, right, up, down) or q to quit: ");
            while((ch = getch()) != 'q') {
                switch(ch) {
                    case KEY_LEFT:
                        printw("Left Arrow\n");
                        break;
                    case KEY_RIGHT:
                        printw("Right Arrow\n");
                        break;
                    case KEY_UP:
                        printw("Up Arrow\n");
                        break;
                    case KEY_DOWN:
                        printw("Down Arrow\n");
                        break;
                    default:
                        printw("Not an arrow key!\n");
                }
            }
            */

            bool userLost = false, userQuit = false;
            int score = 0, ms = 1000; // will decrease by 250 every 15 points
                                      // once ms == 500, it will decrease by 25 every 10 points
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::string arr[4] = {"UP", "RIGHT", "DOWN", "LEFT"};
            std::vector<std::string> sequence;
            while (!userQuit)
            {
                srand(static_cast<unsigned int>(time(0))); // seeding srand
                int randomNum = rand() % 4;                // rand num from 0-3
                sequence.push_back(arr[randomNum]);
                // now show sequence
                for (int i = 0; i < sequence.size(); i++)
                {
                    clear();
                    move(1, 0);
                    printw("*****************************************************************************************************");
                    std::string sequenceMem = std::to_string(i + 1);
                    sequenceMem.append(") ");
                    sequenceMem.append(sequence.at(i));
                    move(10, 50 - (sequenceMem.length() / 2));
                    printw("%s", sequenceMem.c_str());

                    move(20, 0);
                    printw("*****************************************************************************************************");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                }
                // now check out users sequence
                std::string yourTurn = "Now repeat the sequence using arrow keys!";
                clear();
                move(1, 0);
                printw("*****************************************************************************************************");

                move(10, 50 - (yourTurn.length() / 2));
                printw("%s", yourTurn.c_str());

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();
                timeout(-1);
                int movesMade = 0;
                int userChoice = -1;
                flushinp();
                while (movesMade != sequence.size() && !userQuit)
                {
                    userChoice = getch();
                    if ((char)userChoice == 'q')
                    {
                        userQuit = true;
                        break;
                        /*
                        do something else here
                        */

                        std::string quitMessage = "Quitting Game...";
                        clear();
                        move(1, 0);
                        printw("*****************************************************************************************************");

                        move(10, 50 - (quitMessage.length() / 2));
                        printw("%s", quitMessage.c_str());

                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();
                        waitThisLong(2);
                    }
                    else if (userChoice == KEY_LEFT)
                    {
                        if (sequence.at(movesMade) == "LEFT")
                        {
                            movesMade++;
                        }
                        else
                        {
                            userLost = true;
                            break;
                        }
                    }
                    else if (userChoice == KEY_RIGHT)
                    {
                        if (sequence.at(movesMade) == "RIGHT")
                        {
                            movesMade++;
                        }
                        else
                        {
                            userLost = true;
                            break;
                        }
                    }
                    else if (userChoice == KEY_UP)
                    {
                        if (sequence.at(movesMade) == "UP")
                        {
                            movesMade++;
                        }
                        else
                        {
                            userLost = true;
                            break;
                        }
                    }
                    else if (userChoice == KEY_DOWN)
                    {
                        if (sequence.at(movesMade) == "DOWN")
                        {
                            movesMade++;
                        }
                        else
                        {
                            userLost = true;
                            break;
                        }
                    }
                    else
                    {
                        // ignore input
                    }
                }

                if (userLost)
                {
                    if (score > highScore)
                        highScore = score;
                    clear();
                    std::string messageLost = "You have lost!";
                    std::string messageLost1 = "Your score was ";
                    std::string messageLost2 = "High score: ";
                    messageLost1.append(std::to_string(score));
                    messageLost2.append(std::to_string(highScore));
                    move(1, 0);
                    printw("*****************************************************************************************************");
                    move(10, 50 - (messageLost.length() / 2));
                    printw("%s", messageLost.c_str());

                    move(11, 50 - (messageLost1.length() / 2));
                    printw("%s", messageLost1.c_str());
                    move(12, 50 - (messageLost2.length() / 2));
                    printw("%s", messageLost2.c_str());

                    move(20, 0);
                    printw("*****************************************************************************************************");
                    refresh();

                    waitThisLong(2);

                    clear();
                    move(1, 0);
                    printw("*****************************************************************************************************");
                    move(20, 0);
                    printw("*****************************************************************************************************");

                    std::string playAgain = "Play again? Y/N";

                    move(10, 50 - (playAgain.length() / 2));
                    printw("%s", playAgain.c_str());
                    timeout(2000);

                    int Choice = getch();
                    if ((char)Choice == 'Y' || (char)Choice == 'y')
                    {
                        sequence.clear();
                        score = 0;
                        userLost = false;
                    }
                    else
                    {
                        userQuit = true;
                    }
                }
                else if (userQuit)
                {
                    // DONT DO ANYTHING
                }
                else
                {
                    score++;
                    if (score == 15)
                    {
                        ms -= 250;
                    }
                    else if (score == 30)
                    {
                        ms -= 250;
                    }
                    else if (ms <= 500 && (score % 10 == 0))
                    {
                        ms -= 10;
                    }
                    else if (ms == 250)
                    {
                        // ok dont do anything to this point it'll be too fast
                    }
                }
            }

            weDone = true;

            if (!playedMemoryAlr)
            {
                playedMemoryAlr = true;
                addCharge(Item("Memory Game", 3.00, "Charge for playing game"));
                // add charge
            }
        }
        else if ((char)uChoice == '2')
        {
            char board[3][3];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    board[i][j] = '&'; // for now;
                }
            }

            bool p1Won = false, p2Won = false;
            bool p1Turn = true; // if false, p2 turn
            while (!p1Won && !p2Won)
            {
                // flushinp();
                clear();
                move(1, 0);
                printw("*****************************************************************************************************");

                for (int i = 0, y = 8; i < 3; i++, y += 2)
                {
                    for (int j = 0, x = 48; j < 3; j++, x += 2)
                    {
                        move(y, x);
                        printw("%c", board[i][j]);
                    }
                }

                move(20, 0);
                printw("*****************************************************************************************************");
                refresh();

                noecho();   // just in case lollllll lmaooo xdddd
                if (p1Turn) // X
                {
                    p1Turn = false;
                    bool goodSpot = false;
                    while (!goodSpot)
                    {
                        int p1ChoiceX = -1, p1ChoiceY = -1;
                        bool goodChoiceX = false, goodChoiceY = false;


                        clear();
                        move(1, 0);
                        printw("*****************************************************************************************************");

                        for (int i = 0, y = 8; i < 3; i++, y += 2)
                        {
                            for (int j = 0, x = 48; j < 3; j++, x += 2)
                            {
                                move(y, x);
                                printw("%c", board[i][j]);
                            }
                        }
                        std::string msg1 = "Player 1's turn!";
                        std::string msg2 = "First give column number (1-3)";
                        move(15, 50 - (msg1.length() / 2));
                        printw("%s", msg1.c_str());
                        move(16, 50 - (msg2.length() / 2));
                        printw("%s", msg2.c_str());

                        move(20, 0);
                        printw("*****************************************************************************************************");
                        refresh();


                        while (!goodChoiceX)
                        {

                            flushinp();
                            timeout(-1);
                            p1ChoiceX = getch();
                            if (0x31 <= p1ChoiceX && p1ChoiceX <= 0x33)
                            {
                                goodChoiceX = true;
                            }
                            else
                            {
                                // dont do anything
                            }
                        }


                        
                        while (!goodChoiceY)
                        {
                            flushinp();
                            timeout(-1);
                            p1ChoiceY = getch();
                            if (0x31 <= p1ChoiceY && p1ChoiceY <= 0x33)
                            {
                                goodChoiceY = true;
                            }
                            else
                            {
                                // dont do anything
                            }
                        }
                        if (board[(p1ChoiceY - 0x30) - 1][(p1ChoiceX - 0x30) - 1] == '&')
                        {
                            board[(p1ChoiceY - 0x30) - 1][(p1ChoiceX - 0x30) - 1] = 'X';
                            goodSpot = true;
                        }
                        else
                        {
                            clear();
                            move(1, 0);
                            printw("*****************************************************************************************************");

                            for (int i = 0, y = 8; i < 3; i++, y += 2)
                            {
                                for (int j = 0, x = 48; j < 3; j++, x += 2)
                                {
                                    move(y, x);
                                    printw("%c", board[i][j]);
                                }
                            }

                            move(20, 0);
                            printw("*****************************************************************************************************");
                            refresh();
                            // dont do anything
                        }
                    }
                }
                else // 0
                {
                }
            }

            if (!playedTicTacToeAlr)
            {
                playedTicTacToeAlr = true;
                addCharge(Item("Tic Tac Toe", 3.00, "Charge for playing game"));

                // ADD CHARGE
            }
        }
        else
        {
            // ignore input
        }
    }
}

void CustomerAtTable::payBillOption()
{
    clear();
    refreshItems(); // refreshes the items just in case cuz why not lol lmao :3 :3 :3
    move(1, 0);
    printw("*****************************************************************************************************");
    bool goodToPay = true;
    if (items.getCount() != 0) // why even do this like why
    {
        for (int i = 0, movePoint = 10; i <= items.getCount(); i++, movePoint++)
        {
            if (i == items.getCount())
            {
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << getBill();
                std::string bill = ss.str();
                move(movePoint, 0);
                printw("TOTAL: ");
                move(movePoint, 30);
                printw("%s", bill.c_str());
            }
            else
            {
                move(movePoint, 0);
                printw("%s", items.getNode(i)->data.getName().c_str());
                move(movePoint, 30);
            }
        }
        move(items.getCount() + 10, 0);
        printw("Pay now? (y/n)");
    }
    else
    {
        move(items.getCount() + 10, 50 - 15);
        printw("You haven't ordered any items!");
        goodToPay = false;
    }

    move(items.getCount() + 12, 0);
    printw("*****************************************************************************************************");
    refresh();
    if (!goodToPay)
        waitThisLong(3);

    timeout(20000); // if not atfer 20 seconds, like come on now
    int uChoice = -1;

    while (((char)uChoice != 'y' && (char)uChoice != 'Y' && (char)uChoice != 'n' && (char)uChoice != 'N') && goodToPay)
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
                timeout(-1); // set indefinite timeout
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

void CustomerAtTable::addCharge(Item adder)
{
    refreshItems();
    items.add(adder);

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

    for (int i = 0; i < items.getCount(); i++)
    {
        std::string adder = "";
    }

    std::filesystem::remove(path); // removes spin lock
    // should also add it to text file
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
    // intialized screen
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
        if (resetTable)
        {
            clearTable();
            /*
            FIGURE OUT WHAT TO DO HERE

               _____
          .- '     ' -.
        /               \
       |    .-'~~~'-.    |
       |  /  _   _  \  |
       | |  (o) (o)  | |
       | |   (_)     | |
        \ \  \___/  / /
         '-._______.-'
          /`-------'\
        /             \
       /   \       /   \
      /     `-___-'     \
     /                   \
    /_/_/_/_/_/_/_/_/_/_/_\

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
                std::string message1 = "TRY OUR NEW DELICIOUS BURGER MEAL!";
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

std::string CustomerAtTable::getTitlePrivilege()
{
    return title;
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