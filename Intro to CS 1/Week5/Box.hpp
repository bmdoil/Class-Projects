/*********************************************************************
** Author: Brent Doil
** Date: 1/28/2016
** Description: Assignment 5.a Box.hpp
*********************************************************************/

#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>

using namespace std;

class Box
{
private:
	double height;
	double width;
	double length;

public:
	//default constructor
	Box();

	//constructor with parameters
	Box(double w, double l, double h);

	//destructor
	//~Box();

	//getters
	double getVolume() const;
	double getSurfaceArea() const;

	//setters
	bool setWidth(double w);
	bool setLength(double l);
	bool setHeight(double h);
};


#endif // !BOX_H

