/*********************************************************************
** Author: Brent Doil
** Date: 1/20/2016
** Description: Assignment 4.a fallDistance.cpp
*********************************************************************/

#include <math.h>

//Calculates fall distance given the parameter time as a double
double fallDistance(double time)
{
	const double gravity = 9.8;
	double distance = (1.0 / 2.0) * gravity * pow(time, 2);
	return distance;
}

