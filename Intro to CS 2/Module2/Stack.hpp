/*******************************************************
**Program Filename: Stack.hpp
**Author: Brent Doil
**Date: 5/13/2016
**Description: Stack class interface
*********************************************************/

#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

class Stack
{
private:
	struct StackNode
	{
		char node;
		StackNode* next;
		StackNode(char n, StackNode* nextNode = NULL)
		{
			node = n;
			next = nextNode;
		}
	};
	StackNode* current;

public:
	Stack() { current = NULL; };
	~Stack();
	void add(char &);
	char remove(); 
	bool empty() const;

};
#endif // !STACK_HPP

