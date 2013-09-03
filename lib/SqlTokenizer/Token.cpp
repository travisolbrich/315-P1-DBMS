using namespace std;

#include "SqlTokenizer.h"
#include "Token.h"

#include <iostream>
#include <sstream>
#include <algorithm>

string Token::getTypeName()
{
	TokenTypes type = this->type;

	if      (type == DIFF) return "DIFF";
	else if (type == PRODUCT) return "PRODUCT";
	else if (type == UNION) return "UNION";
	else if (type == LEFTBRACE) return "LEFTBRACE";
	else if (type == RIGHTBRACE) return "RIGHTBRACE";
	else if (type == LEFTARROW) return "LEFTARROW";
	else if (type == EQ) return "EQ";
	else if (type == NEQ) return "NEQ";
	else if (type == LT) return "LT";
	else if (type == GT) return "GT";
	else if (type == LEQ) return "LEQ";
	else if (type == GEQ) return "GEQ";
	else if (type == BOR) return "BOR";
	else if (type == BAND) return "BAND";
	else if (type == SELECT) return "SELECT";
	else if (type == PROJECT) return "PROJECT";
	else if (type == RENAME) return "RENAME";
	else if (type == OPEN) return "OPEN";
	else if (type == CLOSE) return "CLOSE";
	else if (type == WRITE) return "WRITE";
	else if (type == PRIMARY) return "PRIMARY";
	else if (type == EXIT) return "EXIT";
	else if (type == SHOW) return "SHOW";
	else if (type == CREATE) return "CREATE";
	else if (type == TABLE) return "TABLE";
	else if (type == PRIMARY) return "PRIMARY";
	else if (type == KEY) return "KEY";
	else if (type == UPDATE) return "UPDATE";
	else if (type == SET) return "SET";
	else if (type == WHERE) return "WHERE";
	else if (type == INSERT) return "INSERT";
	else if (type == INTO) return "INTO";
	else if (type == VALUES) return "VALUES";
	else if (type == FROM) return "FROM";
	else if (type == RELATION) return "RELATION";
	else if (type == DELETE) return "DELETE";
	else if (type == VARCHAR) return "VARCHAR";
	else if (type == INTEGER) return "INTEGER";
	else if (type == LITERAL) return "LITERAL";
	else if (type == IDENTIFIER) return "IDENTIFIER";
	else if (type == NUMBER) return "NUMBER";
	else if (type == SEMICOLON) return "SEMICOLON";
	else return "Error: Unrecognized Token.";
}