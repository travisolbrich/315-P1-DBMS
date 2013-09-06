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
	for (int i=0; i < relation->getTuples().size(); i++)
	{
		Tuple tuple = relation->getTuples()[i];

		// Loop over each value in the tuple
		for (int x=0; x < tuple.getValues().size(); x++)
		{
			Attribute attribute = relation->getAttributes()[x];

			if (attribute.isPrimary())
			{
				cout << "[KEY] ";
			}
			else
			{
				cout << "      ";
			}
			cout << attribute.getTypeName() << " " << attribute.getValue() << ": " << tuple.getValues()[x] << endl;
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
	relation->addTuple(tuple);
}

/**
  * Take the relation name, a vector of pair<attributeID, newValue>, and a vector of the tupleIDs to update.
  */
void Engine::update(string relationName, vector<pair<int, string>> newValues, vector<int> tupleIDs) 
{
	Relation* relation = getRelation(relationName);

	// Check integerID type
/*	attribute = relation->getAttribute(attributeID);
	if( attribute.getType() == Attribute::INTEGER)
	{
		for( int i=0; i<newValues.size(); i++ )
		{
			string attributeName = newValues[i].second;
			int Result;

			if(newValues[i].second == Attribute::STRING)
			{
				iterator = attributeName.begin();
				
				while(iterator != attributeName.end() && isdigit(*iterator))
				{
					iterator++;
					if(iterator == attributeName.size())
						return iterator;
				}

				if(iterator)
				{
					stringstream convert(attributeName);
				}
				else throw runtime_error("Attribute not an INTEGER");
			}

			else throw runtime_error("Attribute not a STRING");
		}
	}
	else throw runtime_error("Attribute improper type");
*/

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