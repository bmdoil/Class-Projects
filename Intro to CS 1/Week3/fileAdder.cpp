/*********************************************************************
** Author: Brent Doil	
** Date: 1/17/2016
** Description: Assignment 3.b fileAdder.cpp
*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	ifstream inputFile;
	ofstream outputFile;
	string fileName;
	int number;
	int numberSum = 0;

	//Prompt user for name of file
	cout << "What is the name of the file?\n";
	cin >> fileName;
	//Open file using c-style string
	
	inputFile.open(fileName.c_str());
	//If input is valid, read in list of integers in file. If not valid, print "could not access file"

	if (inputFile)
	{
		//Add together all integers in file
		while (inputFile >> number)
			numberSum += number;
		inputFile.close();
		//open output file called sum.txt and write sum to that file
		outputFile.open("sum.txt");
		outputFile << numberSum;
		//Close both input and output files
		inputFile.close();
		outputFile.close();
	}
	else
	{
		cout << "Could not access file.\n";
	}
	

	return 0;

}