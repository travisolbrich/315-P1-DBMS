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
		vector<Token> split();
		string readAhead(int);
		Token recognize(string text);

	private: 
		string query;
		string::iterator iterator;
	    vector<Token> tokens;
	    string singleSymbols[12] = {"<", ">", "{", "}", "+", "-", "*", ";", "(", ")", ",", "="};
		string doubleSymbols[7] = {"==", "!=", "<=", ">=", "<-", "||", "&&"};
};

#endif