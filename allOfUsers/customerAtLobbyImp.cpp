#include "customerAtLobby.h"
#include "../outsideFunctions/coolFunctions.h"
customerInfo::customerInfo()
{
    firstName = "";
    phoneN = "";
    queueNum = -1;
    howManyPeople = 0;
}

customerInfo::customerInfo(std::string fName, std::string phoneNum, int qNum, int people)
{
    firstName = fName;
    phoneN = phoneNum;
    queueNum = qNum;
    howManyPeople = people;
}

void CustomerAtLobby::addToQueue(std::string fNameAdder, std::string phoneNAdder, int partySize)
{
    std::filesystem::path path = "../dataBase/customerAtLobbyQueueSL.txt";

    while (std::filesystem::exists(path)) // checks if spinlock is activated
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt"); // spinlock
    spinLock.close();

    std::ifstream openDb("../dataBase/customerAtLobbyQueue.txt");
    // closes immdiaetly

    // first empty, then read in from file, lastly, add it to queue, then update the db
    int queueNum = 1;
    while (!customerInLine.empty())
        customerInLine.pop();

    if (!openDb.is_open())
    {
        // not suppose to happen, assume queue is empty?
    }
    else
    {
        std::string queue = "";
        std::string fName = "", phoneN = "", sizeOfParty = "";

        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN >> sizeOfParty;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"') - 1), phoneN.substr(1, phoneN.find('\"') - 1), queueNum++, std::stoi(sizeOfParty.substr(1, sizeOfParty.find('\"') - 1))));
        }
    }

    customerInLine.push(customerInfo(fNameAdder, phoneNAdder, queueNum++, partySize));
    openDb.close();
    std::queue<customerInfo> copy = customerInLine;

    std::ofstream replaceQueue("../dataBase/customerAtLobbyQueue.txt");
    while (!copy.empty())
    {
        std::string putter = "";

        putter += "\"" + copy.front().firstName + "\" ";
        putter += "\"" + copy.front().phoneN + "\" ";
        putter += "\"" + std::to_string(copy.front().howManyPeople) + "\"";
        encryptString(&putter[0], putter.length());

        replaceQueue << putter << std::endl;
        copy.pop();
    }

    std::filesystem::remove(path);
}

void CustomerAtLobby::Refresh()
{
    std::filesystem::path path = "../dataBase/customerAtLobbyQueueSL.txt";

    while (std::filesystem::exists(path)) // checks if spinlock is activated
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt"); // spinlock
    spinLock.close();

    std::ifstream openDb("../dataBase/customerAtLobbyQueue.txt");
    // closes immdiaetly

    // first empty, then read in from file, lastly, add it to queue, then update the db
    int queueNum = 1;
    while (!customerInLine.empty())
        customerInLine.pop();

    if (!openDb.is_open())
    {
        // not suppose to happen, assume queue is empty?
    }
    else
    {
        std::string queue = "";
        std::string fName = "", phoneN = "", sizeOfParty = "";

        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN >> sizeOfParty;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"') - 1), phoneN.substr(1, phoneN.find('\"') - 1), queueNum++, std::stoi(sizeOfParty.substr(1, sizeOfParty.find('\"') - 1))));
        }
    }
    std::filesystem::remove(path);
}

CustomerAtLobby::CustomerAtLobby() : User()
{
    title = "customerAtLobbyWaiting";
    std::filesystem::path path = "../dataBase/customerAtLobbyQueueSL.txt";

    while (std::filesystem::exists(path))
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt"); // spinlock
    spinLock.close();

    std::ifstream openDb("../dataBase/customerAtLobbyQueue.txt");
    // closes immdiaetly
    int queueNum = 1;
    if (!openDb.is_open())
    {
        // not suppose to happen, assume queue is empty?
    }
    else
    {
        std::string queue = "";
        std::string fName = "", phoneN = "", sizeOfParty = "";

        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN >> sizeOfParty;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"') - 1), phoneN.substr(1, phoneN.find('\"') - 1), queueNum++, std::stoi(sizeOfParty.substr(1, sizeOfParty.find('\"') - 1))));
        }
    }

    std::filesystem::remove(path); // removes spinlock
}

