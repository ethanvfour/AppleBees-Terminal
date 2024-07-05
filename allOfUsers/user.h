#ifndef USER_HEADER
#define USER_HEADER
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

/*
The parent class of all the users
*/
class User
{
protected:
    std::string title;
    std::string id; // customer does NOT need one
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
    virtual ~User();
};

#endif