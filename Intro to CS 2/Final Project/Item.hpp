/*******************************************************
**Program Filename: Item.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: item interface
*********************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include <iostream>
enum ItemType {RareCandy,HealingPotion,Pokeball,Bike,Badge,Key,BadMojo};
class Item
{
private:
	ItemType item;
	int quantity;
	std::string name;
public:
	Item(ItemType);	
	void add();
	void use();
	ItemType type();
	std::string getName();
	int getQuantity();
	void print();
};


#endif // !ITEM_HPP

