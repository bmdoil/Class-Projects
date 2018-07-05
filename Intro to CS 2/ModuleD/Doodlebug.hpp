/*******************************************************
**Program Filename: Doodlebug.hpp
**Author: Brent Doil
**Date: 4/15/2016
**Description: Doodlebug class interface
*********************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP
#include "Critter.hpp"

class Doodlebug : public Critter
{
private:
	int count;
	int eat;
	
public:
	Doodlebug();
	~Doodlebug() {};
	virtual Doodlebug* Breed();
	virtual void Eat();
	bool Starve();
	const int STARVED = 3;
	const int BREED = 8;
};
#endif // !DOODLEBUG_HPP


