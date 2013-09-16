using namespace std;

#include "ConditionParser.h"
#include "../SqlTokenizer/Token.h"
#include "../DBMSEngine/Engine.h"

#include <iostream>
#include <sstream>
#include <algorithm>

void ConditionParser::setToken()
{
	token = tokens[currentID];
	//cout << endl << "### [" << currentID << "] " << token.getTypeName() << ": " << token.getValue() << endl;
}

bool ConditionParser::expect(Token::TokenTypes type)
{
	if(tokens[currentID + 1].getType() == type)
	{
		increment();
		return true;
	}

	return false;
}

bool ConditionParser::peek(Token::TokenTypes type)
{
	if(canIncrement())
	{
		return tokens[currentID + 1].getType() == type;
	}

	return false;
}

void ConditionParser::increment()
{
	if(currentID == tokens.size() - 1) throw runtime_error("Can't increase counter any more.");
	currentID++;
	setToken();
}

bool ConditionParser::canIncrement()
{
	return ! (currentID == tokens.size() - 1);
}

vector<int> ConditionParser::parse()
{
	cout << "==============================" << endl;
	cout << "Condition Parser" << endl;
	cout << "==============================" << endl;


	currentID = 0;
	setToken();
	return condition();
}

// condition { || condition}
vector<int> ConditionParser::condition()
{
	vector<int> rows = conjunction();
	
	// There could be more ||s
	if( ! peek(Token::BOR)) return rows;
	while(canIncrement())
	{
		if(peek(Token::RIGHTPAREN)) return rows;
		if( ! expect(Token::BOR)) throw runtime_error("Expected ||");	

		increment();
		vector<int> nextRows = conjunction();
		vector<int> unioned;

		// Since we're doing &&, do a set intersection
		set_union(rows.begin(), rows.end(), nextRows.begin(), nextRows.end(), back_inserter(unioned));

		rows=unioned;
	}	

	return rows;
}

// comparison { && comparison }
vector<int> ConditionParser::conjunction()
{
	vector<int> rows = comparison();

	// There could be more &&s
	if( ! peek(Token::BAND)) return rows;
	while(canIncrement())
	{
		if(peek(Token::RIGHTPAREN)) return rows;
		if( ! expect(Token::BAND)) throw runtime_error("Expected &&");	

		increment();
		vector<int> nextRows = comparison();
		vector<int> intersected;

		// Since we're doing &&, do a set intersection
		set_intersection(rows.begin(), rows.end(), nextRows.begin(), nextRows.end(), back_inserter(intersected));

		rows=intersected;
	}	

	return rows;	
}

vector<int> ConditionParser::comparison()
{
	vector<int> rows;

	// Deal with actual comparisons
	if( token.getType() == Token::IDENTIFIER || token.getType() == Token::LITERAL || token.getType() == Token::NUMBER)
	{
		Token left = token;
		increment();

		Token op = token;
		increment();

		Token right = token;
		
		// Find every tuple that fits the conditions
		for(int i=0; i < relation.getTuples()->size(); i++)
		{
			Tuple tuple = *relation.getTuple(i);

			string leftVal, rightVal;

			if(left.getType() == Token::LITERAL || left.getType() == Token::NUMBER)
			{
				leftVal = left.getValue();
			}
			else
			{
				leftVal = tuple.getValues()[relation.getAttributeIDFromName(left.getValue())];
			}

			if(right.getType() == Token::LITERAL || right.getType() == Token::NUMBER)
			{
				rightVal = right.getValue();
			}
			else
			{
				rightVal = tuple.getValues()[relation.getAttributeIDFromName(right.getValue())];
			}

			switch (op.getType())
			{
				case Token::EQ:
					if(leftVal == rightVal) rows.push_back(i);
					break;

				case Token::NEQ:
					if(leftVal != rightVal) rows.push_back(i);				
					break;

				case Token::LT:
					if(atoi(leftVal.c_str()) < atoi(rightVal.c_str())) rows.push_back(i);				
					break;

				case Token::LEQ:
					if(atoi(leftVal.c_str()) <= atoi(rightVal.c_str())) rows.push_back(i);				
					break;

				case Token::GT:
					if(atoi(leftVal.c_str()) > atoi(rightVal.c_str())) rows.push_back(i);				
					break;

				case Token::GEQ:
					if(atoi(leftVal.c_str()) >= atoi(rightVal.c_str())) rows.push_back(i);				
					break;
			}	
			
		}	
		
		return rows;
	}

	// Or back up to condition
	if(token.getType() == Token::LEFTPAREN)
	{
		increment();
		rows = condition();
		
		if( ! expect(Token::RIGHTPAREN)) throw runtime_error("Expected RIGHTPAREN");
		return rows;
	}
}


void ConditionParser::semicolon()
{
	cout << "End of Statement" << endl;
}