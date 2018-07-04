/*********************************************************************
** Author: Brent Doil
** Date: 3/7/2016
** Description: Library class implementation file
*********************************************************************/

#include "Library.hpp"
/*********************************************************************
** Description: Constructor for Library object.Current date set to 0
*********************************************************************/
Library::Library()
{
	currentDate = 0;
	
	
}

void Library::addBook(Book* b) //Takes pointer to book and adds to vector holdings
{
	
	holdings.push_back(b);
	

}

void Library::addPatron(Patron* p) //Takes pointer to patron and adds to vector members
{
	members.push_back(p);
}

/*********************************************************************
** Description: Checks out a book to a patron. Takes strings for pID
** and bID. Returns a string depending on location of book.
*********************************************************************/
std::string Library::checkOutBook(std::string pID, std::string bID)
{
	Book* book = getBook(bID);
	Patron* patron = getPatron(pID);
	
	if (book == NULL) //if book is not in library, return book not found
		return "Book not found.";
	
	if (patron == NULL) //if patron is not in library, return patron not found
		return "Patron not found.";
	
	if (book->getLocation() == CHECKED_OUT) //if book is already checked out, return book already checked out
		return "Book already checked out.";

	if (book->getLocation() == ON_HOLD_SHELF) //if book is on hold by this patron, update book members, check out to patron and return successful
		if (book->getRequestedBy()->getIdNum() == patron->getIdNum())
		{
			book->setRequestedBy(NULL);
			book->setCheckedOutBy(patron);
			book->setDateCheckedOut(currentDate);
			book->setLocation(CHECKED_OUT);
			patron->addBook(book);
			return "Check out successful.";
		}
		else //if the book is on hold by another Patron, return "book on hold by other patron"
		{
			return "Book on hold by other patron";
		}
	
	else //else update the book members, check out to patron, and return successful
	{
		book->setCheckedOutBy(patron);
		book->setDateCheckedOut(currentDate);
		book->setLocation(CHECKED_OUT);
		patron->addBook(book);
		return "Check out successful.";
	}	
	
}
/*********************************************************************
** Description: Returns a book to the library. Takes string bID.
*********************************************************************/
std::string Library::returnBook(std::string bID)
{

	Book* book = getBook(bID); //if the specified Book is not in the Library, return book not found
	if (book == NULL)
	{
		return "Book not found.";
	}
	if (book->getLocation() == ON_SHELF) //if the Book is not checked out, return book already in library
	{
		return "Book already in library.";
	}
	else
	{
		//Update Patron's checked out books
		book->getCheckedOutBy()->removeBook(book);
		book->setCheckedOutBy(NULL);
		book->setDateCheckedOut(-1);

		//Update book location to ON_SHELF or ON_HOLD_SHELF
		if (book->getRequestedBy() == NULL)
		{
			book->setLocation(ON_SHELF);  
			return "Return successful.";
		}
		else
		{
			book->setLocation(ON_HOLD_SHELF);
			return "Return successful.";
			
		}
	}	
}

/*********************************************************************
** Description: Requests a book for a patron. Takes string pID and bID
*********************************************************************/
std::string Library::requestBook(std::string pID, std::string bID)
{
	Book* book = getBook(bID);
	Patron* patron = getPatron(pID);

	if (book == NULL) //if the specified Book is not in the Library, return "book not found"
	{
		return "Book not found.";
	}
	if (patron == NULL) //if the specified Patron is not in the Library, return "patron not found"
	{
		return "Patron not found.";
	}
	if (book->getRequestedBy() != NULL) //f the specified Book is already requested, return "book already on hold"
	{
		return "Book already on hold.";
	}
	else
	{
		//Update the Book's requestedBy; if the Book is on the shelf, update its location to on hold; return "request successful"
		book->setRequestedBy(patron);
		if (book->getLocation() == ON_SHELF)
		{
			book->setLocation(ON_HOLD_SHELF);
		}
		return "Request successful.";
	}

}
/*********************************************************************
** Description: Takes the amount that is being paid by a patron for fine. 
*********************************************************************/
std::string Library::payFine(std::string pID, double payment)
{

	Patron* patron = getPatron(pID); //if the specified Patron is not in the Library, return "patron not found"
	if (patron == NULL)
	{
		return "Patron not found.";
	}
	else
	{
		patron->amendFine(-payment);
		return "Payment successful.";
	}
		
}
/*********************************************************************
** Description: Adds one to the current date. Iterates through all patrons
** and their checked out books. Determines whether any of those books are overdue
** if they are overdue, add fine to patron
*********************************************************************/
void Library::incrementCurrentDate()
{
	currentDate++;

	for (unsigned int i = 0; i < members.size(); i++)
	{
		for (unsigned int j = 0; j < members.at(i)->getCheckedOutBooks().size(); j++)
		{
			if ((members.at(i)->getCheckedOutBooks().at(j)->getDateCheckedOut() + 21 < currentDate))
			{
					members.at(i)->amendFine(0.1);
			}
		}
	}
}
/*********************************************************************
** Description: Returns a pointer to a Patron by taking string pID as a
** parameter, or NULL if no such Patron is in members
*********************************************************************/
Patron* Library::getPatron(std::string pID)
{
	for (unsigned int i = 0; i < members.size(); i++)
		if (members.at(i)->getIdNum() == pID)
		{
			return members.at(i);
		}
	return NULL;

}
/*********************************************************************
** Description: Returns a pointer to a Book by taking string bID as a
** parameter, or NULL if no such Book is in holdings
*********************************************************************/
Book* Library::getBook(std::string bID)
{
	
	for (unsigned int i = 0; i < holdings.size(); i++)
		if (holdings.at(i)->getIdCode() == bID)
		{
			return holdings.at(i);
		}
	return NULL;

}