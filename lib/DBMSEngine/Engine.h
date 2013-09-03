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
	int _id[];
	string table_name;
	string _attributes[];
	vector<array> tuple;		//Most likely highly erronious definition

public:
	Create_Table (string i, string j[] ) {
		table_build(i, j);	
	}

	void table_build(string i, string j[]) {
		table_name = i;
		_attributes[] = {j};
	}

	open_ (string i) {
		datafile.open(i);
	}

	close_ (string i) {
		datafile.close(i);
	}

	write_ (string i) {
		ofstream datafile(i);
	}

	show_ (string i) {
		ifstream datafile(i);
	}

	update_ {}

	insert_ {}

	delete_ {}

	exit_ {
		
	}
};

#endif