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
    std::string firstName, lastName;
    std::string phoneNumber; 
public:
    /*
    Default constructor for User class
    */
    User();


    /*
    Constructor for User class that takes in arguments which are strings
    */
    User(std::string title, std::string id, std::string fName, std::string lName, std::string phoneNum);




    /*
    Returns in string either admin, chef, waiter, or customer
    */
    virtual std::string getTitlePrivilege() = 0;

    /*
    Runs correct tablet screen
    */
    virtual void run() = 0;

    /*
    Virual Deconstuctor
    */
    virtual ~User() = 0;
};




#endif