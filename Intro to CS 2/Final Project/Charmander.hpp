/*******************************************************
**Program Filename: Charmander.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: charmander interface
*********************************************************/

#ifndef CHARMANDER_HPP
#define CHARMANDER_HPP
#include "Pokemon.hpp"
class Charmander : public Pokemon
{
protected:
	//Attacks
	Attack* att1;
	Attack* att2;
	Attack* att3;
public:
	Charmander(std::string, int);
	~Charmander();
	void attackPokemon(Pokemon*);
	void attackAI(Pokemon*);

};
#endif // !CHARMANDER_HPP

