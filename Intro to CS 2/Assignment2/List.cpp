/*******************************************************
**Program Filename: List.hpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: List class implementation
*********************************************************/

#include "List.hpp"

/*********************************************************************
** Function: List default constructor
** Description: Sets initital size of shoppingList to 4 and creates
** array of ptr to Items set to NULL. Sets inventory to 0;
*********************************************************************/
List::List()
{
	size = 4;
	shoppingList = new Item*[size];
	inventory = 0;
	
	
	for (int i = 0; i < size; i++)
	{
		shoppingList[i] = NULL;
	}

}
/*********************************************************************
** Function: List destructor
** Description: Frees memory allocated to shoppingList
*********************************************************************/
List::~List()
{
	for (int i = 0; i < size; i++)
	{
		if (shoppingList[i] != NULL)
			delete shoppingList[i];
	}
	delete[] shoppingList;
	shoppingList = NULL;
}
/*********************************************************************
** Function: addItem
** Description: Takes name, unit, numToBuy, unitPrice as arguments to
** create new item in shoppingList. Will increase size of shoppingList
** dynamically if necessary by calling addToList.
*********************************************************************/
void List::addItem(std::string n, std::string u, int toBuy, double unitP)
{
	
	Item* item = new Item(n, u, toBuy, unitP);
	for (int i = 0; i < inventory; i++)
	{
		//Overload == operator to not add duplicates
		if ((shoppingList[i] != NULL) && (*shoppingList[i] == *item))
		{
			std::cout << "Item already on list: \n";
			delete item;
			return;
		}
	}
	inventory++;
	if (inventory > size)
	{
		addToList(item);
		std::cout << "Added: " << shoppingList[size - 1]->getName() << "\n";		
		return;
	}
	else
	{
		for (int i = 0; i < inventory; i++)
		{
			if (shoppingList[i] == NULL)
			{
				shoppingList[i] = item;
				std::cout << "Added: " << shoppingList[i]->getName() << "\n";
				
				return;
			}
		}
	}
	
}
/*********************************************************************
** Function: addItem
** Description: Takes name of Item as argument. Searches for name in
** shoppingList, removes Item if found. 
*********************************************************************/
void List::removeItem(std::string name)
{
	
	for (int i = 0; i < size; i++)
	{
		if ((shoppingList[i] != NULL) && shoppingList[i]->getName() == name)
		{
				inventory--;
				std::cout << "Removed: " << shoppingList[i]->getName() << "\n";
				delete shoppingList[i];
				shoppingList[i] = NULL;
				return;			
		}
	}
	std::cout << "Item not found: " << name << "\n";
	return;
	
}
/*********************************************************************
** Function: addToList
** Description: Takes ptr to Item and adds creates new list of size
** oldList + 1. Only needs to be called from addItem method
*********************************************************************/
void List::addToList(Item* item) //Add to list size
{
	int oldSize = size;
	size++; //New list size
	Item** newList = new Item*[size]; //Create new temp list with max size
	for (int i = 0; i < oldSize; i++) //Copy contents into new list
	{
		newList[i] = shoppingList[i];
	}
	newList[size - 1] = item; //Insert item into end of list

	delete[] shoppingList;
	shoppingList = new Item*[size]; //Creat new shoppingList with max size
	for (int i = 0; i < size; i++) //Copy newList back into shoppinglist and copy contents of temp list into it
	{
		shoppingList[i] = newList[i];
	}	
	delete[] newList;
}
/*********************************************************************
** Function: displayList
** Description: Prints contents of shoppingList to screen. Includes all
** information for each item. Also prints total list price and total items.
*********************************************************************/
void List::displayList()
{
	double totalPrice = 0;
	int totalItems = 0;
	std::cout << "Shopping List\n";
	for (int i = 0; i < size; i++)
	{
		if (shoppingList[i] != NULL)
		{
			totalItems++;
			totalPrice += shoppingList[i]->itemPrice();
			shoppingList[i]->print();
		}
	}
	std::cout << "Total Items: " << totalItems << "\n";
	std::cout << "Cart Total: " << totalPrice << "\n";
}
