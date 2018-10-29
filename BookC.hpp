#ifndef BOOKC_HPP
#define BOOKC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <fstream>
#include <algorithm>

#include "Book.hpp"
#include "Account.hpp"

using namespace std;

class BookC
{

public:

	BookC(){}
	~BookC();

	//Reads input file
	void readbookfile(string bookfile); //Populates the book collection with books

	//Getter functions
	int amountofbooks() { return bookcollection.size(); }
	int amountofbooksoverdue();
	Book* book(int bookid)
	{
		return bookcollection[bookid];
	}

	//Adds a book to collection
	void addbook(Book* book);

	//Command functions
	void getbook(int bookid); //BOOK
	void browsebook(string criteria); //BROWSE
	void searchphrase(string criteria, string phrase); //SEARCH
	void addB(); //ADDB
	void removeB(int bookid); //REMOVEB
	void exportbook(string bookfile); //EXPORT

	//Helper functions
	bool doesbookexist(int bookid);
	bool doesbookexistfromaccountfile(int bookid);
	
	static bool sortbytitle(Book* book1, Book* book2);
	static bool sortbyid(Book* book1, Book* book2);
	static bool sortbyauthor(Book* book1, Book* book2);
	static bool sortbypopularity(Book* book1, Book* book2);
	static bool sortbygenre(Book* book1, Book* book2);

private:

	map<int, Book*> bookcollection;
	set<int> setofid;
	set<pair<string, string>> titleauthorpair;

};

#endif