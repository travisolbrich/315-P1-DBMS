using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
	string query = "SHOW <- TABLE <= <23< symbols_ev3rywhere\"Here's a <literal>\"3>\"cat\"\"dog\" >>= 443 ====";

	cout << "Query: " << query << "\n";

	SqlTokenizer* tokenzier = new SqlTokenizer(query);

	try 
	{
		tokenzier->split();
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}

