#include "../DBMS/DBMS.h"
#include "Seeder.h"

#include <string>
#include <vector>


void Seeder::seed()
{	
	int result;

	// See if the locations file exists
	result = dbms->execute("OPEN locations;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE locations (id INTEGER, city VARCHAR(20), state VARCHAR(20)) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO locations VALUES FROM (1, \"College Station\", \"Texas\");");
		dbms->execute("INSERT INTO locations VALUES FROM (2, \"Bryan\", \"Texas\");");
		dbms->execute("INSERT INTO locations VALUES FROM (3, \"Houston\", \"Texas\");");
	}


	// See if the sale file exists
	result = dbms->execute("OPEN sales;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE sales (id INTEGER, location_id INTEGER, client VARCHAR(30)) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO sales VALUES FROM (1, 1, \"TAMU\");");
		dbms->execute("INSERT INTO sales VALUES FROM (2, 2, \"Blinn\");");
		dbms->execute("INSERT INTO sales VALUES FROM (3, 2, \"BISD\");");
	}

	// See if the employee file exists
	result = dbms->execute("OPEN employees;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE employees (id INTEGER, location_id INTEGER, first_name VARCHAR(30), last_name VARCHAR(30)) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO employees VALUES FROM (1, 1, \"Zalmon\", \"Xavier\");");
		dbms->execute("INSERT INTO employees VALUES FROM (2, 1, \"Walganus\", \"Parwiz\");");
		dbms->execute("INSERT INTO employees VALUES FROM (3, 1, \"Garrick\", \"Maddox\");");
		dbms->execute("INSERT INTO employees VALUES FROM (4, 2, \"Aubery\", \"Herman\");");
		dbms->execute("INSERT INTO employees VALUES FROM (5, 3, \"Rudolph\", \"Hardy\");");
		dbms->execute("INSERT INTO employees VALUES FROM (6, 3, \"Lesley\", \"Milton\");");
	}

	// See if the role file exists
	result = dbms->execute("OPEN roles;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE roles (id INTEGER, role_name VARCHAR(30)) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO roles VALUES FROM (1, \"Manager\");");
		dbms->execute("INSERT INTO roles VALUES FROM (2, \"Owner\");");
		dbms->execute("INSERT INTO roles VALUES FROM (3, \"Employee\");");
	}

	// See if the employee_role file exists
	result = dbms->execute("OPEN employee_role;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE employee_role (id INTEGER, employee_id INTEGER, role_id INTEGER) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (1, 1, 1);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (2, 1, 2);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (3, 2, 3);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (4, 3, 3);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (5, 4, 1);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (6, 4, 2);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (1, 4, 3);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (2, 5, 1);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (3, 5, 2);");
		dbms->execute("INSERT INTO employee_role VALUES FROM (1, 6, 3);");
	}

	// See if the employee_sale file exists
	result = dbms->execute("OPEN employee_sale;");

	if(result == 1)
	{
		// Create location table
		dbms->execute("CREATE TABLE employee_sale (employee_id INTEGER, sale_id INTEGER) PRIMARY KEY (id);");
		dbms->execute("INSERT INTO employee_sale VALUES FROM (1, 1);");
		dbms->execute("INSERT INTO employee_sale VALUES FROM (3, 1);");
		dbms->execute("INSERT INTO employee_sale VALUES FROM (4, 2);");
		dbms->execute("INSERT INTO employee_sale VALUES FROM (4, 3);");
	}
}