#ifndef TABLE
#define TABLE



/*
In database text file, it should look like 
"<tableNum>" "<isOccupied>" "<numOfPeople>" "<isCleaned>"
*/

class Table
{
private:
    int tableNum;
    bool isOccupied;
    int numOfPeople;
    bool isCleaned;
public:
    /*
    Default constructor for Table class
    */
    Table();

    /*
    Constructor for Table class that takes in arguments which are integers and booleans
    */
    Table(int tableNum, bool isOccupied, int numOfPeople, bool isCleaned);

    /*
    Returns the table number
    */
    int getTableNum();

    /*
    Return true if table is occupied, false if not
    */
    bool getIsOccupied();

    /*
    Returns number of people at table
    */
    int getNumOfPeople();

    /*
    Return true if table is cleaned, false if not
    */
    bool getIsCleaned();

    /*
    Sets table number specified by param
    */
    void setTableNum(int tableNum);

    /*
    Sets table to occupied or not occupied
    */
    void setIsOccupied(bool isOccupied);

    /*
    Sets the number of people specified by param
    */
    void setNumOfPeople(int numOfPeople);

    /*
    Sets table to cleaned or not cleaned
    */
    void setIsCleaned(bool isCleaned);
};





#endif