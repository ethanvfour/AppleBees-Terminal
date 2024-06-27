#ifndef CUSTOMER_LOBBY
#define CUSTOMER_LOBBY
#include "user.h"
#include "../outsideFunctions/coolFunctions.h"
#include <iostream>
#include "otherObj/table.h"
#include <queue>
#include <filesystem> //gonna be used to open db and see if another executable is currenly opening
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/*
This function will take in a string and use the ror implication in assembly to encrypt each byte
String is passed by ref
*/
extern "C" void encryptString(char *str, int length);

/*
This function will take in a string and use the rol implication in assembly to decrypt each byte
String is passed by ref
*/
extern "C" void decryptString(char *str, int length);

/*
Needed cuz stoi is acting like a baby, a big baby holy
*/
std::string makeItANumber(std::string str);

/*
What the queue is gonna hold
*/
struct customerInfo
{
    std::string firstName, phoneN;
    int queueNum, howManyPeople;

    /*
    Default Constructor
    */
    customerInfo();

    /*
    Constructor with params
    */
    customerInfo(std::string, std::string, int, int);
};

/*
    DB is to look like
    "<firstName>" "<phoneNumber>" "<amountOfPeople>"
*/
class CustomerAtLobby : public User
{
private:
    /*
    Gonna be a 2d array of a 6x5
    Assuming the restaurant has 30 tables 
    */
    Table **tables = nullptr;
    std::queue<customerInfo> customerInLine;

    /*
    Adds a customer to a queue
    */
    void addToQueue(std::string, std::string, int);

    /*
    Will refresh the queue
    */
    void Refresh();

    void RefreshTables();

public:
    /*
    Default constructor for Customer
    */
    CustomerAtLobby();

    /*
    Runs the "ui" for the queue
    */
    void run();

    /*
    Returns a string of what title it gets
    */
    std::string getTitlePrivilege();

    /*
    Deconstructor
    Going to call encrypt, and update db
    */
    ~CustomerAtLobby();

};

/*
Gets in user input the ncurses way
*/
void ncursesUserInput(std::string &uInput);


#endif