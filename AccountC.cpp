#ifndef ACCOUNTC_CPP
#define ACCOUNTC_CPP

#include "AccountC.hpp"
#include "BookC.hpp"

AccountC::~AccountC()
{
	for(auto it=accountcollection.begin(); it!=accountcollection.end(); ++it)
	{
		delete it->second;//Delete all the accounts
		accountcollection.erase(it);
	}
}

void AccountC::readaccountfile(string accountfile, BookC &bookc) //Populates the account collection with accounts
{

	ifstream accountfileopener;
	accountfileopener.open(accountfile);
	if(accountfile=="")//If no account was provided
	{
		cout<<"No accounts provided."<<endl;
	}
	else if(accountfileopener.fail())//If provided file doesn't exist
	{
		cout<<"Could not find file \""<<accountfile<<"\". Skipping"<<endl;
	}
	else//If it was successful
	{
		cout<<"Loading accounts from \""<<accountfile<<"\""<<endl;
		if(!accountfileopener.eof())
		{
			string firstline;
			getline(accountfileopener, firstline);//Get the first line which is the number of accounts
		}
		while(!accountfileopener.eof())
		{
			string nextline;
			string stringseg2;
			vector<string> accountinfo;
			getline(accountfileopener, nextline);
			stringstream test2(nextline);
			while(getline(test2, stringseg2, '|'))
			{
				accountinfo.push_back(stringseg2);
			}
			Account* a=new Account(stoi(accountinfo[0]), accountinfo[1]);
			for(int i=0; i<stoi(accountinfo[2]); i++)//Sees the amount of books user has checked out
			{
				string anotherstring;//String to get the books in the accountfile
				string stringseg3;
				vector<string> booksinaccountfile;//Store the information about the book user has checked out
				getline(accountfileopener, anotherstring);
				stringstream test3(anotherstring);
				while(getline(test3, stringseg3, '|'))
				{
					booksinaccountfile.push_back(stringseg3);
				}
				if(bookc.doesbookexistfromaccountfile(stoi(booksinaccountfile[0]))==true)
				{
					a->addbooktoaccountfromfile(bookc.book(stoi(booksinaccountfile[0])), stoi(booksinaccountfile[1]), stoi(booksinaccountfile[2]));
				}
			}
			addaccount(a);
			accountinfo.clear();
		}
	}
	accountfileopener.close();
}

void AccountC::addaccount(Account* account)//Function that adds the account into the library
{
	accountcollection[account->getuserid()]=account;//Create a map with ID being the key, and its corresponding account as the value;
	setofaccountid.insert(account->getuserid());//Put the ID in the set so we know which ID is taken, to make sure we won't use the same ID for account
}

void AccountC::browseaccount(string criteria)//Function that displays all accounts by criteria
{
	vector<Account*> accounts;//Make a temp vector
	for(auto it=accountcollection.begin(); it!=accountcollection.end(); ++it)
	{
		accounts.push_back(it->second);//Store books into vector
	}
	if(criteria=="name")//If sort by name
	{
		//Sort vector in ascending alphabetical
		sort(accounts.begin(), accounts.end(), [](Account* const& a1, Account* const& a2){return a1->getname()< a2->getname();});
	}
	else if(criteria=="accountid")//If sort by id
	{
		//Sort vector in ascending numerical
		sort(accounts.begin(), accounts.end(), [](Account* const& a1, Account* const& a2){return a1->getuserid()< a2->getuserid();});
	}
	else//If sort by number of books checked out
	{
		//Sort vector in descending
		sort(accounts.begin(), accounts.end(), [](Account* const& a1, Account* const& a2){return a1->amountofbookscheckedout()> a2->amountofbookscheckedout();});
	}

	for(unsigned int i=0; i<accounts.size(); i++)//Display the accounts in the sorted vector
	{
		cout<<i+1<<". "<<accounts[i]->getname()<<" (AccountID# "<<accounts[i]->getuserid()<<"). ";
		accounts[i]->displaybookinaccountforsorting();//Display the books in account
	}
	cout<<""<<endl;
}

void AccountC::getaccount(int accountid)//Function for the "ACCOUNT" command to retrieve information of a single account
{
	if(accountid!=0)
	{
		if(doesaccountexist(accountid)==true)//Account exist
		{
			auto it=accountcollection.find(accountid);//Get the Account
			it->second->displayaccount();//Display the account associated with valid ID
		}	
	}
}

