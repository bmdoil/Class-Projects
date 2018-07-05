/*******************************************************
**Program Filename: Item.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: item implementation
*********************************************************/
#include "Item.hpp"

/*********************************************************************
** Function: Item constructor
** Description: sets itemType, quantity, and name of item based on
** itemType
*********************************************************************/
Item::Item(ItemType i)
{
	item = i;
	quantity = 1;
	switch (i)
	{
	case 0: name = "Rare Candy";
		break;
	case 1: name = "Healing Potion";
		break;
	case 2: name = "Pokeball";
		break;
	case 3: name = "Bike";
		break;
	case 4: name = "Badge";
		break;
	case 5: name = "Key";
		break;
	case 6: name = "Bad Mojo";
		break;
	default: name = "";
	}
}
/*********************************************************************
** Function: add
** Description: adds to existing item by incrementing quantity
*********************************************************************/
void Item::add()
{
	this->quantity++;
}
/*********************************************************************
** Function: use
** Description: uses item by decrementing quantity, else says no more
*********************************************************************/
void Item::use()
{
	if (quantity == 0)
	{
		std::cout << "No more " << this->name << " !\n";
	}
	else
	{
		quantity--;
	}
}
/*********************************************************************
** Function: type
** Description: returns item type
*********************************************************************/
ItemType Item::type()
{
	return item;
}
/*********************************************************************
** Function: getName
** Description: returns item name
*********************************************************************/
std::string Item::getName()
{
	return this->name;
}
/*********************************************************************
** Function: getQuantity
** Description: returns item quantity
*********************************************************************/
int Item::getQuantity()
{
	return quantity;
}
/*********************************************************************
** Function: print
** Description: prints item name and quantity
*********************************************************************/
void Item::print()
{
	std::cout << "-----------------------------------";
	std::cout << "\nItem Name: " << this->name;
	std::cout << "\nItem Quantity: " << this->quantity;
	std::cout << "\n-----------------------------------\n";
}
