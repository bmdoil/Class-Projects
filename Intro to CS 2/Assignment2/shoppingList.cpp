/*******************************************************
**Program Filename: shoppingList.cpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: Assignment 2 main method
*********************************************************/

#include "CS162.hpp"
#include "List.hpp"

int main()
{

	if (menu()) //If option to start program is chosen from menu
	{

		//Create a list
		List* shoppingList = new List;
		while (true)
		{
			std::string options = "[1] Add an item: \n[2] Remove an item: \n[3] Display shopping list: \n[4] To exit: \n";
			int choice = validNum(options, "Please enter a valid option: ", 1, 4);

			switch (choice)
			{
				case 1:
				{
					std::string name;
					std::string unit;
					int numtoBuy;
					double unitPrice;
					std::cout << "Item Name: ";
					std::getline(std::cin, name);
					std::cout << "Unit for Purchase: ";
					std::getline(std::cin, unit);
					numtoBuy = validNum("Number to Buy: ", "Enter a valid amount: ", 1);
					unitPrice = validNum("Price per Unit: ", "Enter a valid amount: ", 0.0);
					shoppingList->addItem(name, unit, numtoBuy, unitPrice);
					break;

				}
				case 2:
				{
					std::string name;
					std::cout << "Enter name of item to remove: ";
					std::getline(std::cin, name);
					shoppingList->removeItem(name);
					break;

				}
				case 3:
				{
					shoppingList->displayList();
					break;
				}
				case 4:
				{
					delete shoppingList;
					shoppingList = NULL;
					return 0;
				}

			}

		}
		return 0;
	}
}