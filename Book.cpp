#ifndef BOOK_CPP
#define BOOK_CPP

#include <iostream>
#include <string>
#include "Book.hpp"
#include "Account.hpp"

using namespace std;

bool Book::isbookoverdue() //Retrieve whether or not a book is overdue
{
	if(isbookavailable()==true)//If the book is available
	{
		isbookdue=false;//It cant be overdue
		return isbookdue;
	}
	else//If the book is checkout
	{
		if(Time::gettime()>duedate)//If time is greater than the due date
		{
			isbookdue=true;//The book is overdue
			return isbookdue;
		}
		else//If time is less than or equal to the due date
		{
			isbookdue=false;//The book is not overdue
			return isbookdue;
		}
	}
}

void Book::displaybook()//Function to be used by the "BOOK" to display the information about a book
{
	cout<<"Title: "<<"\""<<gettitle()<<"\""<<endl;//Display the title
	cout<<"Author: "<<getauthor()<<endl;//Display the author
	cout<<"BookID#: "<<getid()<<endl;//Display the ID
	cout<<"Genre: "<<getgenre()<<endl;//Display the genre
	cout<<"Populatiry Score: "<<getpopscore()<<endl;//Display the popularity score
	if(isbookavailable()==true)//Checks to see if the book is borrowed
	{
		cout<<"AVAILABLE"<<endl;//Display books availability
	}
	else//If book is checked out
	{
		cout<<"Borrower AccountID#: "<<getbookuser()->getuserid()<<endl;//Display account that has checked out the book
		cout<<"Due date: "<<getduedate()<<endl;//Display the books due date
		cout<<"Times renewed: "<<getrenewamount()<<endl;//Display the amount of times the book is renewed
		//setbookoverdue();//Determine if the book is overdue;
		if(isbookoverdue()==true)//If the book is overdue
		{
			cout<<"OVERDUE"<<endl;//Display overdue
		}
	}
	cout<<""<<endl;//New line
}

void Book::displaybookinaccount()//Function to be used by the "ACCOUNT" command to display all the books in a single account
{
	cout<<'\t'<<"Title: "<<"\""<<gettitle()<<"\""<<endl;//Display the title
	cout<<'\t'<<"Author: "<<getauthor()<<endl;//Display the author
	cout<<'\t'<<"BookID#: "<<getid()<<endl;//Display the ID
	cout<<'\t'<<"Genre: "<<getgenre()<<endl;//Display the genre
	cout<<'\t'<<"Populatiry Score: "<<getpopscore()<<endl;//Display the popularity score
	cout<<'\t'<<"Due date: "<<getduedate()<<endl;//Display books duedate
	cout<<'\t'<<"Times renewed: "<<getrenewamount()<<endl;//Display the amount of times its been renewed
	//setbookoverdue();//Determine if the book is overdue;
	if(isbookoverdue()==true)//If the book is overdue
	{
		cout<<'\t'<<"OVERDUE"<<endl;//Display overdue
	}
}

void Book::renewabook()//Function to be used by the "RENEW" command
{
	updaterenew();//Update the amount of times the book is renewed
	setrenewduedate();//Update the due date
	displaybookinaccount();//Display the books information
	cout<<'\t'<<"Book successfully renewed."<<endl;
}

bool Book::didaccountcheckthisbookoutbefore(Account* account)//Determines if a book has been checked out by a user already
{
	if(bookuserhistory.count(account)==0)//Return false if it hasn't
	{
		return false;
	}
	else//Return true if it has
	{
		return true;
	}
}

#endif