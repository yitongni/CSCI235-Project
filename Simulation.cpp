#ifndef SIMULATION_CPP
#define SIMULATION_CPP

#include "Simulation.hpp"

void Simulation::simulatelibrary(string bookfile, string accountfile)//Runs the program;
{
	BookC bc;
	AccountC ac;
	bc.readbookfile(bookfile);
	ac.readaccountfile(accountfile, bc);

	string command="";
	while(command!="EXIT")
	{
		command=commandinput();
		if(command=="BROWSE")//If command is "BROWSE"
		{
			string criteria;
			cout<<"Enter the criteria to sort by. (title/author/genre/bookid/popularity)"<<endl;
			cout<<"> ";
			cin>>criteria;
			if(criteria=="title" || criteria=="author" || criteria=="genre" || criteria=="bookid" ||criteria=="popularity")
			{
				bc.browsebook(criteria);
			}
			else//It's invalid
			{
				cout<<"Invalid value."<<'\n'<<endl;
			}
		}

		else if(command=="BOOK")//If command is "BOOK"
		{
			cout<<"Enter a book id."<<endl;
			bc.getbook(getnumberinput());
		}

		else if(command=="SEARCH")//If command is "SEARCH"
		{
			string criteria;
			cout<<"Enter the criteria to search. (title/author)"<<endl;
			cout<<"> ";
			cin>>criteria;
			if(criteria=="title" || criteria=="author")//If the criteria is title or author
			{
				string phrase;
				cout<<"Enter the search phrase."<<endl;//Get the phrase
				cout<<"> ";
				cin>>phrase;
				bc.searchphrase(criteria, phrase);//Calls the function
			}
			else
			{
				cout<<"Invalid value."<<'\n'<<endl;
			}
		}

		else if(command=="ACCOUNTS")
		{
			string criteria;
			cout<<"Enter the criteria to sort by. (name/accountid/checkouts)"<<endl;
			cout<<"> ";
			cin>>criteria;
			if(criteria=="name" || criteria=="accountid" || criteria=="checkouts")//If user input matches on of the criteria
			{
				ac.browseaccount(criteria);
			}
			else//It doesn't match
			{
				cout<<"Invalid value."<<'\n'<<endl;
			}
		}

		else if(command=="ACCOUNT")
		{
			cout<<"Enter an account id."<<endl;
			ac.getaccount(getnumberinput());
		}

		else if(command=="CHECKOUT")
		{
			int bookid;
			int accountid;
			
			cout<<"Enter an account id."<<endl;
			accountid=getnumberinput();
			if(accountid!=0)
			{
				cout<<"Enter a bookid."<<endl;
				bookid=getnumberinput();
				if(bookid!=0)
				{		
					ac.checkoutbook(bookid, accountid, bc);
				}
			}
		}

		else if(command=="RENEW")
		{
			cout<<"Enter an account id."<<endl;
			ac.renewbook(getnumberinput());
		}

		else if(command=="RETURN")
		{
			cout<<"Enter a book id."<<endl;
			ac.returnbook(getnumberinput(), bc);
		}

		else if(command=="ADDB") //If command is "ADDB"
		{
			bc.addB();
		}

		else if(command=="REMOVEB") //If command is "REMOVEB"
		{
			cout<<"Enter a book id."<<endl;
			bc.removeB(getnumberinput());
		}

		else if(command=="ADDA") //If command is "ADDA"
		{
			ac.addA();
		}

		else if(command=="REMOVEA")
		{
			cout<<"Enter an account id."<<endl;
			ac.removeA(getnumberinput());
		}

		else if(command=="SYSTEM") //If command is "SYSTEM"
		{
			displaysystem(Time::gettime(), bc.amountofbooks(), bc.amountofbooksoverdue(), ac.amountofaccounts(), ac.amountofoverdueaccounts());
		}

		else if(command=="TIME") //If command is "TIME"
		{
			Time::changetime();
		}

		else if(command=="EXPORT")
		{
			string bookfilename="";
			string accountfilename="";
	
			cout<<"Enter the name for the books file. (This may overwrite a file)"<<endl;//Ask user to enter a book file to export
			cout<<"> ";
			cin>>bookfilename;

			cout<<"Enter the name for the accounts file. (This may overwrite a file)"<<endl;//Ask user to enter an account file to export
			cout<<"> ";
			cin>>accountfilename;

			bc.exportbook(bookfilename);
			ac.exportaccount(accountfilename);

			cout<<"Books data successfully exported to "<<"\""<<bookfilename<<"\"."<<endl;
			cout<<"Accounts data successfully exported to "<<"\""<<accountfilename<<"\"."<<endl;
		}

		else if(command=="HELP")
		{
			displaycommands();
		}

		else if(command=="EXIT")
		{
				cout<<"Thank you for using StackOverdue!"<<'\n'<<endl;
		}

		else
		{
			cout<<"Invalid command."<<'\n'<<endl;
		}
	}
}

