#ifndef SQLTOKENIZER_TOKEN_H_
#define SQLTOKENIZER_TOKEN_H_

using namespace std;

#include <iostream>
#include <string>
#include <vector>

class Token
{
	public:
		enum TokenTypes { IDENTIFIER, SELECT, EQ, NEQ, LT, GT, LEQ, GEQ, LITERAL, PROJECT, RENAME,
						  BOR, BAND, UNION, DIFF, PRODUCT, OPEN, CLOSE, WRITE, EXIT, SHOW, CREATE, 
						  PKEY, UPDATE, INSERT, VALUES, RELATION, DELETE, WHERE, VARCHAR, INTEGER,
						  LEFTBRACE, RIGHTBRACE, LEFTARROW };

		Token(TokenTypes type, string value) : type(type), value(value) {};
		TokenTypes getType() { return type; }
		string getValue() {	return value; }

	private: 
		string value;
		TokenTypes type;
};

#endif