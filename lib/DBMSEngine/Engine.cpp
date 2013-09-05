#include "Engine.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>

using namespace std;
 
void Engine::create() 
{
}

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
	cout << "==== Relation: " << relation->getName() << endl;

	for (int i=0; i < relation->getTuples().size(); i++)
	{
		Tuple tuple = relation->getTuples()[i];

		for (int x=0; x < tuple.getValues().size(); x++)
		{
			Attribute attribute = relation->getAttributes()[x];

			cout << attribute.getTypeName() << " " << attribute.getValue() << ": " << tuple.getValues()[x] << endl;
		}

		cout << endl;
	}
}

void Engine::update() 
{
	//Do Me Eighth
	//changes existing entry
	//need error checking to ensure entry exists
	//be able to take input stream and rectify valid inputs. should be able to handle all primitives? ie. int's shouldn't be in a firstName block (unecessary?)
}

void Engine::insert() 
{
	//Do Me Seventh
	//inserts a NEW entry
	//need error checking to ensure entry does NOT yet exist

}

void Engine::deleteTuple() 
{
	//Do Me Nineth
	//removes an existing entry
	//need error checking to ensure entry exists
}

void Engine::exit (/* Pass 'exit_var' current state*/)
{
	//Do Me First
	//set 'exit_var=true' to exit the while loop in try block in Engine.cpp
	//we will need the state of exit_var for error checking (I think)
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