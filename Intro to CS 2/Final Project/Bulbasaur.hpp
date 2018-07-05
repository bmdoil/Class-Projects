/*******************************************************
**Program Filename: Bulbasaur.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: bulbasaur interface
*********************************************************/

#ifndef BULBASAUR_HPP
#define BULBASAUR_HPP


#include "Pokemon.hpp"
#include "Attack.hpp"
class Bulbasaur : public Pokemon
{
protected:
	//Attacks
	Attack* att1;
	Attack* att2;
	Attack* att3;
public:
	Bulbasaur(std::string, int);
	~Bulbasaur();
	void attackPokemon(Pokemon*);
	void attackAI(Pokemon*);

	
};
#endif // !BULBASAUR_HPP
