/*******************************************************
**Program Filename: Backpack.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: backpack interface
*********************************************************/

#ifndef BACKPACK_HPP
#define BACKPACK_HPP
#include "Item.hpp"
class Backpack
{
private:
	int maxSize;
	Item** pack;
	int gold;
	int currentsize;
public:
	Backpack(int);
	~Backpack();
	void addItem(Item*);
	void addItem(Item*, int);
	bool removeItem(ItemType);
	void displayBackpack();
	void changeGold(int);
	int getGold();
	int getItemQuant(ItemType);

};
#endif // !BACKPACK_HPP

