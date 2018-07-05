/*********************************************************************
** Author: Brent Doil
** Date: 2/8/2016
** Description: Assignment 6 Point.hpp
*********************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

#include <math.h>


class Point
{
private:
	double xCoord;
	double yCoord;

public:
	//default constructor
	Point();

	//constructor
	Point(double x, double y);

	//setters
	void setXCoord(double x);
	void setYCoord(double y);

	//getters
	double getXCoord() const;
	double getYCoord() const;
	double distanceTo(const Point &p);

};

#endif // !Point_hpp

