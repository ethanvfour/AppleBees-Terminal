#ifndef CUSTOMER
#define CUSTOMER
#include "user.h"
#include <iostream>
#include <queue>


class CustomerAtLobby : public User
{
private:
    std::queue<int> customerInLine;
public:

    /*
    Default constructor for Customer
    */
    CustomerAtLobby();

    void run();

    std::string getTitlePrivilege();



    ~CustomerAtLobby()
    {

    }

};



#endif