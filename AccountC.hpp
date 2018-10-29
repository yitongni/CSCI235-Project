#ifndef ACCOUNTC_HPP
#define ACCOUNTC_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

#include "Account.hpp"

class BookC;

class AccountC
{

public:

	AccountC(){}
	~AccountC();

	//Reading file
	void readaccountfile(string accountfile, BookC &bookc); //Populates the account collection with accounts

	//Add an account to the collection
	void addaccount(Account* account); //Function that adds the account into the library

	//Command functions
	void browseaccount(string criteria); //ACCOUNTS
	void getaccount(int accountid); //ACCOUNT
	void checkoutbook(int bookid, int accountid, BookC &bookc); //CHECKOUT
	void renewbook(int accountid); //RENEW
	void returnbook(int bookid, BookC &bookc); //RETURN
	void addA(); //ADDA
	void removeA(int accountid); //REMOVEA
	void exportaccount(string accountfile); //EXPORT

	//Helper functions
	int amountofaccounts(){ return accountcollection.size(); }
	bool doesaccountexist(int accountid); //See if an account with given id exist
	int amountofoverdueaccounts(); //Determine the amount of accounts with overdue books


private:

	map<int, Account*> accountcollection;//Contains a collection of accounts
	set<int> setofaccountid;//Contains a set of ID in use for accounts

};


#endif