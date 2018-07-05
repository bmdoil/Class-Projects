/*******************************************************
**Program Filename: Mod1.cpp
**Author: Brent Doil
**Date: 4/24/2016
**Description: Module 1 function implementation
*********************************************************/

#include "Mod1.hpp"

void reverseString(std::string s)
{
	
	if (s.length() > 0)
	{
		std::cout << s.at(s.length() - 1);
		s.erase(s.length() - 1, 1);
		reverseString(s);
	}
	else std::cout << "\n";
}

double sumArray(double arr[], int size)
{	
	if (size == 0)
	{
		return 0;					
	}
	else
	{
		return arr[size - 1] + sumArray(arr, size - 1);
	}	
}

int triangleNum(int N)
{
	if (N == 1)
	{
		return 1;
	}
	else
	{
		return N + triangleNum(N - 1);
	}
}