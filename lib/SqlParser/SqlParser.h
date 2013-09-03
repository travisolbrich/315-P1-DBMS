#ifndef SQLPARSER_SQLPARSER_H_
#define SQLPARSER_SQLPARSER_H_

using namespace std;

#include "../SqlTokenizer/Token.h"

#include <iostream>
#include <string>
#include <vector>

class SqlParser
{
	public:
		SqlParser(vector<Token> tokens) : tokens(tokens) {};
		vector<Token> getTokens() { return tokens; }
		void parse();

	private: 
	    vector<Token> tokens;
	    Token token;
	    int currentID;
	    void setToken();
	    void program();
	    void command();
	    bool expect(Token::TokenTypes type);
	    void semicolon();

};

#endif