/*********************************************************************
** Author: Brent Doil
** Date: 2/15/2016
** Description: Assignment 7 findMode.cpp
*********************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> findMode(int array[], int arraySize);
void showValues(vector <int> vect);


int main()
{
	int SIZE = 10;
	int array1[] = {8,4,5,3,4,8,4,3,4,8};
	
	vector <int> results = findMode(array1,SIZE);
	showValues(results);

	return 0;
}


vector <int> findMode(int array[], int arraySize)
{
	int modeCount = 0;
	int modeMax = 0;
	vector<int> modeVect;

	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			if (array[i] == array[j])
			{
				modeCount++;
				if (modeCount > modeMax)
				{
					modeMax = modeCount;
				}
			}
		}
		modeCount = 0;
	}
	

	sort(array, array + arraySize);

	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			if (array[i] == array[j])
			{
				modeCount++;
				if (modeCount == modeMax)
				{
					modeVect.push_back(array[i]);
					i += modeMax - 1;
				}
			}
		}
		modeCount = 0;
	}
	return modeVect;
}
void showValues(vector <int> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << endl;
	}
}
