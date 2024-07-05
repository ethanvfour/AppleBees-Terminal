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

            fName = queue.substr(0, queue.find('\"', 2) + 1);

            queue = queue.substr(queue.find('\"', 2) + 2, queue.length());
            phoneN = queue.substr(0, queue.find('\"', 2) + 2);

            queue = queue.substr(queue.find('\"', 2) + 2, queue.length());
            sizeOfParty = queue;
            sizeOfParty = makeItANumber(sizeOfParty);

            customerInLine.push(customerInfo(removeQuotations(fName.substr(1, fName.find('\"') - 2)), removeQuotations(phoneN.substr(1, phoneN.find('\"') - 2)), queueNum++, std::stoi(sizeOfParty)));
        }
    }

    customerInLine.push(customerInfo(fNameAdder, phoneNAdder, queueNum++, partySize));
    openDb.close();

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

    std::filesystem::remove(path);
    Refresh();
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

        while (std::getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());

            fName = queue.substr(0, queue.find('\"', 2) + 1);

            queue = queue.substr(queue.find('\"', 2) + 2, queue.length());
            phoneN = queue.substr(0, queue.find('\"', 2) + 2);

            queue = queue.substr(queue.find('\"', 2) + 2, queue.length());
            sizeOfParty = queue;
            sizeOfParty = makeItANumber(sizeOfParty);

            customerInLine.push(customerInfo(removeQuotations(fName.substr(1, fName.find('\"') - 2)), removeQuotations(phoneN.substr(1, phoneN.find('\"') - 2)), queueNum++, std::stoi(sizeOfParty)));
        }
    }
    std::filesystem::remove(path);
}

void CustomerAtLobby::RefreshTables()
{
    if (tables == nullptr)
    {
        tables = new Table *[6];
        for (int i = 0; i < 6; i++)
        {
            tables[i] = new Table[5];
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            delete[] tables[i];
        }
        delete[] tables;
    }

    std::filesystem::path path = "../dataBase/tablesInfoSL.txt";

    while (std::filesystem::exists(path))
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/tablesInfoSL.txt"); // spinlock

    std::ifstream openDb("../dataBase/tablesInfo.txt");

    std::string tableInfo = "";

    int tableNum = 0;
    bool isOccupied = false;
    int numOfPeople = 0;
    bool isCleaned = false;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            getline(openDb, tableInfo);
            decryptString(&tableInfo[0], tableInfo.length());
            tableNum = std::stoi(tableInfo.substr(1, tableInfo.find('\"') - 1));
            tableInfo = tableInfo.substr(tableInfo.find('\"', 2) + 2, tableInfo.length());
            if (tableInfo.substr(1, tableInfo.find('\"') - 1) == "true")
            {
                isOccupied = true;
            }
            else
            {
                isOccupied = false;
            }
            tableInfo = tableInfo.substr(tableInfo.find('\"', 2) + 2, tableInfo.length());

            numOfPeople = std::stoi(tableInfo.substr(1, tableInfo.find('\"') - 1));

            tableInfo = tableInfo.substr(tableInfo.find('\"', 2) + 2, tableInfo.length());

            if (tableInfo.substr(1, tableInfo.find('\"') - 1) == "true")
            {
                isCleaned = true;
            }
            else
            {
                isCleaned = false;
            }
            tables[i][j] = Table(tableNum, isOccupied, numOfPeople, isCleaned);
        }
    }

    openDb.close();
    std::filesystem::remove(path);
}

int CustomerAtLobby::howManyAvailableTables()
{
    RefreshTables(); // refreshes the tables rq

    int count = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!tables[i][j].getIsOccupied())
                count++;
        }
    }

    return count;
}

void CustomerAtLobby::viewQueue()
{
    echo();
    endwin();
    std::queue<customerInfo> temp = customerInLine;
    coolOutput("");
    while (!temp.empty())
    {
        coolOutputNoClear("Name: ");
        coolOutputNoClear(temp.front().firstName);
        coolOutputNoClear(" Phone Number: ");
        coolOutputNoClear(temp.front().phoneN);
        coolOutputNoClear(" Party Size: ");
        coolOutputNoClear(std::to_string(temp.front().howManyPeople));
        coolOutputNoClear("\n");
        temp.pop();
    }
    waitThisLong(5);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    coolOutput("");
}

std::string CustomerAtLobby::removeQuotations(std::string str)
{
    std::string replacement = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '\"')
            replacement += str[i];
    }
    return replacement;
}

CustomerAtLobby::CustomerAtLobby() : User()
{
    title = "customerAtLobbyWaiting";
    Refresh();
    RefreshTables();
}

