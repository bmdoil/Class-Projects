/*********************************************************************
** Author: Brent Doil
** Date: 1/20/2016
** Description: Assignment 4.c hailstone.cpp
*********************************************************************/


/*#include <iostream>

int hailstone(int);

int main()
{
	int start;
	std::cout << "Provide a start number:";
	std::cin >> start;
	int end = hailstone(start);
	std::cout << end << std::endl;
}*/

//Counts number of steps for hailstone sequence to reach one, given an initial seed. 
int hailstone(int start)
{
	int steps = 0;
	while (start != 1)
	{
		steps++;
		if (start % 2 == 0)
		{
			start /= 2;
		}
		else
		{
			start = (start * 3) + 1;
		}
	}
	return steps;
}