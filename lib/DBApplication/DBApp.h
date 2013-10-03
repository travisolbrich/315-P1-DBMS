#ifndef DBApplication_Menu_H_
#define DBApplication_Menu_H_


#include "../DBMS/DBMS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//#include "../DBMSEngine/Engine.h"

using namespace std;

class DBApp
{
	private:
		DBMS* dbms;
		void locations();
		void employees();
		void sales();
		void viewSales();
		void deleteSales();
		void updateSales();
		void addSale();
		void viewIndividualSales();
		
	public: 
		DBApp(DBMS* _dbms) { dbms = _dbms; };

		void mainMenu();

};


#endif