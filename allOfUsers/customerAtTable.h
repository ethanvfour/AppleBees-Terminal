#ifndef CUSTOMER_TABLE
#define CUSTOMER_TABLE
#include "user.h"
#include "../outsideFunctions/coolFunctions.h"
#include "otherObj/table.h"
#include <iostream>


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



class CustomerAtTable : public User
{
private:
    
public:
};



#endif