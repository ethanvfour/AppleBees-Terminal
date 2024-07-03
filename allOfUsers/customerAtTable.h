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
    Deconstructor for LinkedList
    Going to delete all nodes
    */
    ~LinkedListItems();  
};


class CustomerAtTable : public User
{
private:
    Table thisTable;
    LinkedListItems items;    

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
    */
    void addItem();

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