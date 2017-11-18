/*********************************************************************
** Author: Brent Doil
** Date: 3/7/2016
** Description: Book class implementation file
*********************************************************************/

#include "Book.hpp"
/*********************************************************************
** Description: Constructor for Book object. Sets idCode, title and author.
*********************************************************************/
Book::Book(std::string id, std::string t, std::string a)
{
	idCode = id;
	title = t;
	author = a;
	checkedOutBy = NULL;
	requestedBy = NULL;
	location = ON_SHELF;
}
std::string Book::getIdCode(){return idCode;}
std::string Book::getTitle(){return title;}
std::string Book::getAuthor(){return author;}
int Book::getCheckOutLength(){return CHECK_OUT_LENGTH;}
Locale Book::getLocation(){return location;}
Patron* Book::getCheckedOutBy(){return checkedOutBy;}
Patron* Book::getRequestedBy(){return requestedBy;}
int Book::getDateCheckedOut(){return dateCheckedOut;}
void Book::setLocation(Locale loc){location = loc;}
void Book::setCheckedOutBy(Patron* chOut){checkedOutBy = chOut;}
void Book::setRequestedBy(Patron* reBy){requestedBy = reBy;}
void Book::setDateCheckedOut(int date){dateCheckedOut = date;}