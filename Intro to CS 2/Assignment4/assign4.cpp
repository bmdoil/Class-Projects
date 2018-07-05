/*******************************************************
**Program Filename: assign4.cpp
**Author: Brent Doil
**Date: 5/22/2016
**Description: Assignment 4 main method
*********************************************************/

#include "FightLogic.hpp"
#include "CS162.hpp"


int main()
{
	//Choose team names
	std::string team1Name;
	std::string team2Name;
	std::cout << "Choose a name for Team 1: ";
	std::getline(std::cin, team1Name);
	std::cout << "Choose a name for Team 2: ";
	std::getline(std::cin, team2Name);

	//Instantiate teams and loser stack
	Team team1(team1Name);
	Team team2(team2Name);
	Defeated loserStack;


	int creatureType;
	std::string creatureName;
	//Pick a team size
	int teamSize = validNum("Enter a team size ", "Please enter a valid number >= 2 ", 2);

	//Player 1 selects their lineup
	std::cout << team1.getName() << " add your creatures!\n";
	std::cout << "[1]Barbarian\n[2]Baba Yaga\n[3]Blue Men\n[4]Harry\n[5]Medusa\n";
	for (int i = 1; i <= teamSize; i++)
	{
		
		creatureType = validNum("Enter the type of creature: ", "Enter a number between 1 and 5: ", 1, 5);
		std::cout << "Name the creature: ";
		std::getline(std::cin, creatureName);
		team1.newCreat(creatureType, creatureName, team1Name);
	}

	//Player 2 selects their lineup
	std::cout << "Team 2: Add Your Creatures\n";
	std::cout << "[1]Barbarian\n[2]Baba Yaga\n[3]Blue Men\n[4]Harry\n[5]Medusa\n";
	for (int i = 1; i <= teamSize; i++)
	{

		creatureType = validNum("Enter the type of creature: ", "Enter a number between 1 and 5: ", 1, 5);
		std::cout << "Name the creature: ";
		std::getline(std::cin, creatureName);
		team2.newCreat(creatureType, creatureName, team2Name);
	}
	//While both teams have creatures in their lineup
	while (!team1.empty() && !team2.empty())
	{
		//Set up temp pointers
		Creature* creat1 = NULL;
		Creature* creat2 = NULL;
		Creature* winner = NULL;
		Creature* loser = NULL;
		//Remove creature from front of each queue
 		creat1 = team1.remove();
		creat2 = team2.remove();
		//Battle
		winner = fightLogic(creat1, creat2);
		//If creature from team 1 wins, revitalize and place it back in queue. Place creature from team 2 in loser stack
		if (winner == creat1)
		{
			std::cout << creat1->getName() << " from " << team1.getName() << " wins!\n";
			std::cout << creat1->getName() << " is revitalized and regenerates some strength.\n";
			creat1->revitalize();
			team1.addExisting(creat1);
			loser = creat2;
			loserStack.add(loser);
		}
		//Vice versa for creature from team 2 winning
		else
		{
			std::cout << creat2->getName() << " from " << team2.getName() << " wins!\n";
			std::cout << creat2->getName() << " is revitalized and regenerates some strength.\n";
			creat1->revitalize();
			team2.addExisting(creat2);
			loser = creat1;
			loserStack.add(loser);
		}
		std::cout << "Press enter to start the next round.";
		std::cin.get();
		std::cin.clear();
	}
	//Total number of creatures
	int totalCreat = teamSize * 2;
	//Standings array of size totalCreat
	Creature** standings = new Creature*[totalCreat];
	//Declares the winner
	if (!team1.empty())
	{
		std::cout << team1.getName() << " wins!\n";
	}
	else if (!team2.empty())
	{
		std::cout << team2.getName() << " wins!\n";		
	}
	std::cout << "The final standings are: \n";
	//Populate standings array
	for (int i = 0; i < teamSize * 2; i++)
	{
		if (!team1.empty())
		{	
			standings[i] = team1.remove();	
		}
		else if (!team2.empty())
		{
			standings[i] = team2.remove();
		}
		else
		{
			standings[i] = loserStack.remove();
		}
	}
	//Print standings
	std::cout << "Standings determined by creatures left on winning team, then last creatures to lose.\n";
	for (int i = 0; i < 3; i++)
	{
		
		std::cout << i+1 << ": " << standings[i]->getName() << " from " << standings[i]->getTeam() << ": Round wins:" << standings[i]->getRoundWin() << " Strength remaining:"
		          << standings[i]->getStrength() << " Total damage done:" << standings[i]->getDamage() << "\n";
	}
	std::cout << "Press S to see the entire list of standings, any other character to quit: ";
	char list;
	std::cin >> list;
	if (list == 'S')
	{
		for (int i = 0; i < teamSize * 2; i++)
		{

			std::cout << i + 1 << ": " << standings[i]->getName() << " from " << standings[i]->getTeam() << ": Round wins:" << standings[i]->getRoundWin() << " Strength remaining:"
				<< standings[i]->getStrength() << " Total damage done:" << standings[i]->getDamage() << "\n";
		}
	}
	delete[] standings;
	standings = NULL;
	return 0;
	
	
	
}