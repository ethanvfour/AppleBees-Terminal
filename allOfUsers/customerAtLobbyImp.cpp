#include "customerAtLobby.h"

customerInfo::customerInfo()
{
    firstName = "";
    phoneN = "";
    queueNum = -1;
}

customerInfo::customerInfo(std::string fName, std::string phoneNum, int qNum)
{
    firstName = fName;
    phoneN = phoneNum;
    queueNum = qNum;
}

void CustomerAtLobby::addToQueue(std::string fNameAdder, std::string phoneNAdder)
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
        std::string fName = "", phoneN = "";

        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"')-1), phoneN.substr(1, phoneN.find('\"')-1), queueNum++));
        }
    }

    customerInLine.push(customerInfo(fNameAdder, phoneNAdder, queueNum++));

    std::queue<customerInfo> copy = customerInLine;

    ofstream replaceQueue("../dataBase/customerAtLobbyQueue.txt");
    while (!copy.empty())
    {
        std::string putter = "";

        putter += "\"" + copy.front().firstName + "\" ";
        putter += "\"" + copy.front().phoneN + "\"";

        encryptString(&putter[0], putter.length());

        replaceQueue << putter << std::endl;
        copy.pop();
    }


    std::filesystem::remove(path);
}

void CustomerAtLobby::refresh()
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
        std::string fName = "", phoneN = "";

        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"')-1), phoneN.substr(1, phoneN.find('\"')-1), queueNum++));
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

    if (!openDb.is_open())
    {
        // not suppose to happen, assume queue is empty?
    }
    else
    {
        std::string queue = "";
        std::string fName = "", phoneN = "";
        int queueNum = 1;
        while (getline(openDb, queue)) // read the text file
        {
            decryptString(&queue[0], queue.length());
            std::stringstream ss(queue);
            ss >> fName >> phoneN;
            // queueNum = stoi(tempQNum.substr(1, tempQNum.find('\"', 2)-1));
            customerInLine.push(customerInfo(fName.substr(1, fName.find('\"')-1), phoneN.substr(1, phoneN.find('\"')-1), queueNum++));
        }
    }

    std::filesystem::remove(path); // removes spinlock
}

void CustomerAtLobby::run()
{
    //setting up ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    int uInput = -100;//for now
    bool done = false;

    while(!done)
    {
        timeout(60000);
        uInput = getch();
        if(uInput != ERR)
        {

        }
        else
        {
            
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
    std::filesystem::path path = "../dataBase/customerAtLobbyQueueSL.txt";

    while (std::filesystem::exists(path))
    {
        // keeps waiting till it doesnt exist
    }

    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt"); // spinlock
    spinLock.close();

    ofstream replaceQueue("../dataBase/customerAtLobbyQueue.txt");
    while (!customerInLine.empty())
    {
        std::string putter = "";

        putter += "\"" + customerInLine.front().firstName + "\" ";
        putter += "\"" + customerInLine.front().phoneN + "\"";

        encryptString(&putter[0], putter.length());

        replaceQueue << putter << std::endl;
        customerInLine.pop();
    }

    std::filesystem::remove(path); // removes spinlock
}