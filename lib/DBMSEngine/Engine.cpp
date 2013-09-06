#include "Engine.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;
 

void Engine::open() 
{
		throw runtime_error("File I/O is not yet implemented as the parser is incomplete.");
}

void Engine::close() 
{
	throw runtime_error("File I/O is not yet implemented as the parser is incomplete.");
}

void Engine::write() 
{
	throw runtime_error("File I/O is not yet implemented as the parser is incomplete.");
}

void Engine::show(string relationName) 
{
	Relation* relation = getRelation(relationName);

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

void Engine::create(string relationName, vector<Attribute> attributes) 
{
	Relation* relation = new Relation(relationName, attributes);

	relations.push_back(*relation);
}

void Engine::insert(string relationName, Tuple tuple) 
{
	Relation* relation = getRelation(relationName);

	vector<string> values = tuple.getValues();
	
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

void Engine::exit (/* Pass 'exit_var' current state*/)
{
	throw runtime_error("Goodbye, cruel world...");
}

/**
	* Search for a relation by name and return a reference to the 
	* relation.
	*/
Relation *Engine::getRelation(string relationName)
{
	for (int i=0; i < relations.size(); i++)
	{
		if (relations[i].getName() == relationName) return &relations[i];
	}

	throw runtime_error("Relation not found.");
}

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


Relation Engine::exprUnion(Relation* a, Relation* b)
{
	// Ensure that the relations are union-compatible
	if ( ! isUnionCompatible(a,b))
	{
		throw runtime_error("Trying to take the union of non-union-compatible relations.");
	}

	return Relation();
}

bool Engine::isUnionCompatible(Relation* a, Relation* b)
{
	if(a->getAttributes()->size() != b->getAttributes()->size())
	{
		return false;
	}

	for (int i=0; i<a->getAttributes()->size(); i++)
	{
		if(a->getAttribute(i)->getType() != b->getAttribute(i)->getType()) return false;
		if(a->getAttribute(i)->getValue() != b->getAttribute(i)->getValue()) return false;
		if(a->getAttribute(i)->isPrimary() != b->getAttribute(i)->isPrimary()) return false;
	}

	return true;
}