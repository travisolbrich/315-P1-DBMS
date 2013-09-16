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

	try 
	{
		// Create the engine. There are no relations to add to it yet
		Engine* engine = new Engine();
		
		// Create a table
		vector<Attribute> attributes = 
		{
			Attribute(Attribute::INTEGER, "ID", true),
			Attribute(Attribute::VARCHAR, "first_name"),
			Attribute(Attribute::VARCHAR, "last_name")
		};

		engine->create("Names", attributes);

		cout << "!!! 'Names' relation created" << endl << endl;

		// Insert to the relation
		vector<string> tuple = 
		{
			"1",
			"Bill", 
			"Nye"
		};

		engine->insert("Names", tuple);

		tuple = 
		{
			"2",
			"Steve", 
			"Steve"
		};

		engine->insert("Names", tuple);

		//string query = "people <- rename (Last, First) ( project (last_name, first_name) (Names) )";
		string query = "people <- select ((first_name != \"Billy\" && last_name == \"Steve\" && first_name == first_name) || ID == 43 || ID == 1) Names";

		cout << "Query: " << query << "\n";

		SqlTokenizer* tokenzier = new SqlTokenizer(query);
		vector<Token> tokens = tokenzier->split();
		cout<<tokens.size()<<" tokens have been collected:\n\n";

		SqlParser* parser = new SqlParser(tokens, engine);

		parser->parse();
		/**
		cout << "==============================" << endl;
		cout << "Engine" << endl;
		cout << "==============================" << endl;
		
		

		tuple = 
		{
			"2",
			"Carll", 
			"Sagan"
		};

		engine->insert("Names", tuple);

		cout << "!!! Tuples inserted into 'Names'" << endl << endl;

		// Show a relation
		cout << "!!! Showing 'Names'" << endl << endl;

		engine->show("Names");

		// Update a relation
		vector<int> updateIDs = { 1 };

		vector<pair<int, string>> toset;
		toset.push_back(make_pair(1, string("Carl")));
		
		engine->update("Names", toset, updateIDs);

		cout << "!!! Updated 'Names'. Set 'first_name' to 'Carl' on tupleID 1" << endl << endl;

		engine->show("Names");

		// Delete a tuple
		vector<int> deleteIDs = { 1 };
		engine->deleteTuples("Names", deleteIDs);

		cout << "!!! Deleted tuple 0 from 'Names'" << endl << endl;
		engine->show("Names");

		// Select a relation (make the copy)
		vector<int> selectIDs = {0};
		Relation namesCopy = engine->exprSelect(engine->getRelation("Names"), selectIDs);
		namesCopy.setName("Other");
		namesCopy.addTuple(tuple);

		tuple = {
			"4",
			"Neil",
			"Tyson"
		};
		engine->insert("Names", tuple);

		cout << "!!! Created a 'other' relation (using Select) and added a tuple to this relation and 'names'" << endl << endl;
		
		engine->show("Names");
		engine->show(&namesCopy);

		// Union
		Relation unionResult = engine->exprUnion(engine->getRelation("Names"), &namesCopy);
		unionResult.setName("Union of 'Names' and 'Other'");

		cout << "!!! Computed union of 'Names' and 'Other'" << endl << endl;

		engine->show(&unionResult);

		// Difference
		Relation differenceResult = engine->exprDifference(engine->getRelation("Names"), &namesCopy);
		differenceResult.setName("Difference of 'Names' and 'Other'");

		cout << "!!! Computed union of 'Names' and 'Other'" << endl << endl;

		engine->show(&differenceResult);

		// Product
		Relation productResult = engine->exprProduct(engine->getRelation("Names"), &namesCopy);
		productResult.setName("Product of 'Names' and 'Other'");

		cout << "!!! Computed product of 'Names' and 'Other'" << endl << endl;

		engine->show(&productResult);

		// Project
		vector<string> attributeNames = {"first_name"};

		Relation projectResult = engine->exprProject(engine->getRelation("Names"), attributeNames);
		projectResult.setName("Projection of 'Names'");

		cout << "!!! Computed Projection of 'Names'" << endl << endl;

		engine->show(&projectResult);

		// Rename
		vector<string> newAttributes = {"first"};

		Relation renameResult = engine->exprRenaming(&projectResult, newAttributes);
		renameResult.setName("Renaming of 'Projection of 'Names''");

		cout << "!!! Computed Renaming of 'Projection of 'Names''" << endl << endl;

		engine->show(&renameResult);
		
		//Exiting
		engine->exit();
		*/
	}
	catch (exception& e)
	{
		cout << "!!! " <<  e.what() << "\n";
	}
	
	return 0;

}

