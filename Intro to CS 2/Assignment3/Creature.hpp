#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <string>


class Creature
{
protected:
	int armor;
	int strength;
	bool alive;
	std::string name;
public:
	Creature();
	virtual ~Creature() {};
	virtual int attack() = 0;
	virtual int defend(int) = 0;
	virtual bool isAlive() = 0;	
	virtual void setName(std::string);
};

#endif // !CREATURE_HPP

