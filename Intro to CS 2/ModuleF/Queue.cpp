/*******************************************************
**Program Filename: Queue.cpp
**Author: Brent Doil
**Date: 5/13/2016
**Description: Queue class implementation
*********************************************************/

#include "Queue.hpp"

Queue::Queue()
{
	front = NULL;
	back = NULL;
}
Queue::~Queue()
{
	while (!empty())
	{
		remove();
	}
}
void Queue::add(int &input)
{
	if (empty())
	{
		front = new QueueNode(input);
		back = front;
	}
	else
	{
		back->next = new QueueNode(input);
		back = back->next;
	}
}

char Queue::remove() 
{	
	QueueNode* oldNode;
	int temp;
	if(empty())
	{
		//std::cout << "Queue is empty!\n";
		return '\0';
	}
	else
	{
		temp = front->node;
		oldNode = front;
		front = front->next;	
		delete oldNode;
		return temp;
	}
	
	
}
bool Queue::empty() const
{
	if (front == NULL)
	{
		return true;
	}
	else return false;
}