void CustomerAtLobby::run()
{
    endwin();
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
        timeout(0);
        getch();
        coolOutput("");
        std::cout << "\r" << RESET << std::setw(60) << std::setfill('*') << "" << std::endl
                  << std::flush;
        std::cout << "\rWelcome to " << RED << "AppleBee's!" << RESET " Press any button to reserve a spot!" << std::endl;
        std::cout << "\r" << RESET << std::setw(60) << std::setfill('*') << "" << std::endl
                  << std::flush;
        std::cout << "\r ";
        timeout(60000);
        uInput = getch();
        if (uInput == 27)
        {
            echo();
            done = true;
        }
        else if ((char)uInput == '$')
        {
            viewQueue();
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
            endwin();
            coolOutput("");

            while (true)
            {
                coolOutput("Hello there! What is the name for the reservation?\n\r**");
                std::getline(std::cin, fName);
                bool goodName = true;

                for (int i = 0; i < fName.length() && goodName; i++)
                {
                    if (fName[i] == '\"')
                        goodName = false;
                }
                if (goodName)
                    break;
                else
                {
                    coolOutput("Not a valid name!\n");
                    waitThisLong(2);
                }
            }

            // endwin();

            // ncursesUserInput(fName);
            //  initscr();
            coolOutput("");
            // std::cin>>phoneNum;
            while (true)
            {
                coolOutputNoClear("\rGreat! Hello ");
                coolOutputNoClear(fName);
                coolOutputNoClear("! Now what is a good phone number to text you when your table is ready?\n\rFollow the format");
                std::cout << RED;
                coolOutputNoClear("*** *** ****");
                std::cout << RESET;
                coolOutputNoClear("\n\r**");
                std::getline(std::cin, phoneNum);

                bool goodNum = true;
                if (phoneNum.length() != 12)
                    goodNum = false;
                for (int i = 0; i < phoneNum.length() && goodNum; i++)
                {
                    if (i == 3 || i == 7)
                    {
                        if (phoneNum[i] != ' ')
                            goodNum = false;
                    }
                    else
                    {
                        if (!(0x30 <= phoneNum[i] && phoneNum[i] <= 0x39))
                            goodNum = false;
                    }
                }
                if (goodNum)
                    break;
                else
                {
                    coolOutput("Not a valid number!\n");
                    waitThisLong(2);
                }
            }
            while (true)
            {
                coolOutput("Lastly, how big is the party size?\n**");
                std::getline(std::cin, sizeOfParty);
                // sizeOfParty = "23";
                bool goodStr = true;
                if (sizeOfParty.length() >= 3)
                    goodStr = false;

                for (int i = 0; i < sizeOfParty.length() - 1 && goodStr; i++)
                {
                    if (!(48 <= (int)sizeOfParty[i] && (int)sizeOfParty[i] <= 57))
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

            initscr();
            cbreak();
            keypad(stdscr, TRUE);
            noecho();

            addToQueue(fName, phoneNum, stoi(sizeOfParty));

            coolOutput("Adding to queue...");
            waitThisLong(2);

            int waitTime = 0; // temp

            if (howManyAvailableTables() == 0)
            {
                waitTime = customerInLine.size() * 10;
                coolOutput("Wait time is about ");
                coolOutputNoClear(std::to_string(waitTime));
                coolOutputNoClear(" minutes.\n");
            }
            else
            {
                coolOutput("There is a table available for you right now!\n");
                waitThisLong(2);
                coolOutputNoClear("Please wait for a server to take you to your table!\n");
            }

            waitThisLong(4);
        }
    }
    coolOutput("");
    echo();
    // endwin();
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
        endwin();
        encryptString(&putter[0], putter.length());

        replaceQueue << putter << std::endl;
        customerInLine.pop();
    }

    std::filesystem::remove(path); // removes spinlock
    initscr();

    if(tables != nullptr)
    {
        for(int i = 0; i < 6; i++)
        {
            delete[] tables[i];
        }
        delete[] tables;
    } 
}

void ncursesUserInput(std::string &uInput)
{
    bool nameDone = false;

    while (!nameDone)
    {

        int adder = getch();
        if (adder == 263)
        {
            if (uInput.length() > 1)
                uInput.substr(0, uInput.length() - 1);
            else
                uInput = "";
            std::cout << uInput;
        }
        else if ((char)adder != '\n')
        {
            uInput += (char)adder;
        }
        else
            nameDone = true;
    }
}

std::string makeItANumber(std::string str)
{
    std::string ret = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (0x30 <= str[i] && str[i] <= 0x39)
            ret += str[i];
    }
    return ret;
}