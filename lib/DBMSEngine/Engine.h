//Engine Header

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

	open_ {}

	close_ {}

	write_ {}

	exit_ {}

	show_ {}

	update_ {}

	insert_ {}

	delete_ {}
}