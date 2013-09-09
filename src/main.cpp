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

		vector<int> update;
		update.push_back(1);

		vector<pair<int, string>> toset;
		toset.push_back(make_pair(1, string("Yup.")));

		vector<int> deletions;
		deletions.push_back(0);

		Relation copy = *engine->getRelation("Sentences");
		copy.setName("originalSentences");
		engine->addRelation(copy);

		engine->show("Sentences");
		engine->update("Sentences", toset, update);

		
		cout << "\nUPDATED SENTENCES\n";

		engine->show("Sentences");
		engine->deleteTuples("Sentences", deletions); 

		cout << "\nDELETED FROM SENTENCES\n";

		engine->show("Sentences");


		Relation merge = engine->exprUnion(engine->getRelation("Sentences"), engine->getRelation("originalSentences"));
		merge.setName("union");
		engine->addRelation(merge);

		cout << "\nUNION OF ORIGINAL SENTENCES AND MOST RECENT SENTENCES\n";

		engine->show("union");
		engine->show("Sentences");

		Relation diff = engine->exprDifference(engine->getRelation("union"), engine->getRelation("Sentences"));
		diff.setName("difference");
		engine->addRelation(diff);

		cout << "\nDIFFERENCES OF UNION AND MOST RECENT SENTENCES\n";

		engine->show("difference");

		engine->show("Sentences");

		Relation product = engine->exprProduct(engine->getRelation("union"), engine->getRelation("originalSentences"));
		product.setName("product");
		engine->addRelation(product);

		cout << "\nPRODUCT OF UNION AND MOST ORIGINAL SENTENCES\n";

		engine->show("product");

		engine->show("Sentences");
		//renaming testing 
		vector<string> renaming ={"NEWID","NEWSENTENCE"};
		Relation newName = engine->exprRenaming(engine->getRelation("Sentences"), renaming);
		newName.setName("NEWRelation");
		engine->addRelation(newName);

		engine->show("NEWRelation");
		engine->show("Sentences"); 
		
		//Exiting
		vector<int> selectTest;
		selectTest.push_back(1);
		selectTest.push_back(4);
		selectTest.push_back(2);

		Relation select = engine->select(&product, selectTest);
		select.setName("selectProduct");
		engine->addRelation(select);
		engine->show("selectProduct");

		engine->exit();
	}
	catch (exception& e)
	{
		cout << "Exception: " <<  e.what() << "\n";
	}

	return 0;
}

