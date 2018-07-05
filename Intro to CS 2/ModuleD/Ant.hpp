/*******************************************************
**Program Filename: Ant.hpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Ant class interface
*********************************************************/

#ifndef ANT_HPP
#define ANT_HPP
#include "Critter.hpp"

class Ant : public Critter
{
private:
	int count;	
public:
	Ant();
	~Ant() {};
	virtual Ant* Breed();
	const int BREED = 3;
};
#endif // !ANT_HPP