void Simulation::displaysystem(int time, int numberofbooks, int numberofoverduebooks, int numberofaccounts, int numberofoverdueaccounts) //SYSTEM
{
	cout<<"System time: "<<time<<"."<<endl;//Display current time
	cout<<"Number of books: "<<numberofbooks<<"."<<endl;//Display number of books in library
	cout<<"Number of overdue books: "<<numberofoverduebooks<<"."<<endl;//Displays number of overdue books in library
	cout<<"Number of accounts: "<<numberofaccounts<<"."<<endl;//Displays number of accounts in library
	cout<<"Number of overdue accounts: "<<numberofoverdueaccounts<<"."<<'\n'<<endl;//Displays number of accounts with overdue books in library
}

void Simulation::displaycommands() //HELP
{
	cout<<"BROWSE: Provides the status of all the books."<<endl;
	cout<<"BOOK: Provides the status of a specific book."<<endl;
	cout<<"SEARCH: Searches for all books with a key-phrase in the title or author."<<endl;
	cout<<"ACCOUNTS: Provides account snapshots for all user accounts."<<endl;
	cout<<"ACCOUNT: Provides an account snapshot for a specific user account."<<endl;
	cout<<"CHECKOUT: Checks a book out to a user account."<<endl;
	cout<<"RENEW: Renews a checked out book. (Up to two times allowed)"<<endl;
	cout<<"RETURN: Returns a checked out book."<<endl;
	cout<<"RECOMMEND: Generates a list of recommended books for a given user."<<endl;
	cout<<"ADDB: Adds a new book to the library."<<endl;
	cout<<"REMOVEB: Removes a specific book from the library."<<endl;
	cout<<"ADDA: Creates a new user account in the library."<<endl;
	cout<<"REMOVEA: Removes a specific user account from the library."<<endl;
	cout<<"SYSTEM: Provides diagnostic information about the system."<<endl;
	cout<<"TIME: Fast forwards the system time by a specified number of days."<<endl;
	cout<<"EXPORT: Exports the library’s books and accounts to files."<<endl;
	cout<<"HELP: Displays this help menu."<<endl;
	cout<<"EXIT: Exits the program."<<endl;
	cout<<""<<endl;
}

string Simulation::commandinput() //Get command inout
{
	string command;
	cout<<"> ";
	cin>>command;
	cin.ignore();
	return command;
}

int Simulation::getnumberinput()//Gets a number input
{
	int num;
	cout<<"> ";
	cin>>num;
	if(!cin || num==0)//Makes sure user input is a number
	{
		cout<<"Invalid input."<<'\n'<<endl;//If not a number	
		cin.clear();//Clear the input
		cin.ignore(256, '\n');//Ignores the rest
		return 0;
	}
	else
	{
		cin.clear();//Clear the input
		cin.ignore(256, '\n');//Ignores the rest
		return num;
	}
}

#endif



