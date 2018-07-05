/*******************************************************
**Program Filename: Stack.cpp
**Author: Brent Doil
**Date: 5/13/2016
**Description: Stack class implementation
*********************************************************/

#include "Stack.hpp"


void Stack::add(char &input)
{
	current = new StackNode(input, current);
}
Stack::~Stack()
{
	while (!empty())
	{
		remove();
	}
	delete current;
}
char Stack::remove()
{
	StackNode* oldNode;
	char temp;

	if (empty())
	{
		std::cout << "Stack is empty!\n";
		return '\0';
	}
	else
	{
		temp = current->node;
		oldNode = current;
		current = current->next;
		delete oldNode;
		return temp;
	}
}
bool Stack::empty() const
{
	if (current == NULL)
	{
		return true;
	}
	else return false;
}