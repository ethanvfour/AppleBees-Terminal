#ifndef CUSTOMER
#define CUSTOMER
#include "user.h"
#include "../outsideFunctions/coolFunctions.h"
#include <iostream>
#include <queue>
#include <filesystem> //gonna be used to open db and see if another executable is currenly opening
#include <fstream>
#include <sstream>


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
    DB is to look like
    <queueNumber>,<firstName>,<phoneNumber>
*/
class CustomerAtLobby : public User
{
private:
    std::queue<int> customerInLine;


    /*
    Adds a customer to a queue
    */
    void addToQueue();
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