/*******************************************************
**Program Filename: Item.hpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: Item class interface
*********************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include <iostream>

class Item
{
private:
	std::string name;
	std::string unit; //Type of item (Oz,Gallon,Box etc.)
	int numToBuy;
	double unitPrice;
public:
	Item();
	Item(std::string n, std::string u, int toBuy, double unitP);
	double itemPrice();
	void print();
	std::string getName();
	friend bool operator== (const Item& lhs, const Item& rhs); //Overloaded == operator
};

#endif // !ITEM_HPP

