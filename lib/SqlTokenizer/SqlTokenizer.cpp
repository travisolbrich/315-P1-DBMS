using namespace std;

#include "SqlTokenizer.h"
#include "InvalidSymbolException.h"
#include "Token.h"

#include <iostream>
#include <sstream>
#include <algorithm>

vector<Token> SqlTokenizer::split()
{
	iterator = query.begin();
	string text;

	while( iterator != query.end())
	{
		bool isNumber = false;
		bool isLiteral = false; 
		text = "";

		// Ignore whitespace
		if( *iterator == ' ')
		{
			iterator++;
		}

		// Grab text (allow underscores), includes potential commands
		else if (isalpha(*iterator))
		{
			while(iterator != query.end() && (isalpha(*iterator) || isdigit(*iterator) || *iterator == '_'))
			{
				text += *iterator;
				iterator++;
			}
		}

		// Grab numbers
		else if (isdigit(*iterator))
		{
			while(iterator != query.end() && isdigit(*iterator))
			{
				text += *iterator;
				iterator++;
			}
			isNumber = true;
		}

		// Try to match two-character symbols
		else if (count(doubleSymbols, doubleSymbols+7, readAhead(2)))
		{
			text = readAhead(2);
			iterator+=2;
		}

		// Try to match single-character symbols
		else if (count(singleSymbols, singleSymbols+8, readAhead(1)))
		{
			text = readAhead(1);
			iterator++;
		}

		// Literals
		else if (*iterator == '"')
		{
			iterator++;
			while(iterator != query.end() && *iterator != '"')
			{
				text += *iterator;
				iterator++;
			}

			// This character should be a '"'. If not, then it's the end of the string.
			// and we should throw an exception
			if(*iterator != '"')
			{
				throw InvalidSymbolException;
			}
			else
			{
				iterator++; 
			}

			isLiteral = true;
		}
		
		else
		{
			throw InvalidSymbolException;
		}

		if (text != "")
		{
			Token recognized = recognize(text);

			if(isNumber) recognized = Token(Token::NUMBER, text);
			if(isLiteral) recognized = Token(Token::LITERAL, text);

			tokens.push_back(recognized);

		}
	}
	
	return tokens;
}

/**
  * Get the next n characters without advancing the iterator. Reads unitl
  * the distance is reached or until the string ends.
  */
string SqlTokenizer::readAhead(int distance)
{
	stringstream stream;
	string::iterator it = iterator;
	
	for (int i = 0; i < distance; i++)
	{
		stream << *it;
		
		if(it == query.end())
		{
			return stream.str();
		}

		it++;
	}

	return stream.str();
}

/**
  * When given text like INSERT or relation_name, determine the kind of
  * token it is.
  */
Token SqlTokenizer::recognize(string text)
{
	if      (text == "-" )	return Token(Token::DIFF, text);
	else if (text == "*" )			return Token(Token::PRODUCT, text);
	else if (text == "+" )			return Token(Token::UNION, text);
	else if (text == "{" )			return Token(Token::LEFTBRACE, text);
	else if (text == "}")			return Token(Token::RIGHTBRACE, text);
	else if (text == "<-" )			return Token(Token::LEFTARROW, text);
	else if (text == ";" )			return Token(Token::SEMICOLON, text);
	else if (text == "==" )			return Token(Token::EQ, text);
	else if (text == "!=" )			return Token(Token::NEQ, text);
	else if (text == "<" )			return Token(Token::LT, text);
	else if (text == ">" )			return Token(Token::GT, text);
	else if (text == "<=" )			return Token(Token::LEQ, text);
	else if (text == ">=" )			return Token(Token::GEQ, text);
	else if (text == "||" )			return Token(Token::BOR, text);
	else if (text == "&&" )			return Token(Token::BAND, text);
	else if (text == "select")		return Token(Token::SELECT, text);
	else if (text == "project")		return Token(Token::PROJECT, text);
	else if (text == "RENAME")		return Token(Token::RENAME, text);
	else if (text == "OPEN")		return Token(Token::OPEN, text);
	else if (text == "CLOSE")		return Token(Token::CLOSE, text);
	else if (text == "WRITE")		return Token(Token::WRITE, text);
	else if (text == "EXIT")		return Token(Token::EXIT, text);
	else if (text == "SHOW")		return Token(Token::SHOW, text);
	else if (text == "CREATE")		return Token(Token::CREATE, text);
	else if (text == "TABLE")		return Token(Token::TABLE, text);
	else if (text == "PRIMARY")		return Token(Token::PRIMARY, text);
	else if (text == "KEY")			return Token(Token::KEY, text);
	else if (text == "UPDATE")		return Token(Token::UPDATE, text);
	else if (text == "SET")			return Token(Token::SET, text);
	else if (text == "WHERE")		return Token(Token::WHERE, text);
	else if (text == "INSERT")		return Token(Token::INSERT, text);
	else if (text == "INTO")		return Token(Token::INTO, text);
	else if (text == "VALUES")		return Token(Token::VALUES, text);
	else if (text == "FROM")		return Token(Token::FROM, text);
	else if (text == "RELATION")	return Token(Token::RELATION, text);
	else if (text == "DELETE")		return Token(Token::DELETE, text);
	else if (text == "VARCHAR")		return Token(Token::VARCHAR, text);
	else if (text == "INTEGER")		return Token(Token::INTEGER, text);
	
	else return Token(Token::IDENTIFIER, text);
}