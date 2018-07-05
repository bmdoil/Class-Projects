#include "Traffic.hpp"
#include <ctime>
#include <string>

Traffic::Traffic(std::string dir)
{
	srand(time(NULL));
	lane = new Queue;
	waitTime = 0;
	carCount = 0;
	direction = dir;
	showOutput = false;
}
Traffic::~Traffic()
{
	delete lane;
	lane = NULL;
}
void Traffic::arriving(int iter)
{
	int arrive = 0;
	arrive = (rand() % 5) + 1 + (rand() % 5) + 1;
	if (showOutput)
	{
		std::cout << arrive << " vehicles arrive in " << direction << " lane.\n";
	}	
	for (int i = 0; i < arrive; i++)
	{
		carCount++;
		lane->add(iter);
	}	
}
void Traffic::departing(int iter)
{
	int depart = 0;
	depart = (rand() % 6) + 1;
	if (showOutput)
	{
		std::cout << depart << " vehicles can depart " << direction << " lane.\n";
	}	
	for (int i = 0; i < depart; i++)
	{
		int wait = lane->remove();
		waitTime += (iter - wait);
	}

}
int Traffic::getWait() const
{
	return waitTime / carCount;
}
void Traffic::setOutPut(bool inpt)
{
	showOutput = inpt;
}