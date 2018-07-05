/*******************************************************
**Program Filename: Squirtle.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: squirtle interface
*********************************************************/

#ifndef SQUIRTLE_HPP
#define SQUIRTLE_HPP

#include "Pokemon.hpp"
#include "Attack.hpp"
class Squirtle : public Pokemon
{
protected:
	//Attacks
	Attack* att1;
	Attack* att2;
	Attack* att3;
public:
	Squirtle(std::string, int);
	~Squirtle();
	void attackPokemon(Pokemon*);
	void attackAI(Pokemon*);
	
	
};
#endif // !SQUIRTLE_HPP

