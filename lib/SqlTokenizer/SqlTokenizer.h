#ifndef SQLTOKENIZER_SQLTOKENIZER_H_
#define SQLTOKENIZER_SQLTOKENIZER_H_

using namespace std;

#include <iostream>
#include <string>
#include <vector>

class SqlTokenizer
{
	private: 
		string query;
		string::iterator iterator;
	    vector<string> tokens;
	    string singleSymbols[7] = {"<", ">", "{", "}", "+", "-", "*"};
		string doubleSymbols[7] = {"==", "!=", "<=", ">=", "<-", "||", "&&"};

	public:
		SqlTokenizer(string query) : query(query) {};
		string getQuery() {	return query; }
		void split();
};

#endif