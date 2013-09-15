#ifndef SQLPARSER_SQLPARSER_H_
#define SQLPARSER_SQLPARSER_H_

using namespace std;

#include "../SqlTokenizer/Token.h"
#include "../DBMSEngine/Engine.h"

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

class SqlParser
{
	public:
		SqlParser(vector<Token> tokens, Engine* e) : tokens(tokens), engine(e)  {};
		vector<Token> getTokens() { return tokens; }
		void parse();

	private: 
	    vector<Token> tokens;
	    Engine* engine;
	    Token token;
	    int currentID;
	    void setToken();
	    void increment();
	    bool program();
	    bool command();
	    bool query();
	    Relation expr();
	    Relation atomicExpr();
	    Relation exprProject();
	    Relation exprRename();
	    Relation exprProductParser();
	    Relation exprDifferenceParser();
	    Relation exprUnionParser();
	    Relation exprIntersectionParser();
	    vector<string> attributeList();
	    bool expect(Token::TokenTypes type);
	    void semicolon();

};

#endif