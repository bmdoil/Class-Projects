/*******************************************************
**Program Filename: Queue.hpp
**Author: Brent Doil
**Date: 5/13/2016
**Description: Queue class interface
*********************************************************/

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
class Queue
{
private:
	struct QueueNode
	{
		int node;
		QueueNode* next;
		QueueNode(char n, QueueNode* nextNode = NULL)
		{
			node = n;
			next = nextNode;
		}
	};
	QueueNode* front = NULL;
	QueueNode* back = NULL;
public:
	Queue();
	~Queue();
	void add(int &);
	char remove();
	bool empty() const;

};
#endif // !QUEUE_HPP

