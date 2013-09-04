#ifndef DBMSENGINE_RELATION_H
#define DBMSENGINE_RELATION_H

using namespace std;

#include "Tuple.h"
#include "Attribute.h"

#include <iostream>
#include <string>
#include <vector>

class Relation
{
	public:
		Relation(string name, vector<Attribute> attributes, vector<Tuple> tuples) : name(name), attributes(attributes), tuples(tuples) {};
		Relation() {};

		string getName() { return name; }
		vector<Attribute> getAttributes() { return attributes; }
		vector<Tuple> getTuples() { return tuples; }

		void setAttributes(vector<Attribute> inAttributes) { attributes = inAttributes; };
		void setTuples(vector<Tuple> inTuples) { tuples = inTuples; };
		void setName(string inName) { name = inName; }

	private: 
		string name;
		vector<Attribute> attributes;
		vector<Tuple> tuples;

};

#endif