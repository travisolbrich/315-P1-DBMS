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
	void update();
	void insert(string relationName, Tuple tuple);
	void deleteTuple();
	void exit();

private:
	vector<Relation> relations;
	Relation *getRelation(string relationName);
};

#endif
