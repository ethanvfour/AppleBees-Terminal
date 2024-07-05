#ifndef USER_HEADER
#define USER_HEADER
#include <iostream>



/*
The parent class of all the users
*/
class User
{    
protected:
    std::string title;
    std::string id; //customer does NOT need one
    std::string firstName, lastname;
    std::string phoneNumber; 
public:
    /*
    Default constructor for User class
    */
    User();


    /*
    Constructor for User class that takes in arguments which are strings
    */
    User(std::string , std::string , std::string , std::string , std::string );



    /*
    Returns in string either admin, chef, waiter, or customer
    */
    virtual std::string getTitlePrivilege() = 0;
};




#endif USER_HEADER