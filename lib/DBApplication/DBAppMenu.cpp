#include "DBAppMenu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int menu = 0;
int submenu = 0;

void DBAppMenu::MainMenu(){
			cout << "<<<<< Main Menu >>>>> \n\n\n";
			cout << "Menu Options: \n"
				<<"1) Location table \n"
				<<"2) Sale table \n"
				<<"3) Employee table \n"
				<<"4) Role table \n"
				<<"5) Report functions \n"
				<<"9) Back / Previous Option \n"
				<<"99) EXIT \n";

			cin >> submenu;

			switch(submenu)
				{
					case 1: //loc
						menu = submenu;
						break;

					case 2: //sales
						menu = submenu;
						break;

					case 3: //employee
						menu = submenu;
						break;

					case 4: //role
						menu = submenu;
						break;

					case 5: //reports
						menu = submenu;
						break;
					
					case 9: //BACK
						menu = submenu;
						break;

					case 99: //EXIT
						break;	
				}
		}

void DBAppMenu::location()
{
	cout << "<<<<< Location Sub-Menu >>>>> \n\n\n";
	cout << "Menu Options: \n"
		<< "1)  Return to Main Menu \n"
		<< "2)  Sale Table \n"
		<< "3)  Employee Table \n"
		<< "4) Location View \n";

		cin >> submenu;

				switch(submenu)
				{
					case 1:	//main						
						break;

					case 2: //sale
					cout<<"Howdy Aggie\n";
						break;

					case 3: //emp
						break;

					case 4: //locView
						break;
				}
}

void DBAppMenu::sales(){		//sale
				//Link: 0,1,3,21,22,23, 9(back)
				cout << "<<<<< Sale Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "1)  Return to Main Menu \n"
						<< "2)  Location Table \n"
						<< "3)  Employee Table \n"
						<< "4) Sale - View \n"
						<< "5) Sale - Add Menu \n"
						<< "6) Sale - Edit Menu \n";

				cin >> submenu;

				switch(submenu)
				{
					case 1:	//return to MainMenu
						menu = submenu;
						break;

					case 2: //loc
						menu = submenu;
						break;

					case 3: //emp
						menu = submenu;
						break;

					case 4: //saleView
						menu = submenu;
						break;

					case 5: //saleAdd
						menu = submenu;
						break;

					case 6: //saleEdit
						menu = submenu;
						break;
				}
		}

void DBAppMenu::employee()
{
	cout << "<<<<< Employee Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "1)  Return to Main Menu \n"
						<< "2)  Location Table \n"
						<< "3)  Sale Table \n"
						<< "4) Location View \n";

				cin >> submenu;

				switch(submenu)
				{
					case 1:	//main
						break;

					case 2: //loc
						break;

					case 3: //sale
						break;

					case 4: //empView
						break;
				}
}

void DBAppMenu::role()
{
	cout << "<<<<< Role Sub-Menu >>>>> \n\n\n";
	cout << "Menu Options: \n"
			<< "1)  Return to Main Menu \n"
			<< "2) Role View \n";

	cin >> submenu;

	switch(submenu)
	{
		case 1:	//main	
			break;

		case 2: //roleView
			break;
	}
}

void DBAppMenu::reports()
{
		cout << "<<<<< Report Sub-Menu >>>>> \n\n\n";
		cout << "Menu Options: \n"
				<< "1)  Return to Main Menu \n"
				<< "2) Call Difference function \n"
				<< "3) Call Union function \n"
				<< "4) Call Product function \n"
				<< "5) Call Select function \n"
				<< "6) Call Project function \n";

				cin >> submenu;

				switch(submenu)
				{
					case 1:
							// return to MainMenu
						break;

					case 2:
						 	// '-' difference
						break;

					case 3:
						 	// '+' union
						break;

					case 4:	
							// '*' product
						break;

					case 5:	
							// select
						break;

					case 6:	
							// project
						break;

				}
}


int main(int argc, char const *argv[])
{

	while(true)
	{
		//call MainMenu at top of loop

		//MainMenu() receives input --> submenu / exit

		//Call appropriate submenu Location, Sales, Employee, Roles, Reports

		//submenus receive input --> commands sent to inteface / DBEngine

		//display return values from DBEngine

		//display submenu

	}

}
