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
		Relation(string name, vector<Attribute> attributes) : name(name), attributes(attributes) {};
		Relation() {};

		string getName() { return name; }
		vector<Attribute> getAttributes() { return attributes; }
		vector<Tuple> getTuples() { return tuples; }
		Tuple* getTuple(int id) { return &tuples[id]; }

		void setAttributes(vector<Attribute> inAttributes) { attributes = inAttributes; };
		void setTuples(vector<Tuple> inTuples) { tuples = inTuples; };
		void addTuple(Tuple tuple) { tuples.push_back(tuple); }
		void setName(string inName) { name = inName; }

	private: 
		string name;
		vector<Attribute> attributes;
		vector<Tuple> tuples;

};

#endif