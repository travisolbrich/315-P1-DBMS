#ifndef DBMSEngine_Engine_H_
#define DBMSEngine_Engine_H_

#include "Relation.h"
#include <string>
#include <vector>

using namespace std;

class Engine 
{

public:
	Engine(Relation relation) { relations.push_back(relation); };
	Engine(vector<Relation> relations) : relations(relations) {};
	Engine() {};

	void open();
	void close();
	void write();

	// Commands
	void create(string relationName, vector<Attribute> attributes);
	void insert(string relationName, Tuple tuple);
	void show(string relationName);
	void show(Relation* relation);
	void update(string relationName, vector<pair<int, string>> values, vector<int> tuples);
	void deleteTuples(string relationName, vector<int> tupleIDs);

	// Queries
	Relation exprSelect(Relation* a, vector<int> tupleIDs);
	Relation exprUnion(Relation* a, Relation* b);
	Relation exprDifference(Relation* a, Relation* b);
	Relation exprProduct(Relation* a, Relation* b);
	Relation exprProject(Relation* a, vector<string> attributeName);
	Relation exprRenaming(Relation* a, vector<string> newAttributes); 
	
	// Helpers
	Relation *getRelation(string relationName);

	void exit();

private:
	vector<Relation> relations;

	// Helpers
	Relation *getAttributeName(string attributeName);
	bool isUnionCompatible(Relation* a, Relation* b);
	bool exists(Relation* haystack, Tuple* needle);
	void checkType(Attribute* attribute, string value);
	void addRelation(Relation relation) { relations.push_back(relation); }
};

#endif
