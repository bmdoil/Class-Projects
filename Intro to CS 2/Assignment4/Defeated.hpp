#ifndef DEFEATED_HPP
#define DEFEATED_HPP
#include "Creature.hpp"
class Defeated //stack to hold losers
{
private:
	struct DefeatNode
	{
		Creature* loser;
		DefeatNode* next;
		DefeatNode(Creature* l, DefeatNode* n)
		{
			loser = l;
			next = n;
		}
	};
	DefeatNode* current;
public:
	Defeated() { current = NULL; };
	~Defeated();
	void add(Creature*);
	Creature* remove();
	bool empty() const;


};

#endif