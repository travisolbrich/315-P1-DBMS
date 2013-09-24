#include "Engine.h"
#include "Attribute.h"
#include "../SqlTokenizer/SqlTokenizer.h"
#include "../SqlParser/SqlParser.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;
 

void Engine::open(string relation) 	
{
	string line;
	string filename = relation + ".db";
	ifstream dbFile (filename);

	if(dbFile.is_open())
	{
		while(getline(dbFile,line))
		{	
			if(line != "")
			{
				SqlTokenizer* tokenzier = new SqlTokenizer(line);
				vector<Token> tokens = tokenzier->split();
			
				SqlParser* parser = new SqlParser(tokens, this);
				parser->parse();				
			}		
		}
		dbFile.close();
	}
	else
	{
		throw runtime_error("File not found.");
	}

}

void Engine::write(string relation) 
{
	string filename = relation + ".db";
	ofstream outFile;
	outFile.open(filename, ios::out | ios::trunc);	
	outFile.close();
}

void Engine::close(string relationName) 
{
	string filename = relationName + ".db";
	ofstream outFile;
	outFile.open(filename, ios::out | ios::trunc);	
	
	Relation* relation = getRelation(relationName);

	// Create the table
	outFile << "CREATE TABLE " << relationName << " (";

	vector<Attribute>* attributes  = relation->getAttributes();
	vector<string> keys;
	for(int i=0; i<attributes->size(); i++)
	{
		Attribute* attribute = relation->getAttribute(i);

		outFile << attribute->getValue() << " " << attribute->getTypeName();
		if(attribute->getType() == Attribute::VARCHAR)
		{
			outFile << "(" << attribute->getSize() << ")";
		}
		if(i<attributes->size() - 1)
		{
			outFile << ", ";
		}
		if(attribute->isPrimary())
		{
			keys.push_back(attribute->getValue());
		}
	}
	outFile << ") PRIMARY KEY (";

	for(int i=0; i<keys.size(); i++)
	{
		outFile << keys[i];
		if(i < keys.size() - 1)
		{
			outFile << ", ";
		}
	}
	outFile << ");" << endl;
	
	// Write the data
	// Loop over the many tuples
	for (int i=0; i < relation->getTuples()->size(); i++)
	{
		Tuple* tuple = relation->getTuple(i);

		outFile << "INSERT INTO " << relationName << " VALUES FROM (";

		// Loop over each value in the tuple
		for (int x=0; x < tuple->getValues().size(); x++)
		{
			Attribute* attribute = relation->getAttribute(x);

			if(attribute->getType() == Attribute::VARCHAR)
			{
				outFile << "\"" << tuple->getValues()[x] << "\"";
			}
			else
			{
				outFile << tuple->getValues()[x];
			}

			if(x < tuple->getValues().size() - 1)
			{
				outFile << ", ";
			}
		}

		outFile << ");" << endl;
		
	}

	outFile.close();
}


/**
  * Print a relation to the screen
  */
void Engine::show(string relationName) 
{
	Relation* relation = getRelation(relationName);

	show(relation);
}

/**
  * Print a relation to the screen (when given a pointer to a relation)
  */
void Engine::show(Relation* relation) 
{
	cout << "===== SHOW Relation: " << relation->getName() << endl;

	// Loop over the many tuples
	for (int i=0; i < relation->getTuples()->size(); i++)
	{
		Tuple* tuple = relation->getTuple(i);

		// Loop over each value in the tuple
		for (int x=0; x < tuple->getValues().size(); x++)
		{
			Attribute* attribute = relation->getAttribute(x);

			if (attribute->isPrimary())
			{
				cout << "[KEY] ";
			}
			else
			{
				cout << "      ";
			}
			cout << attribute->getTypeName() << " " << attribute->getValue() << ": " << tuple->getValues()[x] << endl;
		}
		
		cout << endl;
	}
}

/**
  * Create a new relation and save it to the relations vector
  */
void Engine::create(string relationName, vector<Attribute> attributes) 
{
	Relation* relation = new Relation(relationName, attributes);

	relations.push_back(*relation);
}

/**
  * Insert a Tuple into the relation
  */
