/*
 * TODO
 * LOGOUT : DO LIKE CLOSE THE CONSOLE AND RE-OPEN IT.
 */

#include "login.h"
#include "Source.cpp"

/* Default Lib */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include<cstdlib>
#include<cstring>
#include<conio.h>
/* Add_On Lib */
#include <string.h>
#include <windows.h>
#include "decoration.h"
#include "PromptBox.h"
	/* SQL LIB */
	#include <cppconn/driver.h>
	#include <cppconn/exception.h>
	#include <cppconn/resultset.h>
	#include <cppconn/statement.h>
	#include <cppconn/prepared_statement.h>
	/* Header File */
	#include "AdminController.h"
	#include "StaffController.h"
	#include "UserController.h"

using namespace std;



void login::loginController(sql::Connection *conn) {
	
	string usr, pwd;
	char masking;

		cout << endl;
		d.title();
		cout << "  " << "( L O G I N )" << endl;
		d.defaultCOLOR();
		cout << "  " << "------------------------------" << endl << endl;
		cout << "  " << "Username\t: " << flush;
		d.input();
		cin >> usr;
		cout << endl;
		d.defaultCOLOR();
		cout << "  " << "Password\t: " << flush;
		d.input();
		//cin >> pwd;
		for (int i = 0; i < 1000; i++)
		{
			masking = _getch();
			if (masking == '\r')
				break;
			std::cout << "*";
			pwd += masking;
		}
		d.defaultCOLOR();


		// NEW FEATURE

			//std::string a = "";
			//std::string b = "ABCD";
			//char c;
			
			//if (a == b)
				//std::cout << "Password Matched!!!";
			//else
				//std::cout << "Password Incorrect!!!";
	
		
		// NEW FEATURE

		multiLogin(usr, pwd, conn);
	
	
}

