#ifndef BOOKC_CPP
#define BOOKC_CPP

#include "BookC.hpp"

BookC::~BookC()
{
	for(auto it=bookcollection.begin(); it!=bookcollection.end(); ++it)
	{
		delete it->second;//Delete all the books
		bookcollection.erase(it);
	}
}

void BookC::readbookfile(string bookfile) //Populates the book collection with books
{
	ifstream bookfileopener;
	bookfileopener.open(bookfile);//Trys to open file
	if(bookfile=="")//If no book file is provided
	{
		cout<<"No books provided."<<endl;
	}
	else if(bookfileopener.fail())//Failed to open file
	{
		cout<<"Could not find file \""<<bookfile<<"\". Skipping"<<endl;
	}
	else
	{
		cout<<"Loading books from \""<<bookfile<<"\""<<endl;
		if(!bookfileopener.eof())
		{
			string firstline;
			getline(bookfileopener, firstline);//Get the first line which is number of books
		}
		while(!bookfileopener.eof())
		{
			string nextline;
			string stringseg;
			vector<string> bookinfo;
			getline(bookfileopener, nextline); //Get next line
			stringstream test(nextline);
			while(getline(test, stringseg, '|')) //Split the string
			{
				bookinfo.push_back(stringseg); //Push each segment into a vector
			}
			Book* b=new Book(stoi(bookinfo[0]), bookinfo[1], bookinfo[2], bookinfo[3], stoi(bookinfo[4])); //Creates the new book with the data in the vector
			addbook(b); //Add the book into the library
			bookinfo.clear(); //Clear the vector to be reused for the next book;
		}
	}
	bookfileopener.close(); //Close the file
}

void BookC::addbook(Book* book)//Function that adds the book into the library
{
	bookcollection[book->getid()]=book; //Create a map with ID being the key, and its corresponding book as the value;
	setofid.insert(book->getid()); //Put the ID in the set so we know which ID is taken
	titleauthorpair.insert(pair<string, string>(book->gettitle(), book->getauthor())); //Create a pair for title author so same book with title and author can be created
}

void BookC::getbook(int bookid)//Function for the "BOOK" command to retrieve information of a single book
{
	if(bookid!=0)
	{
		if(doesbookexist(bookid)==true)//If the book exist
		{
			auto it=bookcollection.find(bookid);//Get the book
			it->second->displaybook();//Display the book associated with valid ID
		}
	}
}

void BookC::browsebook(string criteria)//Function for the "BROWSE" command to sort all the books by a given criteria
{
	vector<Book*> books;//Make a temp vector
	for(auto it=bookcollection.begin(); it!=bookcollection.end(); ++it)
	{
		books.push_back(it->second);//Store books into vector
	}
	if(criteria=="title")//It it's sorting by title
	{
		sort(books.begin(), books.end(), sortbytitle); //Sort title in ascending alphabetical
	}
	else if(criteria=="author")//If sort by author
	{
		sort(books.begin(), books.end(), sortbyauthor); //Sort author in ascending alphabetical
	}
	else if(criteria=="genre")//If sort by genre
	{
		sort(books.begin(), books.end(), sortbygenre); //Sort genre in ascending alphabetical
	}
	else if(criteria=="bookid")//If sort by bookid
	{
		sort(books.begin(), books.end(), sortbyid); //Sort ID in ascending numerical
	}
	else//else must be sort by popularity score
	{
		sort(books.begin(), books.end(), sortbypopularity); //Sort popularity in descending numerical
	}

	for(unsigned int i=0; i<books.size(); i++)//Display the books in the sorted vector
	{
		cout<<i+1<<". \""<<books[i]->gettitle()<<"\" by "<<books[i]->getauthor()<<" (BookID# "<<books[i]->getid()<<") ["<<books[i]->getgenre()<<"]. ";
		if(books[i]->isbookavailable()==true)
		{
			cout<<" AVAILABLE."<<endl;
		}
		else
		{
			cout<<" CHECKED OUT"<<" (AccountID# "<<books[i]->getbookuser()->getuserid()<<")"<<endl;
		}
	}
	cout<<""<<endl;
}

void BookC::searchphrase(string criteria, string phrase)//Function for the "SEARCH" command to search a book if the criteria contains phrase
{
	vector<Book*> bookthatcontainsphrase;
	if(criteria=="title")//If criteria is title
	{
		for(auto it=bookcollection.begin(); it!=bookcollection.end(); ++it)//Get the books
		{
			if(it->second->gettitle().find(phrase) != string::npos)//See if the book title has the phrase
			{
				bookthatcontainsphrase.push_back(it->second);//If it does add it to the vector
			}
		}
	}

	else//If the criteria is author
	{
		for(auto it=bookcollection.begin(); it!=bookcollection.end(); ++it)//Gets the books
		{
			if(it->second->getauthor().find(phrase) != string::npos)//See if the book author has the phrase
			{
				bookthatcontainsphrase.push_back(it->second);//If it does add it to the vector
			}
		}
	}

	if(bookthatcontainsphrase.size()==0)//If the vector size is 0
	{
		cout<<"No search results found."<<endl;//Display
	}
	else//Search found
	{
		cout<<"Search Results:"<<endl;
		for(unsigned int i=0; i<bookthatcontainsphrase.size(); i++)//Go through the vector
		{
			//Display the book
			cout<<i+1<<". \""<<bookthatcontainsphrase[i]->gettitle()<<"\" by "<<bookthatcontainsphrase[i]->getauthor()<<" (BookID# ";
			cout<<bookthatcontainsphrase[i]->getid()<<") ["<<bookthatcontainsphrase[i]->getgenre()<<"]. ";
			if(bookthatcontainsphrase[i]->isbookavailable()==true)
			{
				cout<<" AVAILABLE."<<endl;
			}
			else
			{
				cout<<" CHECKED OUT"<<" (AccountID# "<<bookthatcontainsphrase[i]->getbookuser()->getuserid()<<")"<<endl;
			}
		}
	}
	cout<<""<<endl;
}

