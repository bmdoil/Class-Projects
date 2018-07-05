/*******************************************************
**Program Filename: mod1Main.cpp
**Author: Brent Doil
**Date: 4/24/2016
**Description: Module 1 main program
*********************************************************/


#include "Mod1.hpp"
#include "CS162.hpp"



int main()
{
	std::cout << "Module 1\n";
	std::cout << "This program demonstrates recursion using three functions.\nYou can reverse a string, sum an array or calculate a triangular number.\n";
	while (true)
	{
		int choice = menu();
		switch (choice)
		{
		case 1: 
		{
			std::string inString;
			std::cout << "Please enter a string: ";
			std::getline(std::cin, inString);
			reverseString(inString);
			break;
		}
		case 2:
		{
			//Sum Array
			double* arr = NULL;
			int count = 0;
			int arrSize = 0;
			std::string input;
			arrSize = validNum("Let's enter an array of numbers.\nHow many numbers would you like to enter? ", "Please enter an integer >= 1: ", 1);
			arr = new double[arrSize]; //Allocate new array
			std::cout << "Enter numbers into the array or q to quit at any time.\n";
			while (count < arrSize)
			{
				std::cin >> input;
				if (input[0] == 'q') break; //Sentinel char q to break loop early
				std::stringstream ss(input);
				ss >> arr[count];
				count++;
			}
			std::cout << "Sum of the array is: " << sumArray(arr, count) << "\n";
			//Clean up
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			delete [] arr;
			arr = NULL;
			break;
		}
		case 3:
		{
			//N Triangles
			int N = 0;
			N = validNum("Enter an integer to calculate its triangular #: ", "Enter a positive integer: ", 1, std::numeric_limits<int>::max());
			std::cout << "The triangular # of " << N << " is: " << triangleNum(N) << "\n";
			break;
		}
		case 4:
			return 0;
		}
	}
	
	

	

	
	
}