using namespace std;

#include "SqlParser.h"
#include "ConditionParser.h"
#include "../SqlTokenizer/Token.h"
#include "../DBMSEngine/Attribute.h"
#include "../DBMSEngine/Engine.h"

#include <iostream>
#include <sstream>
#include <algorithm>

void SqlParser::setToken()
{
	token = tokens[currentID];
	cout << endl << "### [" << currentID << "] " << token.getTypeName() << ": " << token.getValue() << endl;
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

bool SqlParser::peek(Token::TokenTypes type)
{
	if(canIncrement())
	{
		if(tokens[currentID + 1].getType() == type) return true;
	}

	return false;
}

void SqlParser::increment()
{
	if( ! canIncrement()) throw runtime_error("Can't increase counter any more.");
	currentID++;
	setToken();
}


bool SqlParser::canIncrement()
{
	return ! (currentID == tokens.size() - 1);
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
		bool status = query();
		if ( ! status) cout << "[FAILURE]\n";
	}
	else
	{
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
	relation.setName(relationName);

	if( ! expect(Token::SEMICOLON)) throw runtime_error("Expected ;");

	engine->show(&relation);
	engine->addRelation(relation);
	return true;
}

bool SqlParser::command()
{
	switch (token.getType())
	{
		case Token::EXIT:
			engine->exit();
			break;

		case Token::SHOW:
		{	
			increment();
			Relation relation = atomicExpr();
			engine->show(&relation);
			break;
		}

		case Token::CREATE:
			create();
			break;
	}
}

Relation SqlParser::expr()
{
	switch (token.getType())
	{
		case Token::LEFTPAREN:
			return atomicExpr();
			break;

		case Token::SELECT:
			return exprSelect();
			break;

		case Token::PROJECT:
			return exprProject();
			break;

		case Token::IDENTIFIER:
			// If it's just an identifier (followed by ; or ')') then it's a atomic expression
			cout <<"IDENT SWITCH"<<endl;
			return atomicExpr();
			break;

		case Token::RENAME:
			return exprRename();
			break;
	}	
}

void SqlParser::create()
{
	if( ! expect(Token::TABLE)) throw runtime_error("Expected TABLE");
	if( ! expect(Token::IDENTIFIER)) throw runtime_error("Expected relation name");
	string relationName = token.getValue();

	// Read in the attributes and types
	if( ! expect(Token::LEFTPAREN)) throw runtime_error("expected LEFTPAREN");

	increment();
	vector<Attribute> attributes;

	
	while(token.getType() != Token::RIGHTPAREN)
	{
		string name = token.getValue();

		increment();
		if( (token.getType() != Token::VARCHAR) && (token.getType() != Token::INTEGER)) throw runtime_error("Expected INTEGER or VARCHAR");

		Attribute::Type type = (token.getType() == Token::VARCHAR) ? Attribute::Type::VARCHAR : Attribute::Type::INTEGER;
		
		Attribute attribute;
		if(type == Attribute::Type::VARCHAR)
		{
			int size;
			if ( ! expect(Token::LEFTPAREN)) throw runtime_error("Expected (");
			if ( ! expect(Token::NUMBER)) throw runtime_error("Expected size");
			size = token.getNumeric();
			if ( ! expect(Token::RIGHTPAREN)) throw runtime_error("Expected )");

			attribute = Attribute(type, name, false, size);
		}
		else
		{
			attribute = Attribute(type, name);
		}

		attributes.push_back(attribute);

		if( ! peek(Token::RIGHTPAREN))
		{
			if ( ! expect(Token::COMMA)) throw runtime_error("Expected COMMA");
		}
		increment();
	}

	if ( ! expect(Token::PRIMARY)) throw runtime_error("Expected PRIMARY");
	if ( ! expect(Token::KEY)) throw runtime_error("Expected KEY");

	vector<string> keys = attributeList();

	for(int i=0; i < attributes.size(); i++)
	{
		for(int j=0; j < keys.size(); j++)
		{
			if(attributes[i].getValue() == keys[j])
			{
				attributes[i].setPrimary(true);
			}
		}
	}

	engine->create(relationName, attributes);
}

Relation SqlParser::exprSelect()
{
	// Expect an condition list (Just read it now, parse later)
	vector<Token> conditions = conditionList();
	
	// Expect a atomic expression	
	Relation relation = atomicExpr();

	ConditionParser* conditionParser = new ConditionParser(conditions, engine, relation);
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

// Handle union, difference, or product
Relation SqlParser::combine(Relation relation)
{
	Relation left = relation;

	increment();
	Token operation = token;

	increment();
	Relation right = atomicExpr();

	switch(operation.getType())
	{
		case Token::UNION:
			return engine->exprUnion(&left, &right);
			break;

		case Token::DIFF:
			return engine->exprDifference(&left, &right);
			break;

		case Token::PRODUCT:
			return engine->exprProduct(&left, &right);
			break;

		default:
			throw runtime_error("Incorrect comparison type.");
	}
}

Relation SqlParser::atomicExpr()
{
	Relation relation;

	if(token.getType() == Token::IDENTIFIER)
	{
		relation =  *engine->getRelation(token.getValue());
	}
	if(token.getType() == Token::LEFTPAREN)
	{
		increment();
		relation = expr();
		if( ! expect(Token::RIGHTPAREN)) 
		throw runtime_error("exptected RIGHTPAREN");
	}

	// If the next token is a +*-, do combine
	if(peek(Token::UNION) || peek(Token::PRODUCT) || peek(Token::DIFF))
	{
		relation = combine(relation);
	}

	return relation;
}

void SqlParser::semicolon()
{
	cout << "End of Statement" << endl;
}