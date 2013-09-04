#ifndef DBMSEngine_Engine_H_
#define DBMSEngine_Engine_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

class Relations 
{

private:
	int id[];
	string tableName;
	string attributes[];
	vector<vector<string>> tuples;		//Most likely highly erronious definition

public:
	createTable (string i, string j[] ) 
	{
		//Do Me Third
		tableBuild(i, j);
	}

	void tableBuild(string i, string j[]) 
	{
		//Do Me Second
		tableName = i;
		attributes[] = {j};
	}

	openTable (string i) 
	{
		//Do Me Fourth
		dataFile.open(i);
	}

	closeTable (string i) 
	{
		//Do Me Fifth
		dataFile.close(i);
	}

	writeTable (string i) 
	{
		//Do Me Sixth
		ofstream dataFile(i);
	}

	showView (string i) 
	{
		//Do Me Tenth
		ifstream dataFile(i);
		//are views any stored Query result?
		//do we need to be able to list the views that are availible to see?
	}

	updateTable() 
	{
		//Do Me Eighth
		//changes existing entry
		//need error checking to ensure entry exists
		//be able to take input stream and rectify valid inputs. should be able to handle all primitives? ie. int's shouldn't be in a firstName block (unecessary?)
	}

	insertToTable() 
	{
		//Do Me Seventh
		//inserts a NEW entry
		//need error checking to ensure entry does NOT yet exist

	}

	deleteFromTable() 
	{
		//Do Me Nineth
		//removes an existing entry
		//need error checking to ensure entry exists
	}

	exitTable (/* Pass 'exit_var' current state*/)
	{
		//Do Me First
		//set 'exit_var=true' to exit the while loop in try block in Engine.cpp
		//we will need the state of exit_var for error checking (I think)
	}
};

#endif