#include "Item.h"

Item::Item()
{
    name = "";
    price = 0.0;
    description = "";
}

Item::Item(std::string name, double price, std::string description)
{
    this->name = name;
    this->price = price;
    this->description = description;
}

std::string Item::getName()
{
    return name;
}

double Item::getPrice()
{
    return price;
}

std::string Item::getDescription()
{
    return description;
}

void Item::setName(std::string name)
{
    this->name = name;
}

void Item::setPrice(double price)
{
    this->price = price;
}

void Item::setDescription(std::string description)
{
    this->description = description;
}

Item::~Item()
{
}

