#include "DBApp.h"
#include "../DBMS/DBMS.h"
#include "../DBMSEngine/Relation.h"
#include "../DBMSEngine/Tuple.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int menu = 0;
int choice = 0;

void DBApp::mainMenu()
{
	cout << "<<<<< Main Menu >>>>> \n\n";
	cout << "Menu Options: \n"
		 << "1) View Locations \n"
		 << "2) View Employees \n"
		 << "3) Manage/View Sales \n"
		 << "0) EXIT (you may need to exit a few times) \n";

	cin >> choice;
	cout << endl;

	if(choice == 1) locations();
	if(choice == 2) employees();
	if(choice == 3) sales();	
}

void DBApp::locations()
{
	// Get the locations
	Relation locations = dbms->relation("locations");
	vector<Tuple> tuples = *locations.getTuples();

	cout << "Locations: " << endl;

	for(int i=0; i<tuples.size(); i++)
	{
		// Grab employees at this location
		dbms->execute("locationEmployees <- select (location_id == " + tuples[i].getValues()[0] + ") employees);");
		Relation employees = dbms->relation("locationEmployees");

		cout << tuples[i].getValues()[1] << ", " << tuples[i].getValues()[2] << " (" << employees.getTuples()->size() << " employees)" << endl;
	}

	cout << endl;
	mainMenu();
}

void DBApp::employees()
{
	dbms->execute("employeeLocationsReport <- (select (location_id == locationID) (employees * (rename (locationID, city, state) locations)));");
	dbms->execute("employees_places <- (rename (first, last, city, state, id) (project (first_name, last_name, city, state, id) employeeLocationsReport));");
	dbms->execute("employeeRoleName <- (project (employee_id, role_name) (select (role_id == roleID) (employee_role * (rename (roleID, role_name) roles))));");
	
	Relation employees = dbms->relation("employees_places");
	vector<Tuple> tuples = *employees.getTuples();

	Relation roles = dbms->relation("employeeRoleName");
	vector<Tuple> roleTuples = *roles.getTuples();

	// List employees
	cout << "Employees: " << endl;
	for(int i=0; i<tuples.size(); i++)
	{
		cout << tuples[i].getValues()[0] << " " << tuples[i].getValues()[1] << " (" << tuples[i].getValues()[2] << ", " << tuples[i].getValues()[3] << ")" << endl;
		
		// List their roles
		cout << "Roles: [ ";
		for(int j=0; j<roleTuples.size(); j++)
		{
			if(roleTuples[j].getValues()[0] == tuples[i].getValues()[4])
			{
				cout << roleTuples[j].getValues()[1] << " ";
			}
		}
		cout << "]" << endl << endl;
	}

	cout << endl;

	// List people who are not employees
	dbms->execute("notEmployees <- (select (role_name != \"Employee\") employeeRoleName);");
	dbms->execute("employeeRoleNameID <- (project (employee_id) employeeRoleName);");
	dbms->execute("notEmployeesID <- (project (employee_id) notEmployees);");
	
	dbms->execute("onlyEmployees <- (employeeRoleNameID - notEmployeesID);");
	dbms->execute("onlyEmployees <- (project (first_name, last_name) (select (id == employee_id) (onlyEmployees * employees)));");

	cout << "People who are only employees:" << endl;

	dbms->execute("SHOW onlyEmployees;");

	mainMenu();
}

void DBApp::sales()
{
	cout << "<<<<< Sales Menu >>>>> \n\n";
	cout << "Menu Options: \n"
		 << "1) View Sales \n"
		 << "2) Delete Sales \n"
		 << "3) Add Sales \n"
		 << "4) Update Sales \n"
		 << "5) View sales for certain locations only \n"
		 << "0) EXIT \n";

	cin >> choice;
	cout << endl;

	if(choice == 1) viewSales();
	if(choice == 2) deleteSales();
	if(choice == 3) addSale();
	if(choice == 4) updateSales();
	if(choice == 5) viewIndividualSales();
	
	mainMenu();
}

void DBApp::viewSales()
{
	dbms->execute("salesReport <- (project (id, client, city, state) (select (location_id == locationID) (sales * (rename (locationID, city, state) locations))));");
	dbms->execute("SHOW salesReport;");

	sales();
}

void DBApp::deleteSales()
{
	cout << endl << "Which sale to delete? (See sale IDs by using the View Sales option. Type -1 to stop)" << endl;

	while (choice != -1)
	{
		cout << "\nSale ID> ";
		cin  >> choice;

		if(choice != -1) dbms->execute("DELETE FROM sales WHERE (id == " + to_string(choice) + ");");
	}

	sales();
}

void DBApp::updateSales()
{
	cout << endl << "Which sale to update? {See sale IDs by using the View Sales option. Type -1 to quit)" << endl;
	
	cin >> choice;
	cout << endl;

	if(choice != -1)
	{
		dbms->execute("SHOW (select (id == " + to_string(choice) + ") sales);");

		cout << "Enter the new client and press enter" << endl;
		string client;
		cin.ignore();
		getline(cin,client);
		
		string query = "UPDATE sales SET client = \"" + client + "\" WHERE id == " + to_string(choice) + ";";
		cout << query;

		dbms->execute(query);
		dbms->execute("SHOW (select (id == " + to_string(choice) + ") sales);");
	}

	sales();
}

void DBApp::addSale()
{
	// Find the next free ID
	Relation sales = dbms->relation("sales");

	vector<Tuple> tuples = *sales.getTuples();

	int nextID = atoi(tuples[tuples.size() - 1].getValues()[0].c_str()) + 1;

	dbms->execute("SHOW locations;");

	cout << endl << "Location ID?" << endl;

	int locationID;
	cin >> locationID;

	cout << endl << "Client?" << endl;

	string client;
	cin.ignore();
	getline(cin, client);

	dbms->execute("INSERT INTO sales VALUES FROM (" + to_string(nextID) + ", " + to_string(locationID) + ", \"" + client + "\");");

	string 	query = "locationEmployees <- (select (location_id == " + to_string(locationID) + ") employees);";
	cout << query << endl;

	dbms->execute(query);
	dbms->execute("SHOW locationEmployees;");

	int employeeID;
	while(employeeID != -1)
	{
		cout << "Employee who was involved with sale (enter ID, or -1 if done)" << endl;
		cin >> employeeID;

		if(employeeID != -1) dbms->execute("INSERT INTO employee_sale VALUES FROM (" + to_string(employeeID) + ", " + to_string(nextID) + ");");
	}

	viewSales();
}

void DBApp::viewIndividualSales()
{	
	dbms->execute("SHOW locations;");

	cout << "Enter the location IDs for the sales you'd like to see. Press enter after each location, -1 to finish" << endl;

	int locationID;

	// Create empty sales
	dbms->execute("saleSelection <- (select (id == 0) sales);");
	dbms->execute("SHOW saleSelection;");

	while(locationID != -1)
	{
		cout << "Location ID > " << endl;
		cin >> locationID;

		if(locationID != -1) dbms->execute("saleSelection <- (saleSelection + (select (location_id == " + to_string(locationID) + ") sales));");
	}

	dbms->execute("SHOW saleSelection;");

	sales();
}