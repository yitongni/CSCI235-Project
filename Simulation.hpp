#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <fstream>

#include "Time.hpp"
#include "BookC.hpp"
#include "AccountC.hpp"
#include "Book.hpp"
#include "Account.hpp"

class Simulation
{

public:
	Simulation(){}
	~Simulation(){}

	//Deals with user input and commands
	void simulatelibrary(string file, string file2);//Reads the files.
	string commandinput();
	int getnumberinput();

	//Command function
	void displaysystem(int time, int numberofbooks, int numberofoverduebooks, int numberofaccounts, int numberofoverdueaccounts);// SYSTEM
	void displaycommands(); //HELP
	
};

#endif