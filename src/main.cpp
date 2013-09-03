using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"
#include "../lib/SqlTokenizer/Token.h"
#include "../lib/SqlParser/SqlParser.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
	string query = "OPEN SELECT people;";

	cout << "Query: " << query << "\n";

	SqlTokenizer* tokenzier = new SqlTokenizer(query);

	try 
	{
		vector<Token> tokens = tokenzier->split();
		cout<<tokens.size()<<" tokens have been collected:\n\n";

		for(int i=0; i < tokens.size(); i++)
		{
			cout<<"RECOGNIZED: "<<tokens[i].getTypeName()<<"\n            "<<tokens[i].getValue()<<"\n\n";
		}

		SqlParser* parser = new SqlParser(tokens);

		parser->parse();
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}

