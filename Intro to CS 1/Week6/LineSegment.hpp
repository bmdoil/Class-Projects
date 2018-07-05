/*********************************************************************
** Author: Brent Doil
** Date: 2/8/2016
** Description: Assignment 6 LineSegment.hpp
*********************************************************************/

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "Point.hpp"

class LineSegment
{
private:
	Point End1;
	Point End2;
public:
	//constructor
	LineSegment(Point p1, Point p2);

	//setters
	void setEnd1(Point p1);
	void setEnd2(Point p2);

	//getters
	Point getEnd1() const;
	Point getEnd2() const;
	double slope();
	double length();

};






#endif // !LINESEGMENT_HPP
