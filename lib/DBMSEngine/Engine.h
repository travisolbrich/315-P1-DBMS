#ifndef DBMSEngine_Engine_H_
#define DBMSEngine_Engine_H_

#include "Relation.h"
#include <string>
#include <vector>

using namespace std;

class Engine 
{

public:
	Engine() {};

	void create();
	void open();
	void close();
	void write();
	void show();
	void update();
	void insert();
	void deleteTuple();
	void exit();

private:
	vector<Relation> relations;
};

#endif
