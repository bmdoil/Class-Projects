/*******************************************************
**Program Filename: Pokemon.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: pokemon interface
*********************************************************/

#ifndef POKEMON_HPP
#define POKEMON_HPP
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <string>
#include "Attack.hpp"
#include "CS162.hpp"

class Pokemon
{
protected:
	
	const int MAXLVL = 20;
	double lvlMod = 1.1;

	//Combat stats
	double maxHP;
	double HP;
	double attack;
	double defense;
	double speed;
	

	//Identifiers	
	std::string name;
	int level;
	bool alive;	
	
public:	
	Pokemon();
	virtual ~Pokemon() {};


	virtual void attackPokemon(Pokemon*) = 0;
	virtual void attackAI(Pokemon*) = 0;
	void levelUp();
	void setName(std::string);	
	std::string getName();	
	
	

	double getDefense() const;
	double getAttack() const;
	double getSpeed() const;
	double getHP() const;
	int getLevel() const;
	void loseHP(double);
	void setHP(double);
	void setHPMax();

	void printStats();

	void setAlive(bool);
	bool getAlive();
	
	

};

#endif // !POKEMON_HPP

