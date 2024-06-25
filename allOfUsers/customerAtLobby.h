#ifndef CUSTOMER
#define CUSTOMER
#include "user.h"
#include "../outsideFunctions/coolFunctions.h"
#include <iostream>
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
What the queue is gonna hold
*/
struct customerInfo
{
    std::string firstName, phoneN;
    int queueNum;

    /*
    Default Constructor
    */
    customerInfo();

    /*
    Constructor with params
    */
    customerInfo(std::string, std::string, int);
};




/*
    DB is to look like
    "<firstName>" "<phoneNumber>"
*/
class CustomerAtLobby : public User
{
private:
    std::queue<customerInfo> customerInLine;

    /*
    Adds a customer to a queue
    */
    void addToQueue(std:: string, std::string);


    /*
    Will refresh the queue
    */
    void refresh();
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

#endif