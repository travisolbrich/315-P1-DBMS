#ifndef SQLTOKENIZER_SQLTOKENIZER_H_
#define SQLTOKENIZER_SQLTOKENIZER_H_

using namespace std;

#include <iostream>
#include <string>

class SqlTokenizer
{
	private: 
		string query;
		string::iterator iterator;

	public:
		SqlTokenizer(string query) : query(query) {};
		string getQuery() {	return query; }
};

#endif