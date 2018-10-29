## Assignment 3 - StackOverdue

For this project we have to simulate a library. The simulation also has a time that is shared among the whole project. The time determines whether or not a book is overdue.

In this project we have Book and Account class. Each BOOK has data members such as an ID, title, author, genre, due dates, etc, and they have member functions that can retrieve these information. A book also has an ACCOUNT pointer that keeps track of its current user. The Book class also has functions that will help with the commands.

Each ACCOUNT has data members such as ID, name. An account also has a vector of BOOK pointer to show the books that a single account has checked out. The account has member function that can retrieve a book in the account, as well as ID and name of account. It also has member function to help the command.

There is an AccountC class that stores a collection of accounts. The AccountC class read a file and populate itself with accounts in that file. From the command input the class can add an account, remove an account, it can checkout books, renew books and return books, display information of a single account or information of all the accounts as well as export all the information into a file.

The BookC class stores a collection of all books in the library. Just like the AccountC class the BookC class will also read a file and populate itself with books in the file. Also like the AccountC class, the BookC class also has function that deal with command inputs. It can display information of all the books, display information of a single book, search for books, add and remove books as well as export all information of all books into a file.

The SIMULATION class takes in user input, as commands and depending on the command it will call the respective functions that deals with the command.

To run the code please type into the terminal
Make all
Once done, the solution executable StackOverdue will appear.
Type ./StackOverdue books.data accounts.data

****NOTE******
The Data directory has 4 directories. Each directories has their own books.data and accounts.data file.