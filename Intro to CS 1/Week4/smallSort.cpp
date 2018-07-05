/*********************************************************************
** Author: Brent Doil
** Date: 1/20/2016
** Description: Assignment 4.b smallSort.cpp
*********************************************************************/

/*
#include <iostream>

void smallSort(int &numOne, int &numTwo, int &numThree);

int main()
{
	int a = 451;
	int b = -99;
	int c = 0;
	smallSort(a, b, c);
	std::cout << a << ", " << b << ", " << c << std::endl;

}
*/

//Pass in 3 int by reference and sort in ascending order
void smallSort(int &numOne, int &numTwo, int &numThree)
{
	int temp;
	//If num one is highest value, push it to end
	if ((numOne > numTwo) && (numOne > numThree))
	{
		temp = numOne;
		numOne = numThree;
		numThree = temp;
	}
	//If num one is > num two, swap
	if (numOne > numTwo)
	{
		temp = numOne;
		numOne = numTwo;
		numTwo = temp;
	}
	//If num two is > num three, swap
	if (numTwo > numThree)
	{
		temp = numTwo;
		numTwo = numThree;
		numThree = temp;
	}
	

}