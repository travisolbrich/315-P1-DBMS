using namespace std;

#include "SqlParser.h"
#include "../SqlTokenizer/Token.h"

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
		currentID++;
		return true;
	}

	return false;
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

void SqlParser::program()
{	
	if(token.getType() == Token::IDENTIFIER)
	{
		cout<<"Expect query"<<endl;
	}
	else
	{
		cout<<"Expect command"<<endl;
		command();
	}
}

void SqlParser::command()
{
	switch (token.getType())
	{
		case Token::OPEN: 
			cout << "Recognized OPEN command" << endl;
			cout<< "Expect relation name (identifier) next... ";
			if( ! expect(Token::IDENTIFIER))
			{
				cout << "[BAD]" << endl;	
				return;			
			} 
			cout << "[Good]" << endl;
			setToken();

			cout << "Relation Name: " << token.getValue()<<endl;
			cout << "Opening " << token.getValue() << endl;
			cout << "Expect semicolon to end... ";

			if ( ! expect(Token::SEMICOLON))
			{
				cout << "[BAD]" << endl;	
				return;	
			}
			cout << "[Good]" << endl;
			setToken();
			semicolon();
			
			break;

		default:
			cout << "Unrecognized Command" << endl;
			break;
	}
}

void SqlParser::semicolon()
{
	cout << "End of Statement" << endl;
}