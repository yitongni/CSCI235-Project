#ifndef ACCOUNTS_CPP
#define ACCOUNTS_CPP

#include "Account.hpp"

void Account::displayaccount()//Display account along with the books it has checkedout
{
	int numberofbooksinaccountdue=0;
	cout<<"Name: "<<getname()<<endl;//Display name
	cout<<"AccountID#: "<<getuserid()<<endl;//Display user id
	if(userbook.size()==0)//If they have no bookss checked out
	{
		cout<<"No books checked out."<<endl;//Display no books checked out
	}
	else//If they do have books checked out
	{
		cout<<userbook.size()<<" books checked out";//Get the amount of books checked out
		for(unsigned int i=0; i<userbook.size(); i++)
		{
			if(userbook[i]->isbookoverdue()==true)
			{
				numberofbooksinaccountdue+=1;
			}	
		}
		if(numberofbooksinaccountdue==0)
		{
			cout<<":"<<endl;
		}
		else
		{
			cout<<numberofbooksinaccountdue<<" overdue):"<<endl;
		}
		for(unsigned int i=0; i<userbook.size(); i++)//Go through the vector 
		{
			cout<<'\t'<<i+1<<"."<<endl;//And display the information of all the books in the account
			userbook[i]->displaybookinaccount();//Display the books information
		}
	}
	cout<<""<<endl;
}

void Account::displaybookinaccountforsorting()//Display a sort description of each book in account
{
	if(userbook.size()==0)//If they have no books checked out
	{
		cout<<"No books checked out."<<endl;//Display no books checked out
	}
	else//If they do have books checked out
	{
		cout<<userbook.size()<<" books checked out:"<<endl;//Get the amount of books checked out
		for(unsigned int i=0; i<userbook.size(); i++)//Go through the vector 
		{
			//And display the information of all the books in the account
			cout<<'\t'<<i+1<<". \""<<userbook[i]->gettitle()<<" by "<<userbook[i]->getauthor()<<" (BookID# "<<userbook[i]->getid()<<") ["<<userbook[i]->getgenre()<<"]"<<endl;//Display the books information
		}
	}
}

void Account::addbooktoaccountfromfile(Book* checkoutbook, int duedate, int renew)//Adds book to account from input file
{

	checkoutbook->setavailability(false);//Since a user checked it out, book is now not available
	checkoutbook->setduedate(duedate);//Get the due date from file
	checkoutbook->setrenewamount(renew);//Check the amount of times the book has been renewed
	checkoutbook->updateuser(this);//Update the books user to this account	
	checkoutbook->updatepopscore();//Update popscore
	checkoutbook->updatebookuserhistory(this);//Update the books checkout history with this accounT
	userbook.push_back(checkoutbook);//Push the into the user account
}

void Account::addbookfromcheckout(Book* book)//Adds book to account from "CHECKOUT" command
{
	if(userbook.size()==10)//If account already has 10 books
	{
		cout<<"Account already has 10 books checked out."<<'\n'<<endl;//Can't check out more books
	}
	else//If user can still borrow books
	{
		if(book->isbookavailable()==true)//Checks to see if book is available
		{
			book->setavailability(false);
			book->setcheckoutduedate();//Set the books due date
			book->updateuser(this);//Update the books user to this account
			if(book->didaccountcheckthisbookoutbefore(this)==false)//If the book has never been checked out by this user
			{
				book->updatepopscore();//Update popscore
				book->updatebookuserhistory(this);//Update the books checkout history with this account
			}
			else{}
			userbook.push_back(book);//Add book to account
			cout<<"Book succesfully checked out."<<endl;//Says book is succesfully checked out
			book->displaybook();//Display the books info
		}
		else//If book is not available
		{
			cout<<"Book is already checked out."<<'\n'<<endl;//Book is checked out
		}
	}
}

void Account::deletebookfromaccount(int bookid)//Remove a book from user account if the book is being removed from library
{
	for(auto it=userbook.begin(); it!=userbook.end(); ++it)//Iteratre through the vector
	{
		if((*it)->getid()==bookid)//Get the book we are looking for
		{
			cout<<"Force returning book from AccountID# "<<getuserid()<<endl;
			cout<<"\""<<(*it)->gettitle()<<"\" by ";//Tells the user the book is removed
			cout<<(*it)->getauthor()<<" successfully removed."<<'\n'<<endl;//Tells user the book is removed
			userbook.erase(it);//Delete book
			break;
		}
	}
}

void Account::returnabook(int bookid)//Return a single book from user account
{
	for(auto it=userbook.begin(); it!=userbook.end(); ++it)//Iteratre through the vector
	{
		if((*it)->getid()==bookid)//Get the book we are looking for
		{
			cout<<"Book successfully returned by AccountID# "<<getuserid();
			if((*it)->isbookoverdue()==true)//If book is overdue
			{
				cout<<" (overdue by "<<abs(Time::gettime()-(*it)->getduedate())<<" days)."<<endl;//Say the amount of days it's overdue by
			}
			else//If it is not overdue
			{
				cout<<" (on time)."<<endl;//Say on time
			}
			cout<<""<<endl;
			(*it)->setavailability(true);//Make the book availavle again
			(*it)->resetrenew();//Make the book availavle again
			(*it)->deleteuser();//Reset the book's user
			userbook.erase(it);//Remove the book from the user
			break;
		}
	}
}

void Account::renewbooksinaccount()//Renew the books in the account
{
	int amountofbooksrenewed=0;//Declarartion
	if(isitanoverdueaccount()==true)//If account is overdue
	{
		cout<<"Account has books overdue."<<'\n'<<endl;//Account has overdue books
	}
	else if(userbook.size()==0)
	{
		cout<<"No books on this account."<<'\n'<<endl;
	}
	else//If all books are not overdue
	{	
		for(unsigned int i=0; i<userbook.size(); i++)//Goes through the vector of books
		{
			if(userbook[i]->getrenewamount()==2)//If a book has been renewed twice
			{
				cout<<'\t'<<i+1<<"."<<endl;
				userbook[i]->displaybookinaccount();//Display the book
				cout<<'\t'<<"Book already renewed twice."<<endl;//Says its renewed twice
			}
			else//If you can renew
			{
				cout<<'\t'<<i+1<<endl;
				userbook[i]->renewabook();//Renew the book
				amountofbooksrenewed++;//Amount of books renewed is increased by 1
			}
		}
		cout<<amountofbooksrenewed<<" of "<<userbook.size()<<" succesfully renewed."<<'\n'<<endl;//Display the amount of books renewed.
	}
}

bool Account::isitanoverdueaccount()//Determine if the account is overdue
{
	for(unsigned int i=0; i<userbook.size(); i++)//Goes through the vector of books
	{
		if(userbook[i]->isbookoverdue()==true)//If book is overdue
		{
			isoverdueaccount=true;//The account is overdue
			
		}
	}
	return isoverdueaccount;
}

void Account::returnallbooks()//Return all books
{
	for(auto it=userbook.begin(); it!=userbook.end(); it+=0)//Iteratre through the vector
	{
		cout<<"\""<<(*it)->gettitle()<<"\" by "<<(*it)->getauthor()<<" (BookID# "<<(*it)->getid()<<") force returned."<<endl;
		(*it)->setavailability(true);//Make the book availavle again
		(*it)->deleteanaccountfrombookcheckouthistory(this);//Update the books checkout history with this account
		(*it)->resetrenew();//Make the book availavle again
		(*it)->deleteuser();//Reset the book's user
		userbook.erase(it);//Remove the book from the user
	}
}

#endif