
#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

class Patron;

// These three locations are mutually exclusive, but note that
// a Book can be on request for a Patron while being checked
// out to another Patron.  In that case the Book's location is
// CHECKED_OUT, and when it is returned, it's location will
// become ON_HOLD_SHELF.
enum Locale { ON_SHELF, ON_HOLD_SHELF, CHECKED_OUT };


class Book
{
private:
	//Unique identifier for the book
	std::string idCode;
	//Title of the book. Cannot be assumed to be unique
	std::string title;
	//Author. These three can be initialized directly with the constructor
	std::string author;
	//Can be ON_SHELF, ON_HOLD_SHELF, or CHECKED_OUT
	Locale location;
	//Pointer to the Patron who has it checked out (if any)
	Patron* checkedOutBy;
	//Pointer to the Patron who has requested it (if any). Only one at a time
	Patron* requestedBy;
	//When a book is checked out. Set to the currentDate of the Library.
	int dateCheckedOut;
public:
	static const int CHECK_OUT_LENGTH = 21;
	//Takes an idCode, title and author. checkedOutBy and requestedBy should be initialized to NULL.
	Book(std::string idc, std::string t, std::string a);
	int getCheckOutLength();
	//Returns idCode
	std::string getIdCode();
	//Returns title
	std::string getTitle();
	//Returns author
	std::string getAuthor();
	//Returns current location
	Locale getLocation();
	//Sets location, takes Locale enum
	void setLocation(Locale);
	//Gets pointer to Patron who checked out Book
	Patron* getCheckedOutBy();
	//Sets pointer to Patron who checked out Book
	void setCheckedOutBy(Patron*);
	//Gets pointer to Patron who requested Book
	Patron* getRequestedBy();
	//Sets pointer to Patron who requested Book
	void setRequestedBy(Patron*);
	//Gets date checked out
	int getDateCheckedOut();
	//Sets date checked out, takes int
	void setDateCheckedOut(int);
};


#endif
