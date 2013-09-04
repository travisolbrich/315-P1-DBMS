#ifndef DBMSENGINE_TUPLE_H
#define DBMSENGINE_TUPLE_H

using namespace std;

#include <iostream>
#include <string>
#include <vector>

class Tuple
{
	public:
		Tuple(vector<string> values) : values(values) {};
		Tuple() {};

		void setValues(vector<string> inValues) { values = inValues; }
		vector<string> getValues() { return values; }

	private:
		vector<string> values;

};

#endif