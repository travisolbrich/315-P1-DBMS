	using namespace std;

#include <iostream>
#include "../lib/SqlTokenizer/SqlTokenizer.h"
#include "../lib/SqlTokenizer/Token.h"
#include "../lib/SqlParser/SqlParser.h"
#include "../lib/DBMSEngine/Relation.h"
#include "../lib/DBMSEngine/Engine.h"
#include "../lib/DBMS/DBMS.h"
#include "../lib/DBSeeder/Seeder.h"
#include "../lib/DBApplication/DBApp.h"

void program();
void getSymbol();

int main(int argc, char const *argv[])
{
	// Create the engine. There are no relations to add to it yet
	DBMS* dbms = new DBMS();

	// Call the seeder
	Seeder* seeder = new Seeder(dbms);
	seeder->seed();	

	// Call the app
	DBApp* app = new DBApp(dbms);
	app->mainMenu();

	// Write and close everything
	dbms->execute("WRITE locations;");
	dbms->execute("WRITE sales;");
	dbms->execute("WRITE employees;");
	dbms->execute("WRITE roles;");
	dbms->execute("WRITE employee_role;");	
	dbms->execute("WRITE employee_sale;");

	dbms->execute("CLOSE locations;");
	dbms->execute("CLOSE sales;");
	dbms->execute("CLOSE employees;");
	dbms->execute("CLOSE roles;");
	dbms->execute("CLOSE employee_role;");	
	dbms->execute("CLOSE employee_sale;");
	
	return 0;

}

