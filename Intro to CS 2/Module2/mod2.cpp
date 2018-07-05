/*******************************************************
**Program Filename: mod2.cpp
**Author: Brent Doil
**Date: 5/13/2016
**Description: Module 2 main method
*********************************************************/

#include "Stack.hpp"
#include "Queue.hpp"
#include <string>


int main()
{
	Stack myStack;
	std::cout << "Enter a series of characters then hit enter. \nThey will be displayed in reverse order FILO.\n";
	std::string stackString;
	
	std::getline(std::cin, stackString);
	std::cout << "Adding to the stack...\n";
	for (unsigned int i = 0; i < stackString.length(); i++)
	{
		std::cout << stackString.at(i);
		myStack.add(stackString.at(i));
		
	}
	std::cout << "\nRemoving from the stack...\n";
	while (!myStack.empty())
	{
		std::cout << myStack.remove();
	}
	std::cout << "\n";
	
	Queue myQueue;
	std::cout << "Enter a series of characters then hit enter. \nThey will be displayed in order FIFO.\n";
	std::string queueString;
	
	std::getline(std::cin, queueString);
	std::cout << "Adding to the queue...\n";
	for (unsigned int i = 0; i < queueString.length(); i++)
	{
		std::cout << queueString.at(i);
		myQueue.add(queueString.at(i));
		
	}
	std::cout << "\nRemoving from the queue...\n";
	while (!myQueue.empty())
	{
		std::cout << myQueue.remove();
	}
	std::cout << "\n";
	
	return 0;
	

}