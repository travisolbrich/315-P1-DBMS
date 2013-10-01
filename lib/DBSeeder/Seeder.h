#ifndef DBSEEDER_SEEDER_H
#define DBSEEDER_SEEDER_H

#include "../SqlTokenizer/SqlTokenizer.h"
#include "../SqlTokenizer/Token.h"
#include "../SqlParser/SqlParser.h"
#include "../DBMSEngine/Relation.h"
#include "../DBMS/DBMS.h"

#include <string>
#include <vector>

using namespace std;

class Seeder 
{
private:
	DBMS* dbms;

public:
	Seeder(DBMS* _dbms) { dbms = _dbms; };

	void seed();
};

#endif
