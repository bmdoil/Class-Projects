/*********************************************************************
** Author: Brent Doil
** Date: 2/8/2016
** Description: Assignment 6 Point.cpp
*********************************************************************/

#include "Point.hpp"
//default constructor
Point::Point()
{
	setXCoord(0.0);
	setYCoord(0.0);
}
//constructor
Point::Point(double x, double y)
{
	setXCoord(x);
	setYCoord(y);
}
//setters
void Point::setXCoord(double x)
{
	xCoord = x;
}

void Point::setYCoord(double y)
{
	yCoord = y;
}

//getters
double Point::getXCoord() const
{
	return xCoord;
}
double Point::getYCoord() const
{
	return yCoord;
}

double Point::distanceTo(const Point &p)
{
	double xCoordCalc = pow(p.getXCoord() - getXCoord(), 2.0);
	double yCoordCalc = pow(p.getYCoord() - getYCoord(), 2.0);
	double distanceTo = sqrt(xCoordCalc + yCoordCalc);
	return distanceTo;
}