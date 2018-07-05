#include "ShoppingCart.hpp"

//default constructor
ShoppingCart::ShoppingCart()
{
	for (int count = 0; count < 100; count++)
	{
		itemArray[count] = NULL;
	}
	arrayEnd = 0;
}

//functions
void ShoppingCart::addItem(Item* i)
{
	itemArray[arrayEnd] = i;
	arrayEnd++;
}
double ShoppingCart::totalPrice()
{
	double totalPrice = 0;
	for (int i = 0; i < arrayEnd; i++)
	{
		totalPrice += itemArray[i]->getPrice() * itemArray[i]->getQuantity();
	}
	return totalPrice;
}