#include "user.h"


User::User()
{
    title = "";
    id = "";
    firstName = "";
    lastName = "";
    phoneNumber = "";
}

User::User(std::string title, std::string id, std::string fName, std::string lName, std::string phoneNum)
{
    this->title = title;
    this->id = id;
    firstName = fName;
    lastName = lName;
    phoneNumber = phoneNum;
}

User::~User()
{
    
}