/* Define User Level and channel to correct Path */
bool login::multiLogin(string usr, string pwd, sql::Connection* conn) {

	bool found = 0;
	bool flagLogout = 0;

	/* Admin */
	sql::PreparedStatement* pstmtAdmin;
	sql::ResultSet* resAdmin;

	pstmtAdmin = conn->prepareStatement("Select * from admin where fullname = ? and password = ?");
	pstmtAdmin->setString(1, usr);
	pstmtAdmin->setString(2, pwd);
	resAdmin = pstmtAdmin->executeQuery();
	/* End of Admin */

	/* Staff */
	sql::PreparedStatement* pstmtStaff;
	sql::ResultSet* resStaff;

	pstmtStaff = conn->prepareStatement("Select * from staff where fullname = ? and password = ?");
	pstmtStaff->setString(1, usr);
	pstmtStaff->setString(2, pwd);
	resStaff = pstmtStaff->executeQuery();
	/* End of Staff */

	/* Users */
	sql::PreparedStatement* pstmtUser;
	sql::ResultSet* resUser;

	pstmtUser = conn->prepareStatement("Select * from users where fullname = ? and password = ?");
	pstmtUser->setString(1, usr);
	pstmtUser->setString(2, pwd);
	resUser = pstmtUser->executeQuery();
	/* End of Users */

	/* Analysis && Login Phase */
	if (resAdmin->next()) {
		d.adminCOLOR();
		int choice;
		flagLogout = 0;
		AdminController ac;
		// INFINTIE LOOP
		for (;;) {
			system("cls");

			string adminName = resAdmin->getString("fullname");
			int adminID = resAdmin->getInt(1);

			cout << endl;
			d.adminStatic();
			cout << "Welcome [ " << adminName << " ]" << endl;		
			cout << "@Admin\n" << endl;
			d.adminCOLOR();

			cout << "[1]\t Manage User " << endl;
			cout << "[2]\t Manage Staff " << endl;
			cout << "[3]\t Manage Complaint " << endl;
			cout << "[4]\t Generate Report" << endl;
			cout << "[5]\t Generate Graph" << endl;
			cout << "[6]\t Logout " << endl << endl;
			d.select();
			cout << "Enter your choice\t: " << flush;
			cin >> choice;
			d.adminCOLOR();

			if (cin.fail()) {

				cin.clear();
				cin.ignore();
				d.danger();
				system("cls");

			}


			system("cls");

			// Choice Path
			switch (choice)
			{

			case 1:
				int userC;
				cout << endl;
				d.adminStatic();
				cout << "Manage User" << endl;
				cout << "@Admin\n" << endl;
				d.adminCOLOR();
				cout << "[1]\t Add User " << endl;
				cout << "[2]\t Update User " << endl;
				cout << "[3]\t Delete User " << endl;
				cout << "[4]\t View User " << endl;
				cout << "[5]\t Back " << endl << endl;
				d.select();
				cout << "Enter your choice\t: " << flush;
				cin >> userC;
				d.adminCOLOR();

				if (cin.fail()) {

					cin.clear();
					cin.ignore();
					d.danger();
					system("cls");

				}

				system("cls");
				switch (userC)
				{
				case 1:
					ac.addUser(conn,adminName,adminID);
					Sleep(3000);
					break;

				case 2:
					//cout << "Update User" << endl;
					ac.updateUser(conn,adminName,adminID);
					Sleep(3000);
					break;

				case 3:
					//cout << "Delete User" << endl;
					ac.deleteUser(conn);
					Sleep(3000);
					break;

				case 4:
					//cout << "View User" << endl;
					ac.viewUser(conn);
					Sleep(3000);
					break;

				case 5:		
					Sleep(1000);
					break;

				default:

					cout << "Wrong option,  please retry";
					Sleep(3000);
				}

			break;

			case 2:
				int staffC;
				cout << endl;
				d.adminStatic();
				cout << "Manage Staff" << endl;
				cout << "@Admin\n" << endl;
				d.adminCOLOR();
				cout << "[1]\t Add Staff " << endl;
				cout << "[2]\t Update Staff " << endl;
				cout << "[3]\t Delete Staff " << endl;
				cout << "[4]\t View Staff " << endl;
				cout << "[5]\t Back " << endl << endl;
				d.select();
				cout << "Enter your choice\t: " << flush;
				cin >> staffC;
				d.adminCOLOR();
				system("cls");
				switch (staffC)
				{
				case 1:
					//cout << "Add Staff" << endl;
					ac.addStaff(conn,adminName,adminID);
					Sleep(3000);
					break;

				case 2:
					//cout << "Update Staff" << endl;
					ac.updateStaff(conn,adminName);
					Sleep(3000);
					break;

				case 3:
					//cout << "Delete Staff" << endl;
					ac.deleteStaff(conn);
					Sleep(3000);
					break;

				case 4:
					//cout << "View Staff" << endl;
					ac.viewStaff(conn);
					Sleep(3000);
					break;

				case 5:
					Sleep(1000);
					break;

				default:
					cout << "Wrong option,  please retry";
					Sleep(3000);
				}

			break;

			case 3:
				int complaintC;
				cout << endl;
				d.adminStatic();
				cout << "Manage Complaint" << endl;
				cout << "@Admin\n" << endl;
				d.adminCOLOR();
				cout << "[1]\t Add Place " << endl;
				cout << "[2]\t Update Place " << endl;
				cout << "[3]\t Delete Place" << endl;
				cout << "[4]\t Assign Complaint " << endl;
				cout << "[5]\t View Complaint " << endl;
				cout << "[6]\t Back " << endl << endl;
				d.select();
				cout << "Enter your choice\t: " << flush;
				cin >> complaintC;
				d.adminCOLOR();
				system("cls");
				switch (complaintC)
				{
				case 1:
					//cout << "Add Complaint" << endl;
					ac.addPlace(conn);
					Sleep(3000);
					break;

				case 2:
					//cout << "Update Complaint" << endl;
					ac.updatePlace(conn);
					Sleep(3000);
					break;

				case 3:
					//cout << "Delete Complaint" << endl;
					ac.deletePlace(conn);
					Sleep(3000);
					break;

				case 4:
					//cout << "View Complaint" << endl;
					ac.assignComplaint(conn);
					Sleep(3000);
					break;

				case 5:
					ac.viewComplaint(conn);
					Sleep(3000);
					break;

				case 6:
					exit(0);
					Sleep(3000);
					break;

				default:
					cout << "Wrong option,  please retry";
				}

			break;

			case 4:
				printPDF("DOCNEW8.pdf",conn);
				Sleep(3000);
				break;

			case 5:
				ac.displayGraph(conn);
				Sleep(3000);
				break;
			case 6: //exit(0);
				flagLogout = 1;
				break;
			
			default:
				
				cout << "Wrong Entry, Please re-try";
				Sleep(3000);
			}
			
			if (flagLogout == 1) {
				break;
			}
				
		}
		// End
	

		found = 1;
	}
	else if (resStaff->next()) {

	int choice;
	int selComp;
	int logout = 0;

	StaffController sc;
	for (;;) {
		system("cls");
		string staffName = resStaff->getString("fullname");

		cout << endl;
		d.adminStatic();
		cout << "Welcome [ " << staffName << " ]" << endl;
		cout << "@Staff\n" << endl;
		d.staffCOLOR();
		cout << "[1]\t Manage User " << endl;
		cout << "[2]\t Manage Complaint " << endl;
		cout << "[3]\t Logout " << endl << endl;
		d.select();
		cout << "Enter your choice\t: " << flush;
		cin >> choice;
		system("cls");

		// Choice Path
		switch (choice)
		{

		case 1:

			int userC;
			cout << endl;
			d.staffStatic();
			cout << "Manage User" << endl;
			cout << "@Staff\n" << endl;
			d.staffCOLOR();
			cout << "[1]\t Add User " << endl;
			cout << "[2]\t Update User " << endl;
			cout << "[3]\t Delete User " << endl;
			cout << "[4]\t Reset Password " << endl;
			cout << "[5]\t View User " << endl;
			cout << "[6]\t Back " << endl << endl;
			d.select();
			cout << "Enter your choice\t: " << flush;
			cin >> userC;
			d.staffCOLOR();
			system("cls");
			switch (userC)
			{
			case 1:
				//cout << "Add User" << endl;
				sc.addUser(conn, staffName);
				Sleep(3000);
				break;

			case 2:
				//cout << "Update User" << endl;
				sc.updateUser(conn, staffName);
				Sleep(3000);
				break;

			case 3:
				//cout << "Delete User" << endl;
				sc.deleteUser(conn);
				Sleep(3000);
				break;

			case 4:
				sc.resetPassword(conn);
				Sleep(3000);
				break;

			case 5:
				//cout << "View User" << endl;
				sc.viewUser(conn);
				Sleep(3000);
				break;

			case 6:
				//exit(0);
				Sleep(3000);
				break;

			default:
				cout << "Wrong option,  please retry";
			}

			break;

		case 2:
			int staffManageComplaint;

			cout << endl;
			d.staffStatic();
			cout << "Manage Complaint" << endl;
			cout << "@Staff\n" << endl;
			d.staffCOLOR();
			cout << "[1]\t Received Complaint " << endl;
			cout << "[2]\t Pending Complaint " << endl;
			cout << "[3]\t Solved Complaint" << endl;
			cout << "[4]\t Back " << endl << endl;
			d.select();
			cout << "Enter your choice\t: " << flush;
			cin >> staffManageComplaint;
			d.staffCOLOR();

			switch (staffManageComplaint)
			{
			case 1:
				sc.receivedComplaint(conn, staffName, resStaff->getInt(1));
				Sleep(3000);
				break;

			case 2:
				sc.pendingComplaint(conn, staffName, resStaff->getInt(1));
				Sleep(3000);
				break;

			case 3:
				sc.solvedComplaint(conn, staffName, resStaff->getInt(1));
				Sleep(3000);
				break;

			case 4:
				//exit(0);
				Sleep(3000);
				break;

			//case 5:
			//	cout << "TESTING FUNCTION" << endl;
			//Sleep(3000);

			//	system("cls");

			//	break;
			default:
				cout << "Wrong Input " << endl;
			}


			break;

		case 3: //exit(0);
			logout = 1;
			break;

		default:
			cout << "Wrong Entry, Please re-try";
		}
		
		if (logout == 1) {
			break;
		}
	}
		found = 1;
	}
	else if (resUser->next()) {

		string userName = resUser->getString(4);
		int userLogout = 0;

		for (;;) {

			UserController uc;
			system("cls");
			userLogout = uc.newUserUpdate(conn, userName);
			//system("pause");
			found = 1;
			if (userLogout == 1) {
				break;
			}
		}
	}
	else {
		system("cls");
		d.danger();
		PromptBox::unauthorized();
		Sleep(3000);
		system("cls");
		d.defaultCOLOR();
	}

	/* Deleting Data */
	delete pstmtAdmin;
	delete pstmtStaff;
	delete pstmtUser;
	delete resAdmin;
	delete resStaff;
	delete resUser;
	//conn->close();

	return found;
}

