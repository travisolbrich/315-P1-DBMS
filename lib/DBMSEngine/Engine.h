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
	Engine() {};

	void create();
	void open();
	void close();
	void write();
	void show(string relationName);
	void update();
	void insert();
	void deleteTuple();
	void exit();

private:
	vector<Relation> relations;
	Relation *getRelation(string relationName);
};

#endif
