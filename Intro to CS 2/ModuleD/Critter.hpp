/*******************************************************
**Program Filename: Critter.hpp
**Author: Brent Doil
**Date: 4/26/2016
**Description: Critter class interface
*********************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP


#include <ctime>
#include <cstdlib>

class Critter {
protected:
	char critter;
	bool moved = false;
	int count = 0;
	
public:
	Critter();
	Critter(char crit);
	virtual ~Critter() {};
	virtual Critter* Breed();
	char getCritter();
	bool setMoved(bool x);
	virtual void Eat();
	virtual bool Starve();
};

#endif // !CRITTER_HPP

