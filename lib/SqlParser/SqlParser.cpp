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
	//cout << endl << "### [" << currentID << "] " << token.getTypeName() << ": " << token.getValue() << endl;
}

void SqlParser::expect(Token::TokenTypes type)
{
	Token against = Token(type, "temp");

	if(tokens[currentID + 1].getType() == type)
	{
		increment();
	}
	else
	{
		throw runtime_error("Expected " + against.getTypeName() + ", but got "+ token.getTypeName());
	}
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
	currentID = 0;
	setToken();

	program();
}

bool SqlParser::program()
{	
	if(tokens[tokens.size()-1].getType() != Token::SEMICOLON) throw runtime_error("Expected SEMICOLON at end of statement");
	if(token.getType() == Token::IDENTIFIER)
	{
		query();
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
	expect(Token::LEFTARROW);

	increment();

	Relation relation = expr();
	relation.setName(relationName);

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

		case Token::UPDATE:
			update();
			break;

		case Token::INSERT:
			insert();
			break;

		case Token::DELETE:
			deleteRows();
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
			return atomicExpr();
			break;

		case Token::RENAME:
			return exprRename();
			break;
	}	
}

void SqlParser::insert()
{
	expect(Token::INTO);
	expect(Token::IDENTIFIER);

	string relationName = token.getValue();

	expect(Token::VALUES);
	expect(Token::FROM);

	increment();

	// Token can be either a ( or RELATION
	if(token.getType() == Token::RELATION)
	{
		increment();

		// Inserting from expression
		Relation relation = expr();

		vector<Tuple> tuples = *relation.getTuples();

		for(int i=0; i<tuples.size(); i++)
		{
			engine->insert(relationName, tuples[i]);
		}
	}
	else if(token.getType() == Token::LEFTPAREN)
	{
		vector<string> tuple;

		do
		{
			increment();
			tuple.push_back(token.getValue());
			increment();
		}
		while(token.getType() == Token::COMMA);

		if(token.getType() != Token::RIGHTPAREN) throw runtime_error("Expected RIGHTPAREN");

		engine->insert(relationName, tuple);
	}
}

void SqlParser::update()
{
	expect(Token::IDENTIFIER);
	string relationName = token.getValue();

	Relation* relation = engine->getRelation(relationName);

	expect(Token::SET);


	vector<pair<int, string>> toset;
	do
	{
		expect(Token::IDENTIFIER);
		int attributeID = relation->getAttributeIDFromName(token.getValue());

		expect(Token::EQUALSIGN);

		increment();
		if( (token.getType() != Token::NUMBER) && (token.getType() != Token::LITERAL)) throw	 runtime_error("Expected number or literal");
			
		// Put in the attribute value pair
		toset.push_back(make_pair(attributeID, token.getValue()));

		increment();
	}
	while(token.getType() == Token::COMMA);

	expect(Token::WHERE);
	increment();

	// Expect an condition list (Just read it now, parse later)
	vector<Token> conditions;

	while(canIncrement())
	{
		conditions.push_back(token);
		increment();
	}

<<<<<<< HEAD
	if(token.getType() == Token::SELECT)
	{
		return exprSelect();
	}

=======
	ConditionParser* conditionParser = new ConditionParser(conditions, engine, *relation);
	engine->update(relationName, toset, conditionParser->parse());
}

void SqlParser::deleteRows()
{
	expect(Token::FROM);
	expect(Token::IDENTIFIER);
	string relationName = token.getValue();

	expect(Token::WHERE);
	increment();

	// Expect an condition list (Just read it now, parse later)
	vector<Token> conditions;

	while(canIncrement())
	{
		conditions.push_back(token);
		increment();
	}

	Relation* relation = engine->getRelation(relationName);

	ConditionParser* conditionParser = new ConditionParser(conditions, engine, *relation);
	cout << conditionParser->parse().size() << endl;
	engine->deleteTuples(relationName, conditionParser->parse());
}

void SqlParser::create()
{
	expect(Token::TABLE);
	expect(Token::IDENTIFIER);
	string relationName = token.getValue();

	// Read in the attributes and types
	expect(Token::LEFTPAREN);

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
			expect(Token::LEFTPAREN);
			expect(Token::NUMBER);
			size = token.getNumeric();
			expect(Token::RIGHTPAREN);

			attribute = Attribute(type, name, false, size);
		}
		else
		{
			attribute = Attribute(type, name);
		}

		attributes.push_back(attribute);

		if( ! peek(Token::RIGHTPAREN))
		{
			expect(Token::COMMA);
		}
		increment();
	}

	expect(Token::PRIMARY);
	expect(Token::KEY);

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

	expect(Token::LEFTPAREN);

	while(parenDepth > 0)
	{
		increment();
		if(token.getType() == Token::LEFTPAREN) parenDepth++;

		if(token.getType() == Token::RIGHTPAREN) parenDepth--;

		tokens.push_back(token);
	}

	tokens.pop_back();

	increment();

	return tokens;
>>>>>>> 5009bb866b3ea6cc78f560d986579a47fd402e67
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

Relation SqlParser::exprProductParser()
{
	// Expect atomic expressions
	Relation relationA = atomicExpr();
	Relation relationB = atomicExpr();

	// Fire the project
	return engine->exprProduct(&relationA, &relationB);
}

Relation SqlParser::exprDifferenceParser()
{
	// Expect atomic expressions
	Relation relationA = atomicExpr();
	Relation relationB = atomicExpr();

	// Fire the project
	return engine->exprDifference(&relationA, &relationB);
}

Relation SqlParser::exprUnionParser()
{
	// Expect atomic expressions
	Relation relationA = atomicExpr();
	Relation relationB = atomicExpr();

	// Fire the project
	return engine->exprUnion(&relationA, &relationB);
}

Relation SqlParser::exprIntersectionPaser(Relation* a,Relation* b)
{
	// Ensure that the relations are union-compatible
	if ( ! engine->isUnionCompatible(a,b))
	{
		throw runtime_error("Trying to take the union of non-union-compatible relations.");
	}

	// Make a copy of Relation "a", and create return variable of type Relation
	Relation tempRelation = *a;
	Relation intersectRelation;

	for( int i =0; i < b->getTuples()->size(); i++)
	{
		// Put what is in "b" at position "i" into bTuple
		Tuple* bTuple = b->getTuple(i);

		// Is the tuple in "b" and also in "a"?
		if( engine->exists(tempRelation, bTuple))
		{
			// If true, put that tuple in intersectRelation
			intersectRelation.addTuple(*bTuple);
		}

	}

	return intersectRelation;
}

vector<string> SqlParser::attributeList()
{
	expect(Token::LEFTPAREN);

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
		expect(Token::RIGHTPAREN);
		return relation;
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