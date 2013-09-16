using namespace std;

#include "SqlParser.h"
#include "ConditionParser.h"
#include "../SqlTokenizer/Token.h"
#include "../DBMSEngine/Engine.h"

#include <iostream>
#include <sstream>
#include <algorithm>

void SqlParser::setToken()
{
	token = tokens[currentID];
	//cout << endl << "### [" << currentID << "] " << token.getTypeName() << ": " << token.getValue() << endl;
}

bool SqlParser::expect(Token::TokenTypes type)
{
	if(tokens[currentID + 1].getType() == type)
	{
		increment();
		return true;
	}

	return false;
}

void SqlParser::increment()
{
	if(currentID == tokens.size() - 1) throw runtime_error("Can't increase counter any more.");
	currentID++;
	setToken();
}

void SqlParser::parse()
{
	cout << "==============================" << endl;
	cout << "Parser" << endl;
	cout << "==============================" << endl;


	currentID = 0;
	setToken();

	program();
}

bool SqlParser::program()
{	
	if(token.getType() == Token::IDENTIFIER)
	{
		cout<<"Expect query"<<endl;
		bool status = query();
		if ( ! status) cout << "[FAILURE]\n";
	}
	else
	{
		cout<<"Expect command"<<endl;
		command();
	}

	return true;
}

bool SqlParser::query()
{
	string relationName = token.getValue();

	// Next thing should be a left arrow
	if( ! expect(Token::LEFTARROW)) return false;

	increment();
	Relation relation = expr();
	engine->show(&relation);
	return true;
}

bool SqlParser::command()
{
	switch (token.getType())
	{
		
	}
	return true;
}

Relation SqlParser::expr()
{
	Relation relation;

	if(token.getType() == Token::IDENTIFIER || token.getType() == Token::LEFTPAREN) 
	{
		return atomicExpr();
	}

	else if(token.getType() == Token::SELECT)
	{
		return exprSelect();
	}

	else if(token.getType() == Token::PROJECT)
	{
		return exprProject();
	}

	else if (token.getType() == Token::RENAME)
	{
		return exprRename();
	}

}

Relation SqlParser::exprSelect()
{
	// Expect an condition list (Just read it now, parse later)
	vector<Token> conditions = conditionList();
	
	// Expect a atomic expression	
	Relation relation = atomicExpr();

	ConditionParser* conditionParser = new ConditionParser(conditions, engine, relation);
	cout << "Number of resulting rows: " << conditionParser->parse().size() << endl;
	relation = engine->exprSelect(&relation, conditionParser->parse());

	return relation;
}


vector<Token> SqlParser::conditionList()
{
	vector<Token> tokens;

	int parenDepth = 1;

	if( ! expect(Token::LEFTPAREN)) throw runtime_error("expected LEFTPAREN");

	while(parenDepth > 0)
	{
		increment();
		if(token.getType() == Token::LEFTPAREN) parenDepth++;

		if(token.getType() == Token::RIGHTPAREN) parenDepth--;

		tokens.push_back(token);
	}

	tokens.pop_back();

	increment();

	for(int i=0; i < tokens.size(); i++)
	{
		cout << " " << tokens[i].getValue();
	}
	cout << endl;

	return tokens;
}

Relation SqlParser::exprProject()
{
	// Expect an attribute list
	vector<string> attributes = attributeList();
	
	// Expect a atomic expression	
	Relation relation = atomicExpr();

	// Fire the project
	return engine->exprProject(&relation, attributes);
}

Relation SqlParser::exprRename()
{
	// Expect an attribute list
	vector<string> attributes = attributeList();
	
	// Expect a atomic expression	
	Relation relation = atomicExpr();

	// Fire the project
	return engine->exprRenaming(&relation, attributes);
}

vector<string> SqlParser::attributeList()
{
	if( ! expect(Token::LEFTPAREN)) throw runtime_error("expected LEFTPAREN");

	increment();

	vector<string> attributes;
	while(token.getType() == Token::IDENTIFIER)
	{
		attributes.push_back(token.getValue());
		increment();

		// Now we expect a comma or a )
		if(token.getType() != Token::COMMA && token.getType() != Token::RIGHTPAREN) throw runtime_error("expected , or )");
		
		if(token.getType() == Token::COMMA) increment();
	}

	increment();

	return attributes;
}

Relation SqlParser::atomicExpr()
{

	if(token.getType() == Token::IDENTIFIER)
	{
		return *engine->getRelation(token.getValue());
	}
	if(token.getType() == Token::LEFTPAREN)
	{
		increment();
		Relation relation = expr();
		if(expect(Token::RIGHTPAREN)) return relation;
		throw runtime_error("exptected RIGHTPAREN");
	}
}

void SqlParser::semicolon()
{
	cout << "End of Statement" << endl;
}