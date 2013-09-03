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
		tableBuild(i, j);	
	}

	void tableBuild(string i, string j[]) 
	{
		tableName = i;
		attributes[] = {j};
	}

	openTable (string i) 
	{
		dataFile.open(i);
	}

	closeTable (string i) 
	{
		dataFile.close(i);
	}

	writeTable (string i) 
	{
		ofstream dataFile(i);
	}

	showView (string i) 
	{
		ifstream dataFile(i);
	}

	updateTable() 
	{

	}

	insertToTable() 
	{

	}

	deleteFromTable() 
	{

	}
	
	exitTable ()
	{


	}
};

#endif