void Engine::insert(string relationName, Tuple tuple) 
{
	Relation* relation = getRelation(relationName);

	vector<string> values = tuple.getValues();

	// Ensure that the number of values and attributes is the same
	if(values.size() != relation->getAttributes()->size()) throw runtime_error("Number of values different from number of attributes");
	
	for(int i=0; i<values.size(); i++)
	{
		Attribute* attribute = relation->getAttribute(i);
		checkType(attribute, values[i]);
	}
	exprUnion(relation, relation);
	relation->addTuple(tuple);
}

/**
  * Take the relation name, a vector of pair<attributeID, newValue>, and a vector of the tupleIDs to update.
  */
void Engine::update(string relationName, vector<pair<int, string>> newValues, vector<int> tupleIDs) 
{
	Relation* relation = getRelation(relationName);

	// Check attribute/value pairs
	for ( int i=0; i<newValues.size(); i++)
	{
		Attribute* attribute = relation->getAttribute(newValues[i].first);
		string value = newValues[i].second;

		checkType(attribute, value);
	}

	// For each tupleID, set values
	for(int i=0; i < tupleIDs.size(); i++)
	{
		Tuple *tuple = relation->getTuple(tupleIDs[i]);
		vector<string> values = tuple->getValues();

		// For each <id, value> pair, update the tuple
		for(int y=0; y < newValues.size(); y++)
		{
			values[newValues[y].first] = newValues[y].second;
		}

		tuple->setValues(values);
	}
}

/**
  * Delete tuples based on given tupleIDs.
  */
void Engine::deleteTuples(string relationName, vector<int> tupleIDs) 
{
	Relation* relation = getRelation(relationName);

	// Sort tuples. If we delete the last index first, then other indexes are preserved
	sort(tupleIDs.rbegin(), tupleIDs.rend());

	vector<Tuple>* tuples = relation->getTuples();

	for(int i=tupleIDs.size()-1; i >= 0; i--)
	{
		tuples->erase(tuples->begin() + tupleIDs[i]);
	}
}

/**
  * Exit the engine
  */
void Engine::exit()
{
	throw runtime_error("Exiting program...");
}

/**
	* Search for a relation by name and return a pointer to the 
	* relation.
	*/
Relation *Engine::getRelation(string relationName)
{
	for (int i=0; i < relations.size(); i++)
	{
		if (relations[i].getName() == relationName) return &relations[i];

	}
	throw runtime_error("Relation '" + relationName + "' not found.");
}

/**
  * If the attribute is an integer, ensure we're inserting an integer
  */
void Engine::checkType(Attribute* attribute, string value)
{
	if(attribute->getType() == Attribute::INTEGER)
	{
		string::iterator iterator = value.begin();
		while(iterator != value.end())
		{
			if( ! isdigit(*iterator)) 
			{
				throw runtime_error("Trying to put a string into an INTEGER");
			}
			iterator++;
		}
	}
}

/**
  * Compute the union of two relations
  */
Relation Engine::exprUnion(Relation* a, Relation* b)
{
	// Ensure that the relations are union-compatible
	if ( ! isUnionCompatible(a,b))
	{
		throw runtime_error("Trying to take the union of non-union-compatible relations.");
	}

	// Union will be everything in a combined with everything in b not in a
	Relation unionRelation = *a;

	for(int i=0; i < b->getTuples()->size(); i++)
	{
		Tuple* tuple = b->getTuple(i);

		if( ! exists(&unionRelation, tuple))
		{
			unionRelation.addTuple(*tuple);
		} 
	}

	return unionRelation;
}

/**
  * Compute the difference of two relations
  */
Relation Engine::exprDifference(Relation* a, Relation* b)
{
	// Ensure that the relations are union-compatible
	if ( ! isUnionCompatible(a,b))
	{
		throw runtime_error("Trying to take the difference of non-union-compatible relations.");
	}

	// Difference will be everything in a that is not in b
	Relation differenceRelation = Relation();
	differenceRelation.setAttributes(*a->getAttributes());

	for(int i=0; i < a->getTuples()->size(); i++)
	{
		Tuple* tuple = a->getTuple(i);
		if( ! exists(b, tuple))
		{
			differenceRelation.addTuple(*tuple);
		} 
	}

	return differenceRelation;
}

/**
  * Compute the product of two relations
  */
