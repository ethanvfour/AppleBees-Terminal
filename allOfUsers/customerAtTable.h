#ifndef CUSTOMER_TABLE
#define CUSTOMER_TABLE
#include "user.h"
#include "../outsideFunctions/coolFunctions.h"
#include "otherObj/table.h"
#include "otherObj/Item.h"
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

template <class T>
struct node
{
    node * next;
    T data;

    /*
    Default constructor for node
    */
    node();

    /*
    Default constructor for node with data
    */
    node(T data);
};


class LinkedListItems
{
    node<Item> * head;
    int count;

public:
    /*
    Default constructor for LinkedList
    */
    LinkedListItems();

    /*
    Default constructor for LinkedList with data
    */
    LinkedListItems(Item data);
     
    /*
    Adds an item into the linked list
    */
    void add(Item data);

    /*
    Getter for count
    */
    int getCount();

    /*
    Assume index is good
    */
    node<Item> * getNode(int index);

    /*
    Clears linked list
    */
    void clearList();

    /*
    Deconstructor for LinkedList
    Going to delete all nodes
    */
    ~LinkedListItems();  
};

/*
textFile for table will look like 
table<tableNum>Items.txt

Example for table 2
table2Items.txt

Clear table will set everything to zero

*/
class CustomerAtTable : public User
{
private:
    Table thisTable;
    LinkedListItems items;    
    bool resetTable;//will only be true if user paid and terminal is waiting for new customer
    /*
    Gets the bill and total of all items
    */
    double getBill();

    /*
    Construtctor calls this function to initialize the table
    */
    void initizalizeTable(int);

    /*
    Adds an item to the list
    Will be called by orderFoodOption
    */
    void addItem();

    /*
    Refreshes the items bought into db
    Will also be called by orderFoodOption, addItem, or payBillOption
    */
    void refreshItems();


    /*
    Will be called by run
    */
    void orderFoodOption();

    /*
    Will be called by run
    */
    void playGamesOption();

    /*
    Will be called by run
    */
    void payBillOption();

    /*
    Will be called when they are done eating
    */
    void clearTable();

public:
    /*
    Constructor for CustomerAtTable
    Should probably not get called
    */
    CustomerAtTable();

    /*
    Initializes everything with the table num given
    */
    CustomerAtTable(int tableNum);

    /*
    Runs the program for the customer at table
    */
    void run();

    /*
    Gets title of tablet
    */
    std::string getTitlePrivilege();
    

    /*
    Destructor for CustomerAtTable
    */
    ~CustomerAtTable();
};

#endif