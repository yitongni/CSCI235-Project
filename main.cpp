#include <iostream>
#include <string>

#include "Simulation.hpp"

using namespace std;

int main(int argc, char* argv[]) 
{
	string bookfilename="";
	string accountfilename="";
	
	if(argc == 2)//Provided solution executable and book file and no account file provided
	{
		bookfilename=argv[1];
	}
	
	else if(argc == 3)//Provided solution executable, book file and account file
	{
		bookfilename=argv[1];
		accountfilename=argv[2];
	}

	Simulation simulate;
	simulate.simulatelibrary(bookfilename, accountfilename);

	return 0;
}