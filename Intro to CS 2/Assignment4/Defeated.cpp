#include "Defeated.hpp"
/*********************************************************************
** Function: Defeated destructor
** Description: Cleans up memory for Defeated
*********************************************************************/
Defeated::~Defeated()
{
	while (!empty())
	{
		remove();
	}
	delete current;
}
/*********************************************************************
** Function: add
** Description: Adds creature to top of stack
*********************************************************************/
void Defeated::add(Creature* c)
{
	current = new DefeatNode(c, current);
}
/*********************************************************************
** Function: remove
** Description: Removes creature from stack and returns it
*********************************************************************/
Creature* Defeated::remove()
{
	DefeatNode* oldNode;
	Creature* temp;

	if (empty())
	{
		std::cout << "Loser pile is empty!\n";
		return '\0';
	}
	else
	{
		temp = current->loser;
		oldNode = current;
		current = current->next;
		delete oldNode;
		return temp;
	}
}
/*********************************************************************
** Function: empty
** Description: Checks if stack is empty
*********************************************************************/
bool Defeated::empty() const
{
	if (current == NULL)
	{
		return true;
	}
	else return false;
}