void BookC::addB()//Function for the "ADDB" command to add a book
{
	int bookid=1;//Declaration
	string booktitle;//Declaration
	string author;//Declaration
	string genre;//Declaration

	cout<<"Enter the new book's title."<<endl;//Gets the title of the new book
	cout<<"> ";
	getline(cin, booktitle);//Get the line

	cout<<"Enter the new book's author."<<endl;//Gets the author of the new book
	cout<<"> ";
	getline(cin, author);//Get the line

	if(titleauthorpair.count(pair<string, string>(booktitle, author))==1)//Checks to see if pair of title and author already exist.//setofauthor.count(author)==1 && setofbooktitle.count(booktitle)==1)
	{
		cout<<"Book with title and author already exists."<<'\n'<<endl;//If it does exist
	}

	else
	{
		cout<<"Enter the new book's genre."<<endl;//If pair does not exist, ask for genre
		cout<<"> ";
		getline(cin, genre);//Get the line
		while(setofid.count(bookid)==1)//Gets an unused book ID
		{
			bookid++;//Incriment bookid
		}
		Book* b=new Book(bookid, booktitle, author, genre, 0);//Creates the new book
		addbook(b);//Add the book to the library
		cout<<"BookID# "<<bookid<<" successfully created."<<'\n'<<endl;//Tells the user book has been created
	}
}

void BookC::removeB(int bookid)//Function for the "REMOVEB" command to remove a book.
{
	if(bookid!=0)
	{
		if(doesbookexist(bookid)==true)//If book exist
		{
			auto it=bookcollection.find(bookid);//Get book
			if(it->second->isbookavailable()==false)//If the book thats being removed is checked out
			{
				it->second->getbookuser()->deletebookfromaccount(bookid);//Force return the book
			}
			else//If book isn't checked out
			{
				cout<<"\""<<it->second->gettitle()<<"\" by "<<it->second->getauthor()<<" successfully removed."<<'\n'<<endl;//Tells user the book is removed
			}
			titleauthorpair.erase(pair<string, string>(it->second->gettitle(), it->second->getauthor()));//Delete the pair of title-author combination so a new book can have that combination
			setofid.erase(bookid);//Remove the bookid from the set so ID can be reused
			bookcollection.erase(bookid);//Erase book with the corresponding bookid from the library
		}
	}
}

void BookC::exportbook(string bookfile) //EXPORT
{
	ofstream bookoutputfile;//Create a output file
	bookoutputfile.open(bookfile);//Create a output file with the name the user gave
	bookoutputfile<<bookcollection.size()<<endl;//First line of the file is the amount of books
	for(auto it=bookcollection.begin(); it!=bookcollection.end(); it++)//Start at the beggining of the map and go until the end.
	{
		//Output the books into the file in this order 
		bookoutputfile<<it->second->getid()<<"|"<<it->second->gettitle()<<"|"<<it->second->getauthor()<<"|"<<it->second->getgenre()<<"|"<<it->second->getpopscore()<<endl;
	}
	bookoutputfile.close();
}

int BookC::amountofbooksoverdue() //Returns the amount of books that are over due
{
	int numberofoverduebooks=0;
	for(auto it=bookcollection.begin(); it!=bookcollection.end(); ++it)//Goes through all books
	{
		//it->second->setbookoverdue();//Determine if a book is overdue
		if(it->second->isbookoverdue()==true)//If it is overdue
		{
			numberofoverduebooks+=1;//Incease the number of overdue books by 1
		}
	}
	return numberofoverduebooks;//Return the number
}

bool BookC::doesbookexist(int bookid) //See if book a book with given id exist
{
	if(setofid.count(bookid)==0)//If ID does not exist
	{
		cout<<"BookID# "<<bookid<<" not found."<<'\n'<<endl;
		return false;//Return false
	}
	else
	{
		return true;//Return true;
	}
}

bool BookC::doesbookexistfromaccountfile(int bookid) //See if book a book with given id exist
{
	if(setofid.count(bookid)==0)//If ID does not exist
	{
		cout<<"Could not find library book with ID# "<<bookid<<"."<<endl;
		return false;//Return false
	}
	else
	{
		return true;//Return true;
	}
}

bool BookC::sortbytitle(Book* book1, Book* book2) //Sort by title
{
	return book1->gettitle()<book2->gettitle(); //Sort title alphabetically ascending
}

bool BookC::sortbyauthor(Book* book1, Book* book2) //Sort by author
{
	return book1->getauthor()<book2->getauthor(); //Sort author alphabetically ascending
}

bool BookC::sortbyid(Book* book1, Book* book2) //Sort by ID
{
	return book1->getid()<book2->getid(); //Sort ID ascending
}

bool BookC::sortbygenre(Book* book1, Book* book2) //Sort by genre
{
	return book1->getgenre()<book2->getgenre(); //Sort genre alphabetically ascending
}

bool BookC::sortbypopularity(Book* book1, Book* book2) //Sort by popularity
{
	return book1->getpopscore()>book2->getpopscore(); //Sort popularity score numerically descending
}


#endif