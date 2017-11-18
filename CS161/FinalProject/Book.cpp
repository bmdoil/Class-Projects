/*********************************************************************
** Author: Brent Doil
** Date: 3/7/2016
** Description: Book class implementation file
*********************************************************************/

#include "Book.hpp"
/*********************************************************************
** Description: Constructor for Book object. Sets idCode, title and author.
*********************************************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
	checkedOutBy = NULL;
	requestedBy = NULL;
	location = ON_SHELF;
}

std::string Book::getIdCode() //gets idCode
{
	return idCode;
}

std::string Book::getTitle() //gets title
{
	return title;
}

std::string Book::getAuthor() //gets author
{
	return author;
}

int Book::getCheckOutLength() //gets CHECK_OUT_LENGTH
{
	return CHECK_OUT_LENGTH;
}

Locale Book::getLocation() //gets location (Locale) of book
{
	return location;
}

Patron* Book::getCheckedOutBy() //gets Patron who checked out book
{
	return checkedOutBy;
}

Patron* Book::getRequestedBy() //gets Patron who requested book
{
	return requestedBy;
}

int Book::getDateCheckedOut() //gets date the book was checked out
{
	return dateCheckedOut;
}

//Setters


void Book::setLocation(Locale loc) //sets location (Locale) of book
{
	location = loc;
}

void Book::setCheckedOutBy(Patron* chOut) //sets Patron that checked out book
{
	checkedOutBy = chOut;
}

void Book::setRequestedBy(Patron* reBy) //sets Patron that requested book
{
	requestedBy = reBy;
}

void Book::setDateCheckedOut(int date) //sets date the book was checked out
{
	dateCheckedOut = date;
}