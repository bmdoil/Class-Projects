/*******************************************************
**Program Filename: Pikachu.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: pikachu interface
*********************************************************/

#ifndef PIKACHU_HPP
#define PIKACHU_HPP

#include "Pokemon.hpp"

class Pikachu : public Pokemon
{
protected:
	//Attacks
	Attack* att1;
	Attack* att2;
	Attack* att3;
public:
	Pikachu(std::string, int);
	~Pikachu();
	void attackPokemon(Pokemon*);
	void attackAI(Pokemon*);

	
};

#endif // !PIKACHU_HPP

