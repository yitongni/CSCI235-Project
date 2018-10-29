#ifndef ACCOUNTS_HPP
#define ACCOUNTS_HPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Book.hpp"

using namespace std;

class Account
{

public:
	//Constructor
	Account(){}//Default
	~Account(){}
	Account(int ID, string username)
	{
		id=ID;
		name=username;
	}

	//Display functions
	void displayaccount();//Display a single account along with the information of the books
	void displaybookinaccountforsorting();

	//Add books to user account
	void addbooktoaccountfromfile(Book* checkoutbook, int duedate, int renew);//Add books to user account from file
	void addbookfromcheckout(Book* booktobecheckedout);//Add books to user account from "CHECKOUT"

	//Getter functions to retrieve data members
	int getuserid()//Retrieve the user id
	{
		return id;
	}
	string getname()//Retrieve the user name
	{
		return name;
	}
	bool isitanoverdueaccount();//Determine if the account is overdue
	int amountofbookscheckedout()
	{
		return userbook.size();
	}

	//Function to help with commands
	void renewbooksinaccount();//Renew all the books
	void resetoverdueaccount()//When account has no overdue books
	{
		isoverdueaccount=false;
	}
	void deletebookfromaccount(int bookid);//When removing a book from library
	void returnabook(int bookid);//When returning a book
	void returnallbooks();//When deleting account return all books
	Book* getbook(int position)
	{
		return userbook[position];
	}


private:

	string name;
	int id;
	vector<Book*> userbook;
	bool isoverdueaccount=false;
};

// #include "Account.cpp"
#endif