#ifndef ITEMS
#define ITEMS
#include <string>


/*
Text file should look like 

"<name>" "<price>" "<description>";
*/

class Item
{
private:
    std::string name;
    double price;
    std::string description;
public:

    /*
    Constructor for Item
    */
    Item();

    /*
    Constructor for Item with params
    */
    Item(std::string name, double price, std::string description);

    /*
    Getters for name
    */
    std::string getName();


    /*
    Getters for price
    
    */
    double getPrice();

    /*
    Getters for description
    */
    std::string getDescription();

    /*
    Setters for name
    */
    void setName(std::string name);

    /*
    Setters for price
    */
    void setPrice(double price);

    /*
    Setters for description
    */
    void setDescription(std::string description);

    /*
    Overloads the assignment operator for Item
    */
    Item& operator= (const Item &item);

    /*
    Destructor for Item
    */
    ~Item();

};

#endif