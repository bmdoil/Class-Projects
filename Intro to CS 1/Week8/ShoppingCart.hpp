/*********************************************************************
** Author: Brent Doil
** Date: 2/8/2016
** Description: Assignment 8 ShoppingCart.hpp
*********************************************************************/

#ifndef SHOPPINGCART_HPP
#define	SHOPPINGCART_HPP
#include "Item.hpp"

class ShoppingCart
{
private:
	//Declare array of pointers to item of size 100
	Item* itemArray[100];	

	//next empty spot in array
	int arrayEnd;

public:
	//default constructor
	ShoppingCart();

	//functions
	void addItem(Item* i);

	double totalPrice();
};
#endif
