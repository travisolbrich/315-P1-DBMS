#ifndef SQLTOKENIZER_SQLTOKENIZER_H_
#define SQLTOKENIZER_SQLTOKENIZER_H_

using namespace std;

#include "Token.h"

#include <iostream>
#include <string>
#include <vector>

class SqlTokenizer
{
	public:
		SqlTokenizer(string query) : query(query) {};
		string getQuery() {	return query; }
		void split();
		string readAhead(int);

	private: 
		string query;
		string::iterator iterator;
	    vector<Token> tokens;
	    string singleSymbols[7] = {"<", ">", "{", "}", "+", "-", "*"};
		string doubleSymbols[7] = {"==", "!=", "<=", ">=", "<-", "||", "&&"};
};

#endif