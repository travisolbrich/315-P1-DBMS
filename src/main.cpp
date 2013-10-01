	using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"
#include "../lib/SqlTokenizer/Token.h"
#include "../lib/SqlParser/SqlParser.h"
#include "../lib/DBMSEngine/Relation.h"
#include "../lib/DBMSEngine/Engine.h"
#include "../lib/DBMS/DBMS.h"
#include "../lib/DBSeeder/Seeder.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
		// Create the engine. There are no relations to add to it yet
		DBMS* dbms = new DBMS();

		// Call the seeder
		Seeder* seeder = new Seeder(dbms);
		seeder->seed();


		while(true)
		{
			string query;
			cout << "sql> ";
			getline(cin,query,';');
			query = query + ";"; // The cin gets rid of the ;

			int status = dbms->execute(query);

			// Done
			if (status == 2) return 0;
		}
	
	return 0;

}

