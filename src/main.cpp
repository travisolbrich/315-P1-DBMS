	using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"
#include "../lib/SqlTokenizer/Token.h"
#include "../lib/SqlParser/SqlParser.h"
#include "../lib/DBMSEngine/Relation.h"
#include "../lib/DBMSEngine/Engine.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{

		// Create the engine. There are no relations to add to it yet
		Engine* engine = new Engine();

		while(true)
		{
			string query;
			cout << "sql> ";
			getline(cin,query,';');
			query = query + ";"; // The cin gets rid of the ;

			try 
			{

				SqlTokenizer* tokenzier = new SqlTokenizer(query);
				vector<Token> tokens = tokenzier->split();

				if(tokens[0].getType() == Token::EXIT) return 0;
			
				SqlParser* parser = new SqlParser(tokens, engine);
				parser->parse();
			}
			catch (exception& e)
			{
				cout << "!!! " <<  e.what() << "\n";
			}
		}
	
	return 0;

}

