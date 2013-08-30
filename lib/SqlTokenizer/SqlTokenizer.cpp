using namespace std;

#include "SqlTokenizer.h"
#include "InvalidSymbolException.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void SqlTokenizer::split()
{
	iterator = query.begin();

	while( iterator != query.end())
	{
		// Ignore whitespace
		if( *iterator == ' ')
		{
			iterator++;
		}

		// Grab words (allow underscores)
		else if (isalpha(*iterator))
		{
			string text;
			while(iterator != query.end() && (isalpha(*iterator) || *iterator == '_'))
			{
				text += *iterator;
				iterator++;
			}

			cout<<"Text: "<<text<<'\n';
		}

		// Grab numbers
		else if (isdigit(*iterator))
		{
			string numberstring;

			while(iterator != query.end() && isdigit(*iterator))
			{
				numberstring += *iterator;
				iterator++;
			}

			// Convert string to number
			int number;
			istringstream(numberstring) >> number;

			cout<<"Number: "<<number<<"\n";
		}

		// Try to match two-character symbols
		else if (count(doubleSymbols, doubleSymbols+7, readAhead(2)))
		{
			cout<<"Symbol: "<<readAhead(2)<<"\n";
			iterator+=2;
		}

		// Try to match single-character symbols
		else if (count(singleSymbols, singleSymbols+7, readAhead(1)))
		{
			cout<<"Symbol: "<<readAhead(1)<<"\n";
			iterator++;
		}

		// Literals
		else if (*iterator == '"')
		{
			string text;
			iterator++;
			while(iterator != query.end() && *iterator != '"')
			{
				text += *iterator;
				iterator++;
			}

			// This character should be a '"'. If not, then it's the end of the string.
			// and we should throw an exception
			if(*iterator != '"')
			{
				throw InvalidSymbolException;
			}
			else
			{
				iterator++;
			}

			cout<<"Literal: "<<text<<'\n';
		}
		
		else
		{
			throw InvalidSymbolException;
			cout<< "Error: "<<*iterator<<"\n";
			iterator++;
		}
	}
}

/**
  * Get the next n characters without advancing the iterator. Reads unitl
  * the distance is reached or until the string ends.
  */
string SqlTokenizer::readAhead(int distance)
{
	stringstream stream;
	string::iterator it = iterator;
	
	for (int i = 0; i < distance; i++)
	{
		stream << *it;
		
		if(it == query.end())
		{
			return stream.str();
		}

		it++;
	}

	return stream.str();
}