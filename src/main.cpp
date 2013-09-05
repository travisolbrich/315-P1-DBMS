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
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
	}


	vector<string> values;
	values.push_back("1");
	values.push_back("Hello");

	vector<string> second;
	second.push_back("2");
	second.push_back("This is cool");
	
	Tuple* tuple = new Tuple(values);

	vector<Attribute> attributes;
	attributes.push_back(Attribute(Attribute::INTEGER, "ID"));
	attributes.push_back(Attribute(Attribute::VARCHAR, "Sentence"));

	vector<Tuple> tuples;
	tuples.push_back(Tuple(values));
	tuples.push_back(Tuple(second));

	Relation* relation = new Relation("Sentences", attributes, tuples);

	cout << relation->getName();
	cout << endl << relation->getTuples().size();
	cout << endl << relation->getAttributes().size();

	cout << endl;

	Engine* engine = new Engine(*relation);
	engine->show("Sentences");

	return 0;
}

