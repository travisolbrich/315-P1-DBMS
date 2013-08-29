using namespace std;

#include <iostream>

string query;
string::iterator it;

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
	query = "SHOW <- TABLE <= << >>= = ==";
	it = query.begin();

	cout << "Query: " << query << "\n";

	program();

	return 0;
}

void program() 
{
	while(it != query.end())
	{
		getSymbol();
	}
}

void getSymbol()
{
	string text;

	cout<< "getSymbol(" << *it << ")\n";

	// Skip past whitespace
	if(*it == ' ')
	{
		while(it != query.end() && *it == ' ')
		{
			it = it + 1;
		}
	}

	// If the current character is alpha, read until the letters stop
	else if(isalpha(*it))
	{
		while(it != query.end() && (isalpha(*it) || *it == '_'))
		{
			text += *it;
			it = it + 1;
		}
	}

	else if(*it == '<')
	{
		it += 1;

		if( *it == '-')
		{
			it += 1;
			text += "<-";
		}

		else if( *it == '=')
		{
			it += 1;
			text += "<=";
		}

		else
		{
			text += '<';
		}
	}

	else if (*it == '>')
	{
		it += 1;

		if ( *it == '=')
		{
			it += 1;
			text += ">=";
		}

		else
		{
			text += '>';
		}
	}

	else if (*it == '=')
	{
		it += 1;

		if ( *it == '=')
		{
			it += 1;
			text += "==";
		}

		else
		{
			cout << "Syntax Error";
		}
	}

	else if (*it == '!')
	{
		it += 1;

		if (*it == '=')
		{
			it += 1;
			text += "!=";
		}

		else
		{
			cout << "Syntax Error";
		}
	}

	else if (*it == '|')
	{
		it += 1;

		if(*it == '|')
		{
			it += 1;
			text += "||";
		}

		else 
		{
			cout << "Syntax Error";
		}
	}

	cout << "Symbol: " << text << "\n";
	return;
}