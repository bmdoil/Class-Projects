/*********************************************************************
** Author: Brent Doil
** Date: 1/28/2016
** Description: Assignment 5.a Box.cpp
*********************************************************************/
#include "Box.hpp"

bool Box::setWidth(double w)
{
	if (w > 0.0)
	{
		width = w;
		return true;
	}
	else return false;
}

bool Box::setLength(double l)
{
	if (l > 0.0)
	{
		length = l;
		return true;
	}
	else return false;

}

bool Box::setHeight(double h)
{
	if (h > 0.0)
	{
		height = h;
		return true;
	}
	else return false;
}

//default constructor
Box::Box()
{
	setWidth(1.0);
	setLength(1.0);
	setHeight(1.0);
}

//constructor with parameters
Box::Box(double w, double l, double h)
{
	setWidth(w);
	setLength(l);
	setHeight(h);
}

/*Destructor
Box::~Box()
{
	cout << "Removing boxes." << endl;
}
*/

double Box::getVolume() const
{
	double volume = height * length * width;
	return volume;
}

double Box::getSurfaceArea() const
{
	double surfaceArea = 2 * (length * width) + 2 * (length * width);
	return surfaceArea;
}
