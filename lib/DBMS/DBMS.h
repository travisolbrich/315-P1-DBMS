#ifndef DBMS_dbms_H_
#define DBMS_dbms_H_

#include "../SqlTokenizer/SqlTokenizer.h"
#include "../SqlTokenizer/Token.h"
#include "../SqlParser/SqlParser.h"
#include "../DBMSEngine/Relation.h"
#include "../DBMSEngine/Engine.h"

#include <string>
#include <vector>

using namespace std;

class DBMS 
{
private:
	// Helpers
	Engine* engine;

public:
	DBMS() {
		engine = new Engine();
	};

	int execute(string query);
	Relation relation(string relationName);

};

#endif
