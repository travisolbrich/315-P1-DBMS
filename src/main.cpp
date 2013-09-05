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
		
		cout << endl << "==============================" << endl;
		cout << "Engine" << endl;
		cout << "==============================" << endl;

		vector<string> values;
		values.push_back("1");
		values.push_back("Hello");

		vector<string> second;
		second.push_back("2");
		second.push_back("This is cool");

		vector<Attribute> attributes;
		attributes.push_back(Attribute(Attribute::INTEGER, "ID", true));
		attributes.push_back(Attribute(Attribute::VARCHAR, "Sentence"));

		Engine* engine = new Engine();
		engine->create("Sentences", attributes);
		engine->insert("Sentences", values);
		engine->insert("Sentences", second);
		engine->show("Sentences");
	}
	catch (exception& e)
	{
		cout << "Exception: " <<  e.what() << "\n";
	}

	return 0;
}

