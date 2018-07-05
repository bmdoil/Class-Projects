#include "Traffic.hpp"


Traffic::Traffic(std::string dir)
{
	srand(time(NULL));
	waitTime = 0;
	carCount = 0;
	direction = dir;
	showOutput = false;
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
		lane.push(iter);
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
		if (!lane.empty())
		{
			int wait = lane.front();
			lane.pop();
			waitTime += (iter - wait);
		}
		
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