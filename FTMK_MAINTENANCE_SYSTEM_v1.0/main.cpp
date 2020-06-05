/* Default Lib */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* Add-On Lib */
#include <Windows.h>
#include <ctime>
#include <string.h>
#include <cstdlib>
#include <limits>
#include <iomanip>

	/* SQL LIB */
	#include <cppconn/driver.h>
	#include <cppconn/exception.h>
	#include <cppconn/resultset.h>
	#include <cppconn/statement.h>
	#include <cppconn/prepared_statement.h>
	/* Header File */
	#include "login.h"
	#include "AdminController.h"
	#include "decoration.h"

using namespace std; // Default 
using namespace sql; // SQL Purpose

/* S Q L  Global Variable */
Driver* driver;
Connection* conn;

/* Project Core */
int main() {

	try{

		/* Create a Connection */
		driver = get_driver_instance();
		conn = driver->connect("tcp://127.0.0.1:3306", "root", "");

		/* Connect to the MySQL database */
		conn->setSchema("db_ftmk_maintenance");

		/* System Run */

		// Local Variable
		int key;
		login login1;
		AdminController admin;
		decoration d;

		d.bannerMontage();
		system("COLOR 0F");
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

		// Infinite For Loop
		for (;;) {
		
				cout << endl << endl;
				d.title();

				cout << "( Welcome to FTMK Maintenance System )" << endl;
				d.defaultCOLOR();

				cout << "--------------------------------------" << endl;
				cout << "|\t\t\t\t     |" << endl;
				cout << "|\t" << "      [1] Login" << "\t\t     |" << endl;
				cout << "|\t" << "      [2] Register" << "\t     |" << endl;
				cout << "|\t" << "      [3] Exit" << "\t\t     |" << endl;
				cout << "|\t\t\t\t     |" << endl;
				cout << "--------------------------------------" << endl << endl << endl;

				d.select();
				cout << "Select any option\t: " << flush;
				cin >> key;

				// Error Handling for the input [key] 
				if (cin.fail()) {

					cin.clear();
					cin.ignore();
					d.danger();
					system("cls");
					
				}

			Beep(600, 500);
			SetConsoleTextAttribute(color, 15);

			// Navigation 
			switch (key)
			{
			case 1:
				system("cls");			
				login1.loginController(conn);
				break;
			case 2:
				login1.registerUser(conn);
				break;
			case 3:
				exit(0);
				break;
			case 4:
				cout << "Color Test" << endl;
				d.userCOLOR();
				cout << "User Default" << endl;
				d.userInput();
				cout << "User Input" << endl;
				d.userStatic();
				cout << "User Static" << endl;
				d.userTableData();
				cout << "User Table Data" << endl;
				d.userTableHeader();
				cout << "User Table Header" << endl;
				d.userCOLOR();
				printf("Binary build date: %s @ %s\n", __DATE__,__TIME__);
				cout << "\n\n" << __DATE__ << " TESTING" << __TIME__ << endl;
				break;
			default:
				d.danger();
				cout << endl;
				cout << "Wrong Input, Retry";
				Sleep(3000);
				system("cls");
			}
		}

	}
	catch (SQLException & e) {

		/* Declaration of the Error */
		decoration d;
		d.danger();
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << " ERR : " << e.what();
		cout << " (MySQL error code : " << e.getErrorCode();
		cout << ", SQLState : " << e.getSQLState() << " )" << endl;
		Sleep(5000);
		system("cls");
		if (e.getErrorCode() == 2003) {

			cout << "\nPlease Turn On your XAMPP Server\n" << endl;
			cout << "Step 1 : Turn On your XAMMP Server" << endl;
			cout << "Step 2 : Click Start Button on Apache and MySQL" << endl;
			cout << "Step 3 : Run the file again" << endl;
		}
		else if (e.getErrorCode() == 1049) {

			cout << "\nDatabase not found" << endl;
		}
		else {

		}

		cout << endl;
		cout << endl;
	}

	return 0;
}