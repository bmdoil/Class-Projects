/*********************************************************************
** Author: Brent Doil
** Date: 3/7/2016
** Description: Patron class implementation file
*********************************************************************/

#include "Patron.hpp"
/*********************************************************************
** Description: Constructor for Patron object. Sets idNum and name to given params
*********************************************************************/
Patron::Patron(std::string idn, std::string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0.0;
}

std::string Patron::getIdNum() //gets IdNum 
{
	return idNum;
}

std::string Patron::getName() //gets name
{
	return name;
}

std::vector<Book*> Patron::getCheckedOutBooks() //gets vector of Patron's checked out books as Book*
{
	return checkedOutBooks;
}

void Patron::addBook(Book* b) //adds book to end of Patron's checked out books vector
{
	checkedOutBooks.push_back(b);
}

void Patron::removeBook(Book* b) //removes book from Patron's checked out books
{
	for (int i = 0; i < checkedOutBooks.size(); i++)
	{
		if (b == checkedOutBooks.at(i))
		{
			checkedOutBooks.erase(checkedOutBooks.begin() + i);
			return;
		}
		else
		{
			continue;
		}
	}
}

double Patron::getFineAmount() //gets fine that Patron owes
{
	return fineAmount;
}

void Patron::amendFine(double amount) //adds parameter to total fine
{
	fineAmount += amount;
}