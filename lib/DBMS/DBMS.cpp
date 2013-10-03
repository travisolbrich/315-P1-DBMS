#include "../SqlTokenizer/SqlTokenizer.h"
#include "../SqlTokenizer/Token.h"
#include "../SqlParser/SqlParser.h"
#include "../DBMSEngine/Relation.h"
#include "../DBMSEngine/Engine.h"
#include "DBMS.h"

#include <string>
#include <vector>

/**
	Returns:
	0: valid answer
	1: Exception
	2: Exit called
**/
int DBMS::execute(string query)
{
	try 
	{
		SqlTokenizer* tokenizer = new SqlTokenizer(query);
		vector<Token> tokens = tokenizer->split();

		if(tokens[0].getType() == Token::EXIT) return 2;
	
		SqlParser* parser = new SqlParser(tokens, engine);
		parser->parse();
	}
	catch (exception& e)
	{
		cout << "!!! " <<  e.what() << "\n";
		return 1;
	}

	return 0;
}

Relation DBMS::relation(string relation)
{
	return *engine->getRelation(relation);
}