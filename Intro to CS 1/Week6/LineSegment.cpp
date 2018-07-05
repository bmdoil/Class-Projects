/*********************************************************************
** Author: Brent Doil
** Date: 2/8/2016
** Description: Assignment 6 LineSegment.cpp
*********************************************************************/

#include "LineSegment.hpp"

//constructor
LineSegment::LineSegment(Point p1, Point p2)
{
	setEnd1(p1);
	setEnd2(p2);
}
//setters
void LineSegment::setEnd1(Point p1)
{
	End1 = p1;
	
}
void LineSegment::setEnd2(Point p2)
{
	End2 = p2;
	
}
//getters
Point LineSegment::getEnd1() const
{
	return End1;
}
Point LineSegment::getEnd2() const
{
	return End2;
}
double LineSegment::length()
{
	double length = End1.distanceTo(End2);
	return length;
	
}
double LineSegment::slope()
{
	double slope = (End2.getYCoord() - End1.getYCoord()) / (End2.getXCoord() - End1.getXCoord());
	return slope;
}
