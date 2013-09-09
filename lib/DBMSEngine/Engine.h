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

	void show(string relationName);
	void create(string relationName, vector<Attribute> attributes);
	void update(string relationName, vector<pair<int, string>> values, vector<int> tuples);
	void insert(string relationName, Tuple tuple);
	void deleteTuples(string relationName, vector<int> tupleIDs);
	void checkType(Attribute* attribute, string value);
	void addRelation(Relation relation) { relations.push_back(relation); }

	Relation *getRelation(string relationName);
	Relation exprUnion(Relation* a, Relation* b);
	Relation exprDifference(Relation* a, Relation* b);
	Relation exprProduct(Relation* a, Relation* b);
	Relation exprProjection(string relationName,string attributeName);
	Relation exprRenaming(Relation* a, vector<string> newAttributes); 
	Relation select(Relation* a, vector<int> tupleIDs);

	bool isUnionCompatible(Relation* a, Relation* b);
	bool exists(Relation* haystack, Tuple* needle);

	void exit();

private:
	vector<Relation> relations;
};

#endif
