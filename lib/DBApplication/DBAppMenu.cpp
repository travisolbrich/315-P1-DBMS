//#include "DBAppMenu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int menu = 0;
int submenu = 0;

int main(int argc, char const *argv[])
{
	while(true)
	{
		cout << "<<<<< Main Menu >>>>> \n\n\n";
		cout << "Menu Options: \n"
				<<"1) Location table \n"
				<<"2) Sale table \n"
				<<"3) Employee table \n"
				<<"4) Role table \n"
				<<"5) Report functions \n"
				<<"9) Back / Previous Option \n"
				<<"99) EXIT \n";

		cin >> menu;

		switch (menu)
		{
/*------------------------------------------------------------------------------*/
/* Main Menu Options (0-5, 9) */
/*------------------------------------------------------------------------------*/
			case 0:		//main menu
				//link: 1,2,3,4,5, 9(back)
				cout << "<<<<< Main Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<<"1)  Location table \n"
						<<"2)  Sale table \n"
						<<"3)  Employee table \n"
						<<"4)  Role table \n"
						<<"5)  Report functions \n"
						<<"9)  Back / Previous Option \n"
						<<"99) EXIT \n";

				cin >> menu;
				break;

			case 1:		//location
				//Link: 0,2,3,11, 9(back)
				cout << "<<<<< Location Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "0)  Return to Main Menu \n"
						<< "2)  Sale Table \n"
						<< "3)  Employee Table \n"
						<< "11) Location View \n";

				cin >> submenu;

				switch(submenu)
				{
					case 0:	//main
						menu = submenu;
						break;

					case 2: //sale
						menu = submenu;
						break;

					case 3: //emp
						menu = submenu;
						break;

					case 11: //locView
						menu = submenu;
						break;
				}

				break;

			case 2:		//sale
				//Link: 0,1,3,21,22,23, 9(back)
				cout << "<<<<< Sale Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "0)  Return to Main Menu \n"
						<< "1)  Location Table \n"
						<< "3)  Employee Table \n"
						<< "21) Sale - View \n"
						<< "22) Sale - Add Menu \n"
						<< "23) Sale - Edit Menu \n";


				cin >> submenu;

				switch(submenu)
				{
					case 0:	//main
						menu = submenu;
						break;

					case 1: //loc
						menu = submenu;
						break;

					case 3: //emp
						menu = submenu;
						break;

					case 21: //saleView
						menu = submenu;
						break;

					case 22: //saleAdd
						menu = submenu;
						break;

					case 23: //saleEdit
						menu = submenu;
						break;
				}

				break;

			case 3:		//employee
				//Link: 0,1,2,31, 9(back)
				cout << "<<<<< Employee Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "0)  Return to Main Menu \n"
						<< "1)  Location Table \n"
						<< "2)  Sale Table \n"
						<< "31) Location View \n";

				cin >> submenu;

				switch(submenu)
				{
					case 0:	//main
						menu = submenu;
						break;

					case 1: //loc
						menu = submenu;
						break;

					case 2: //sale
						menu = submenu;
						break;

					case 31: //empView
						menu = submenu;
						break;
				}

				break;

			case 4:		//role
				//Link: 0,41, 9(back)
				cout << "<<<<< Role Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "0)  Return to Main Menu \n"
						<< "41) Role View \n";

				cin >> submenu;

				switch(submenu)
				{
					case 0:	//main
						menu = submenu;
						break;

					case 41: //roleView
						menu = submenu;
						break;
				}

				break;

			case 5:		//report
				//Link: 9(back)
				//functions: '-', '+', '*', select, project, back, exit
				cout << "<<<<< Report Sub-Menu >>>>> \n\n\n";
				cout << "Menu Options: \n"
						<< "0)  Return to Main Menu \n"
						<< "54) Call Difference function \n"
						<< "55) Call Union function \n"
						<< "56) Call Product function \n"
						<< "57) Call Select function \n"
						<< "58) Call Project function \n";

				cin << submenu;

				switch(submenu)
				{
					case 0:
						menu = submenu;
						break;

					case 54: 	// '-' difference
						menu = submenu;
						break;

					case 55: 	// '+' union
						menu = submenu;
						break;

					case 56:	// '*' product
						menu = submenu;
						break;

					case 57:	// select
						menu = submenu;
						break;

					case 58:	// project
						menu = submenu;
						break;

				}

				break;

			case 9:		//back function
				//Back-step through stack
				//stack-1 : pop end of stack and reset menu to the new end()

			case 99:	//exit
				return false;
				break;

/*------------------------------------------------------------------------------*/
/* Sub-Menu Options (11, 21-23, 31, 41) */
/*------------------------------------------------------------------------------*/

			case 11:	//viewLoc
				//view: open, close, show, project, back, exit

			case 21:	//viewSale
				//view: open, close, show, project, back, exit

			case 22:	//addSale
				//add: write, createTable, update, back, exit

			case 23:	//editSale
				//edit: delete, insertInto, show, back, exit

			case 31:	//viewEmp
				//view: open, close, show, project, back, exit

			case 41: 	//viewRole
				//view: open, close, exit, show, project, back

/*------------------------------------------------------------------------------*/
/* Report functions */
/*------------------------------------------------------------------------------*/
			case 54: 	// '-' difference

			case 55: 	// '+' union

			case 56:	// '*' product

			case 57:	// select

			case 58:	// project

		}
	
	
	}	
}

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
						return false;
						break;	
				}

				break;
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

				break;
		}