void CustomerAtLobby::run()
{
    // setting up ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    noecho();
    timeout(1);
    getch();

    int uInput = -100; // for now
    bool done = false;

    while (!done)
    {
        coolOutput("");
        std::cout << "\r" << RESET << std::setw(55) << std::setfill('*') << "" << std::endl;
        std::cout << "\rWelcome to " << RED << "AppleBee's!" << RESET " Press any button to reserve a spot!" << std::endl;
        std::cout << "\r" << RESET << std::setw(55) << std::setfill('*') << "" << std::endl
                  << std::flush;
        std::cout << "\r";
        timeout(60000);
        refresh();
        uInput = getch();
        if (uInput == 27)
        {
            echo();
            done = true;
        }
        else if (uInput != ERR)
        {
            /*
            FOR NOW, SINCE TABLES IS NOT IMPLEMENTED YET, CHECK HOW BIG THE QUEUE IS
            ASSUME 10 MIN
            */

            std::string fName = "", phoneNum = "";
            std::string sizeOfParty = "";
            coolOutput("");
            // endwin();
            echo();
            coolOutput("Hello there! What is the name for the reservation?\n\r**");
            // endwin();
            ncursesUserInput(fName);
            // initscr();
            coolOutputNoClear("\n\rGreat! Hello ");
            coolOutputNoClear(fName);
            coolOutputNoClear("! Now what is a good phone number to text you when your table is ready?\n\rFollow the format");
            std::cout<<RED;
            coolOutputNoClear("(***) *** - ****");
            std::cout<<RESET;
            coolOutputNoClear("\n\r**");
            std::getline(std::cin, phoneNum);

            while (true)
            {
                coolOutput("Lastly, how big is the party size?\n**");
                std::getline(std::cin, phoneNum);
                bool goodStr = true;
                for (int i = 0; i < phoneNum.length() && goodStr; i++)
                {
                    if (!(0x30 <= phoneNum[i] && phoneNum[i] <= 0x39))
                        goodStr = false;
                }
                if (goodStr)
                    break;
                else
                {
                    coolOutput("Not a valid party size!\n");
                    waitThisLong(2);
                }
            }

            addToQueue(fName, phoneNum, stoi(sizeOfParty));
            coolOutput("Adding to queue...");
            waitThisLong(2);

            int waitTime = customerInLine.size() * 10;

            coolOutput("Wait time is about ");
            coolOutputNoClear(std::to_string(waitTime));
            coolOutputNoClear(" minutes.\n");

            waitThisLong(4);

            noecho();
        }
    }
    endwin();
}

std::string CustomerAtLobby::getTitlePrivilege()
{
    return title;
}

CustomerAtLobby::~CustomerAtLobby()
{

    Refresh(); // refresh it

    std::filesystem::path path = "../dataBase/customerAtLobbyQueueSL.txt";

    while (std::filesystem::exists(path))
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt"); // spinlock
    spinLock.close();

    std::ofstream replaceQueue("../dataBase/customerAtLobbyQueue.txt");
    while (!customerInLine.empty())
    {
        std::string putter = "";

        putter += "\"" + customerInLine.front().firstName + "\" ";
        putter += "\"" + customerInLine.front().phoneN + "\" ";
        putter += "\"" + std::to_string(customerInLine.front().howManyPeople) + "\"";

        encryptString(&putter[0], putter.length());

        replaceQueue << putter << std::endl;
        customerInLine.pop();
    }

    std::filesystem::remove(path); // removes spinlock
}

void ncursesUserInput(std::string &uInput)
{
    bool nameDone = false;
    while (!nameDone)
    {
        int adder = getch();
        if ((char)adder != '\n')
            uInput += (char)adder;
        else
            nameDone = true;
    }
}