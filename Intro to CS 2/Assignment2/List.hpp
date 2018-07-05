/*******************************************************
**Program Filename: List.hpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: List class interface
*********************************************************/

#ifndef LIST_HPP
#define LIST_HPP

#include "Item.hpp"


class List
{
private:
	Item** shoppingList;	
	int inventory; //Items in shoppingList
	int size; //Total size of shoppingList
	void addToList(Item* item);
public:
	List();
	~List();
	void addItem(std::string n, std::string u, int toBuy, double unitP);
	void removeItem(std::string name);
	void displayList();
};

#endif // !LIST_HPP

