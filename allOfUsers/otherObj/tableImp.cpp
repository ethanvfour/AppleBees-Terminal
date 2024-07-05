#include "table.h"


Table::Table()
{
    tableNum = 0;
    isOccupied = false;
    numOfPeople = 0;
    isCleaned = false;
}

Table::Table(int tableNum, bool isOccupied, int numOfPeople, bool isCleaned)
{
    this->tableNum = tableNum;
    this->isOccupied = isOccupied;
    this->numOfPeople = numOfPeople;
    this->isCleaned = isCleaned;
}

int Table::getTableNum()
{
    return tableNum;
}

bool Table::getIsOccupied()
{
    return isOccupied;
}

bool Table::getIsCleaned()
{
    return isCleaned;
}

int Table::getNumOfPeople()
{
    return numOfPeople;
}

void Table::setTableNum(int tableNum)
{
    this->tableNum = tableNum;
}

void Table::setIsOccupied(bool isOccupied)
{
    this->isOccupied = isOccupied;
}

void Table::setNumOfPeople(int numOfPeople)
{
    this->numOfPeople = numOfPeople;
}

void Table::setIsCleaned(bool isCleaned)
{
    this->isCleaned = isCleaned;
}  



