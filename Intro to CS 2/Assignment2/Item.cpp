/*******************************************************
**Program Filename: Item.cpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: Item class implementation
*********************************************************/

#include "Item.hpp"
/*********************************************************************
** Function: Item default constructor
** Description: Sets name and unit to "", numtoBuy and unitPrice to 0
*********************************************************************/
Item::Item()
{
	name = "";
	unit = "";
	numToBuy = 0;
	unitPrice = 0;
}
/*********************************************************************
** Function: Item constructor
** Description: Takes name, unit, numtoBuy and unitPrice as arguments
** to instantiate item
*********************************************************************/
Item::Item(std::string n, std::string u, int toBuy, double unitP)
{
	name = n;
	unit = u;
	numToBuy = toBuy;
	unitPrice = unitP;
}
/*********************************************************************
** Function: itemPrice
** Description: Returns total price of item, unitPrice * numToBuy
*********************************************************************/
double Item::itemPrice()
{	
	int numTemp = this->numToBuy;
	double unitTemp = this->unitPrice;
	return numTemp * unitTemp;
}
/*********************************************************************
** Function: print
** Description: Prints Item data to screen
*********************************************************************/
void Item::print()
{
	std::cout << "-----------------------------------";
	std::cout << "\nItem Name: " << this->name;
	std::cout << "\nUnit for Purchase: " << this->unit;
	std::cout << "\nPrice per Unit:  " << this->unitPrice;
	std::cout << "\nNumber to Buy: " << this->numToBuy;
	std::cout << "\nExtended Price: " << this->itemPrice();
	std::cout << "\n-----------------------------------\n";
}
/*********************************************************************
** Function: getName
** Description: Returns name of Item.
*********************************************************************/
std::string Item::getName()
{
	return this->name;
}
/*********************************************************************
** Function: operator==
** Description: Overload == to compare equality of two Item names
*********************************************************************/
bool operator==(const Item& lhs, const Item& rhs)
{
	return lhs.name == rhs.name;
}