Relation Engine::exprProduct(Relation* a, Relation* b)
{
	//Build the product relation
	Relation productRelation = Relation();

	vector<Attribute> attributes;

	// Rename attributes
	for(int i=0; i < a->getAttributes()->size(); i++)
	{
		Attribute attribute = *a->getAttribute(i);
		attribute.setValue(attribute.getValue());

		attributes.push_back(attribute);
	}

	for(int i=0; i < b->getAttributes()->size(); i++)
	{
		Attribute attribute = *b->getAttribute(i);
		attribute.setValue(attribute.getValue());

		attributes.push_back(attribute);
	}

	productRelation.setAttributes(attributes);

	//Build the product
	for(int i=0; i < b->getTuples()->size(); i++)
	{
		for(int y=0; y < a->getTuples()->size(); y++)
		{
			// For every tuple in b, combine each tuple in a
			vector<string> values = a->getTuple(y)->getValues();			
			vector<string> toAdd = b->getTuple(i)->getValues();

			// Build the values
			for(int i=0; i<toAdd.size(); i++)
			{
				values.push_back(toAdd[i]);
			}

			// Add the tuple to the product relation
			productRelation.addTuple(values);
		}
	}

	return productRelation;
}

/**
  * Rename the attributes in a relation
  */
Relation Engine::exprRenaming(Relation *a, vector<string> newAttributes)
{
	Relation renamedRelation = *a;	

	if(a->getAttributes()->size() != newAttributes.size()) throw runtime_error("Number of attributes renaming not correct.");

	 for(int i=0; i < renamedRelation.getAttributes()->size(); i++) 
        {
          Attribute *attribute = renamedRelation.getAttribute(i);
          attribute->setValue(newAttributes[i]);
        }

	return renamedRelation; 
}
	
/**
  * Select only certain rows from a relation.
  * 
  * The conditions for the select statement are computed in the parser.
  * A vector of tuple IDs where the ID is the tuple's position in the vector
  * is given to select the tuples.
  */
Relation Engine::exprSelect(Relation* a, vector<int> tupleIDs)
{
	Relation tempRelation = Relation();
	tempRelation.setAttributes(*a->getAttributes());

	for(int i=0; i < tupleIDs.size(); i++)
	{
		Tuple tuple = *a->getTuple(tupleIDs[i]);
		tempRelation.addTuple(tuple);
	}

	return tempRelation;
}

/**
  * Determine if two relations are union compatible
  */
bool Engine::isUnionCompatible(Relation* a, Relation* b)
{

	if(a->getAttributes()->size() != b->getAttributes()->size()) return false; // Fail on different sizes

	for (int i=0; i<a->getAttributes()->size(); i++)
	{
		if(a->getAttribute(i)->getType() 		!= b->getAttribute(i)->getType()) 	return false; // Fail on incorrect type
		if(a->getAttribute(i)->getValue()		!= b->getAttribute(i)->getValue()) 	return false; // Fail on different value
		if(a->getAttribute(i)->isPrimary() 	!= b->getAttribute(i)->isPrimary()) return false; // Fail on different primary value
	}

	return true;
}

/**
  * Determine if a tuple exists in a relation
  */
bool Engine::exists(Relation* haystack, Tuple* needle)
{
	//Iterate each tuple in haystack
	for(int i=0; i<haystack->getTuples()->size(); i++)
	{
		Tuple* check = haystack->getTuple(i);
		
		if(check->getValues() == needle->getValues()) return true;
	}
	return false;
}

/**
  * Select only certain attribute colums from a relation.
  */
Relation Engine::exprProject(Relation* a, vector<string> attributeName)
{
	Relation projectRelation = Relation();

	vector<Attribute> attributes;
	vector<int> attributeIDs;

	// Build a vector of attributes matching each element in attributeName
	for(int i=0; i<attributeName.size(); i++)
	{
		for(int j=0; j<a->getAttributes()->size(); j++)
		{
			Attribute attribute = *a->getAttribute(j);

			if(attributeName[i] == attribute.getValue())
			{
				attributes.push_back(attribute);
				attributeIDs.push_back(j);		
			}
		}
	}

	projectRelation.setAttributes(attributes);

	// Add each tuple to the new relation
	for(int i=0; i<a->getTuples()->size(); i++)
	{
		vector<string> oldValues = a->getTuple(i)->getValues();
		vector<string> newValues;

		for(int j=0; j<attributeIDs.size(); j++)
		{
			// From the old tuple, select each attribute and add it
			newValues.push_back(oldValues[attributeIDs[j]]);
		}

		projectRelation.addTuple(newValues);
	}
	return projectRelation;
}