#include "DBAppMenu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	while(cin)
	{
		switch (menu)
		{
			case 0:		//main menu
				//link: 1,2,3,4,5, 9(back)
				cout << "<<<<< Main Menu >>>>> /n/n/n";
				cout << "Menu Options: /n
						1) Location table /n
						2) Sale table
						3) Employee table /n
						4) Role table /n
						5) Report functions /n
						9) Back/previous option/n "

				break;

			case 1:		//location
				//Link: 0,2,3,11, 9(back)

				switch(submenu)
				{
					case 0:	//main

					case 2: //sale

					case 3: //emp

					case 11: //locView
				}

			case 2:		//sale
				//Link: 0,1,3,21,22,23, 9(back)
				switch(submenu)
				{
					case 0:	//main

					case 1: //loc

					case 3: //emp

					case 21: //saleView

					case 22: //saleAdd

					case 23: //saleEdit
				}

			case 3:		//employee
				//Link: 0,1,2,31, 9(back)
				switch(submenu)
				{
					case 0:	//main

					case 1: //loc

					case 2: //sale

					case 31: //empView
				}

			case 4:		//role
				//Link: 0,41, 9(back)
				switch(submenu)
				{
					case 0:	//main

					case 41: //roleView
				}

			case 5:		//report
				//Link: 9(back)
				//functions: '-', '+', '*', select, project, back, exit

			case 9:		//back function
				//Back-step through stack
				//stack-1

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
		}
	}	
}