void AccountC::checkoutbook(int bookid, int accountid, BookC &bookc)//Function for the "CHECKOUT" command to check out a book into an account
{
	if(accountid!=0 && bookid!=0)//Checks to see if user input is a number;
	{
		if(doesaccountexist(accountid)==true && bookc.doesbookexist(bookid)==true)//If account id exist
		{
			auto it=bookc.book(bookid);//Get the book in the map
			auto it2=accountcollection.find(accountid);//Get the account in the map
			if(it2->second->isitanoverdueaccount()==false)
			{
				it2->second->addbookfromcheckout(it);//Add the book into the account
			}
			else
			{
				cout<<"Account has books overdue."<<'\n'<<endl;
			}
		}
	}	
}

void AccountC::renewbook(int accountid)//Function for the "RENEW" command to renew all books in an account
{
	if(accountid!=0)//Checks to see if user input is a number
	{
		if(doesaccountexist(accountid)==true)//Checks to see if account with ID exist
		{
			auto it=accountcollection.find(accountid);//Get the account
			it->second->renewbooksinaccount();//Renew the book
		}
	}
}

void AccountC::returnbook(int bookid, BookC &bookc)//Function for the "RETURN" command to return a specific book
{
	if(bookid!=0)//Checks to see if user input is a number
	{
		if(bookc.doesbookexist(bookid)==true)
		{
			auto it=bookc.book(bookid);//Get the book
			if(it->isbookavailable()==true)//If book is not checked out
			{
				cout<<"Book is not currently checked out."<<'\n'<<endl;//Can't return the book
			}
			else//If book is checked out
			{
				it->getbookuser()->returnabook(bookid);//Force return the book
			}	
		}
	}
}

void AccountC::addA()//Function for the "ADDA" command to add an account
{
	int accountid=1;//Declaration
	string name;//Declaration

	cout<<"Enter the new user's name."<<endl;//Ask for name
	cout<<"> ";//Waits for user input
	getline(cin, name);//Get name
	while(setofaccountid.count(accountid)==1)//If the ID already exist
	{
		accountid++;//Increment the ID
	}
	Account* a=new Account(accountid, name);//Make an account with the name and unique ID
	addaccount(a);//Adds the account to the library
	cout<<"AccountID# "<<accountid<<" successfully created."<<'\n'<<endl;//Tells user account has been created.
}

void AccountC::removeA(int accountid)//Function for the "REMOVEA" command to delete an account
{
	if(accountid!=0)
	{
		if(doesaccountexist(accountid)==true)//Checks to see if account with ID exist
		{
			auto it=accountcollection.find(accountid);//Get the map with the corresponding key
			if(it->second->amountofbookscheckedout()!=0) //If user has books checked out
			{
				it->second->returnallbooks();//Return all books 
			}
			setofaccountid.erase(accountid);//Remove the accountid from the set so ID can be reused
			accountcollection.erase(accountid);//Erase account with the corresponding accountid
			cout<<it->second->getname()<<"'s account successfully removed."<<'\n'<<endl;//Tells user the account is removed
		}
	}
}

void AccountC::exportaccount(string accountfile) //EXPORT
{
	ofstream accountoutputfile;//Create a output file
	accountoutputfile.open(accountfile);//Create a output file with the name the user gave
	accountoutputfile<<accountcollection.size()<<endl;//First line of the file is the amount of books
	for(auto it=accountcollection.begin(); it!=accountcollection.end(); it++)//Start at the beggining of the map and go until the end.
	{
		//Output the books into the file in this order 
		accountoutputfile<<it->second->getuserid()<<"|"<<it->second->getname()<<"|"<<it->second->amountofbookscheckedout()<<endl;
		for(int i=0; i<it->second->amountofbookscheckedout(); i++)
		{
			accountoutputfile<<it->second->getbook(i)->getid()<<"|"<<it->second->getbook(i)->getduedate()<<"|"<<it->second->getbook(i)->getrenewamount()<<endl;
		}
	}
	accountoutputfile.close();
}

bool AccountC::doesaccountexist(int accountid)//See if an account with given id exist
{
	if(setofaccountid.count(accountid)==0)//If ID does not exist
	{
		cout<<"AccountID# "<<accountid<<" not found."<<'\n'<<endl;
		return false;//Return false
	}
	else
	{
		return true;//Return true;
	}
}

int AccountC::amountofoverdueaccounts()//Checks number of overdue accounts
{
	int numberofoverdueaccounts=0;
	for(auto it=accountcollection.begin(); it!=accountcollection.end(); ++it)//Goes through all account
	{
		if(it->second->isitanoverdueaccount()==true)//If it does
		{
			numberofoverdueaccounts+=1;//Incease the number of overdue accounts by 1
		}
	}
	return numberofoverdueaccounts;//Return the number
}


#endif
