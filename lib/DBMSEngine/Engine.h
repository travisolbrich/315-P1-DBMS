#ifndef DBMSEngine_Engine_H_
#define DBMSEngine_Engine_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

class Relations {

private:
	int id[];
	string tableName;
	string attributes[];
	vector<vector<string>> tuple;		//Most likely highly erronious definition

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

	open_ (string i) {
		dataFile.open(i);
	}

	close_ (string i) {
		dataFile.close(i);
	}

	write_ (string i) {
		ofstream dataFile(i);
	}

	show_ (string i) {
		ifstream dataFile(i);
	}

	update_ {}

	insert_ {}

	delete_ {}

	exit_ {}
};

#endif