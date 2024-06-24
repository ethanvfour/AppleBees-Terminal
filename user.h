#ifndef USER_HEADER
#define USER_HEADER
#include <iostream>



/*
The parent class of all the users
*/
class User
{
private:
    
protected:
    std::string title;
public:

    /*
    Default constructor for User class
    */
    User();


    /*
    Constructor for User class that takes in an argument which is a string
    */
    User(std::string title);


    /*
    Returns in string either admin, chef, waiter, or customer
    */
    virtual std::string getTitlePrivilege() = 0;
};




#endif USER_HEADER