bool login::registerUser(sql::Connection* conn) {

	bool found = 0;
	
	/* Local Variable */
	string fullname, password, email, contact, department, address, state, country, pincode;
	string status = "USER";

	system("cls");
	d.title();
	cout << "   ( R E G I S T E R )\n" << endl;
	d.defaultCOLOR();
	cout << "   --------------------------------" << endl;

	cout << "   Fullname\t: " << flush;
	d.input();
	getline(cin.ignore(), fullname);
	d.defaultCOLOR();

	cout << "   Password\t: " << flush;
	d.input();
	getline(cin, password);
	d.defaultCOLOR();

	cout << "   Email\t: " << flush;
	d.input();
	getline(cin, email);
	d.defaultCOLOR();

	cout << "   Contact\t: " << flush;
	d.input();
	getline(cin,contact);
	d.defaultCOLOR();

	cout << "   Department\t: " << flush;
	d.input();
	getline(cin, department);
	d.defaultCOLOR();

	cout << "   Address\t: " << flush;
	d.input();
	getline(cin, address);
	d.defaultCOLOR();

	cout << "   State\t: " << flush;
	d.input();
	getline(cin, state);
	d.defaultCOLOR();

	cout << "   Country\t: " << flush;
	d.input();
	getline(cin, country);
	d.defaultCOLOR();

	cout << "   Pincode\t: " << flush;
	d.input();
	getline(cin, pincode);
	d.defaultCOLOR();

	cout << endl << endl;
	d.info();
	cout << "   Are you sure to register ? [ Y/N ]" << endl;
	d.select();

	
	
	string data;
	cout << "   Select\t: " << flush;
	cin >> data;

	// convert string to upper case
	for_each(data.begin(), data.end(), [](char& c) {
		c = ::toupper(c);
		});

	
	if (data == "Y") {

		/* Start Register New User */
		sql::PreparedStatement* pstmt;

		pstmt = conn->prepareStatement("Insert into users (fullname,password,email,contact,department,status,address,state,country,pincode) values (?,?,?,?,?,?,?,?,?,?) ");
		pstmt->setString(1, fullname);
		pstmt->setString(2, password);
		pstmt->setString(3, email);
		pstmt->setString(4, contact);
		pstmt->setString(5, department);
		pstmt->setString(6, status);
		pstmt->setString(7, address);
		pstmt->setString(8, state);
		pstmt->setString(9, country);
		pstmt->setString(10, pincode);

		found = pstmt->execute();
		delete pstmt;
		/* End Register New User */
		d.success();
		PromptBox::successRegister();
		d.defaultCOLOR();
	}
	else {
		d.danger();
		PromptBox::exiting();
		d.defaultCOLOR();
	}

	system("cls");
	
	return found;

}