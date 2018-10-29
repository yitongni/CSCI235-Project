#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>
#include <set>

#include "Time.hpp"

using namespace std;

class Account;

class Book
{
public:

	//Constructors 
	Book(){}//Default
	~Book(){}
	Book(int id, string booktitle, string writer, string type, int popularityscore)//Makes a book with given information
	{
		ID=id;
		title=booktitle;
		popscore=popularityscore;
		author=writer;
		genre=type;
	}

	//Functions that retrieve the data members that a book has
	int getid(){ return ID; } //Retrieve the book's id
	int getpopscore(){ return popscore; } //Retrieve the book's popularity score
	string gettitle(){ return title; } //Retrieve the book's title
	string getauthor(){ return author; } //Retrieve the book's author
	string getgenre(){ return genre; } //Retrieve the book's genre
	int getrenewamount(){ return amountofrenew; } //Retrieve the amount of times a book has been renewed
	int getduedate(){ return duedate; } //Retrieve the due date
	bool isbookavailable(){ return availability; } //Retrieve the availability of a book
	bool isbookoverdue();//{ return isbookdue; } //Retrieve whether or not a book is overdue
	Account* getbookuser(){ return user; } //Retrieve the book's user if the book is checkout

	//Functions that displays a book
	void displaybook(); //To be used for the "BOOK" command
	void displaybookinaccount(); //To be used for the "ACCOUNT" command

	//Mutator functions to changes the data members
	void updatepopscore(){ popscore+=1; } //Update popularity score whenever a book it checkout by a new user.
	void setduedate(int num){ duedate=num; } //Set books current due date from reading from file
	void setcheckoutduedate(){ duedate=Time::gettime()+15; } //Set books due date when checking out from library
	void setrenewduedate(){ duedate+=5; } //When a book is renewed its due date is 5 + current due date
	void setrenewamount(int num){ amountofrenew=num; } //Set the amount of time a book has been renewed from the file
	void updaterenew(){ amountofrenew+=1; } //Whenever a book is renewed, the amount of times the books been renewed goes up by 1
	void resetrenew(){ amountofrenew=0; } //When a book is returned, the amount of times the book has been renewed resets to 0;
	void setavailability(bool flag) { availability=flag; } //When a book is checked out it becomes unavailable, likewise, when it's returned, it becomes available.
	void updateuser(Account* a_user) { user=a_user; } //Set the book's user when checking out
	void deleteuser() { user=NULL; } //When a book is returned, it doesn't have a user
	//void setbookoverdue(); //Determines if a book is overdue
	void renewabook(); //Renews a book
	void updatebookuserhistory(Account* account){ bookuserhistory.insert(account); } //Store an account in books user history. To be used by pop score to determine if popularity needs to go up
	void deleteanaccountfrombookcheckouthistory(Account* account){ bookuserhistory.erase(account); } //If an account is deleted, delete is from books user history too
	bool didaccountcheckthisbookoutbefore(Account* account); //Checks bookuserhistory to see if the account has checked the book out before

private:

	int ID;
	int duedate;
	int popscore=0;
	int amountofrenew=0;
	string title;
	string author;
	string genre;
	Account* user=NULL;
	set<Account*> bookuserhistory;
	bool availability=true;
	bool isbookdue=false;
	
};

// #include "Book.cpp"
#endif