using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
	string query = "SHOW <- TABLE <= << symbols_everywhere >>= = ==";

	cout << "Query: " << query << "\n";

	SqlTokenizer* tokenzier = new SqlTokenizer(query);

	cout << tokenzier->getQuery();

	return 0;
}

