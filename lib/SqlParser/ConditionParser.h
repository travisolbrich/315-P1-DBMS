#ifndef ConditionParser_ConditionParser_H_
#define ConditionParser_ConditionParser_H_

using namespace std;

#include "../SqlTokenizer/Token.h"
#include "../DBMSEngine/Engine.h"
#include "../DBMSEngine/Relation.h"

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

class ConditionParser
{
	public:
		ConditionParser(vector<Token> tokens, Engine* e, Relation relation) : tokens(tokens), engine(e), relation(relation)  {};
		vector<Token> getTokens() { return tokens; }
		vector<int> parse();

	private: 
	    vector<Token> tokens;
	    Engine* engine;
	    Token token;
	    Relation relation;
	    int currentID;
	    void setToken();
	    void increment();
	    bool canIncrement();

	    vector<int> condition();
		vector<int> conjunction();
	    vector<int> comparison();

	    bool expect(Token::TokenTypes type);
	    bool peek(Token::TokenTypes type);
	    void semicolon();

};

#endif