#include "UserController.h"
#include "StaffController.h"
#include "AdminController.h"

/* Default Lib */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* Add_On Lib */
#include <string>
#include <Windows.h>
#include <iomanip>
#include <typeinfo>
#include "PromptBox.h"
#include "TextTable.h"
	/* SQL LIB */
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int UserController::newUserUpdate(sql::Connection* conn, string userName) {

	int logout = 0;
	
	try {

		int sel;

		/* Finding Default Password */
		string defPwd = "abc123";
		
		sql::PreparedStatement* pstmtPWD;
		sql::ResultSet* resPWD;
		string pwdSQL = "Select UID, password from users where fullname = ?";

		pstmtPWD = conn->prepareStatement(pwdSQL);
		pstmtPWD->setString(1, userName);
		resPWD = pstmtPWD->executeQuery();
		int userID = 0;
		string foundUserPwd;

		if (resPWD->next()) {
			userID = resPWD->getInt(1);
			foundUserPwd = resPWD->getString(2);
		}
	
	/* End Finding Default Password */


	/* OUTPUT */
	d.userStatic();
	cout << "Welcome [ " << userName << " ]" << endl;
	cout << "@User" << endl << endl;
	d.userCOLOR();

	if (defPwd == foundUserPwd) {

		string newPwd;
		string comfPwd;

		d.userInput();
		cout << "Please update Password" << endl << endl;

		cout << "Password\t\t: " << flush;
		//getline(cin.ignore(), newPwd);
		cin >> newPwd;

		cout << "Comfirm Password\t: " << flush;
		//getline(cin.ignore(), comfPwd);
		cin >> comfPwd;
		d.userStatic();

		if (newPwd == comfPwd) {

			string address, state, country, pincode;
			system("cls");
			cout << "Welcome [ " << userName << " ]" << endl;
			cout << "@User" << endl << endl;

			d.userInput();
			cout << "Please update Details" << endl << endl;

			cout << "Address\t\t : " << flush;
			getline(cin.ignore(), address);

			cout << "State\t\t : " << flush;
			getline(cin, state);

			cout << "Country\t\t : " << flush;
			getline(cin, country);

			cout << "Pin Code\t : " << flush;
			getline(cin, pincode);

			string sqlExecute = "Update users set password = ?,address = ?,state = ?,country = ?,pincode = ? where UID = ?";
			sql::PreparedStatement* pstmtUpNewData;
			pstmtUpNewData = conn->prepareStatement(sqlExecute);
			pstmtUpNewData->setString(1, newPwd);
			pstmtUpNewData->setString(2, address);
			pstmtUpNewData->setString(3, state);
			pstmtUpNewData->setString(4, country);
			pstmtUpNewData->setString(5, pincode);
			pstmtUpNewData->setInt(6, userID);
			pstmtUpNewData->executeUpdate();

			delete pstmtUpNewData;
			system("cls");
			d.userCOLOR();
		}
		else {
			d.danger();
			cout << "Password Not Match" << endl;
		}

	}

	system("cls");
	d.userStatic();
	cout << "Welcome [ " << userName << " ]" << endl;
	cout << "@User" << endl << endl;
	d.userCOLOR();

	cout << "[1]\t Make Complaint " << endl;
	cout << "[2]\t View Status " << endl;
	cout << "[3]\t Account Setting " << endl;
	cout << "[4]\t Logout " << endl << endl;

	d.select();
	cout << "Enter your choice\t: " << flush;
	cin >> sel;
	system("cls");
	d.userCOLOR();

	switch (sel)
	{
	case 1:
		
		d.userStatic();
		cout << "Make Complaint" << endl;
		cout << "@User\n" << endl;

		/* Import Function */

		makeComplaint(conn, userName);
		/* End Importing */
		Sleep(3000);
		break;

	case 2:
		viewMyStatus(conn, userName);
		cout << endl;
		system("pause");
		Sleep(3000);
		break;

	case 3:
		int as;

		d.userStatic();
		cout << "Account Setting" << endl;
		cout << "@User" << endl << endl;
		d.userCOLOR();

		cout << "[1]\tView Profile" << endl;
		cout << "[2]\tUpdate Profile" << endl;
		cout << "[3]\tChange Password" << endl << endl;
		d.select();
		cout << "Select\t: " << flush;
		cin >> as;
		d.userCOLOR();
		system("cls");

		switch (as)
		{
		case 1:
			viewProfile(conn, userName);
			Sleep(3000);
			system("pause");
			break;
		case 2:
			updateProfile(conn, userName);
			Sleep(3000);
			break;
		case 3:
			system("cls");
			changePassword(conn, userName);
			Sleep(3000);
			break;
		default:
			cout << "Wrong Input " << endl;
		}

		
		break;

	case 4:
		//cout << "Logout " << endl;
		Sleep(3000);
		//exit(0);
		logout = 1;
		break;

	default:
		cout << "Wrong Input" << endl;
	}



	/* Deleting Data */
	delete pstmtPWD;
	delete resPWD;


	}
	catch (sql::SQLException & e1) {

		/* Declaration of the Error */
		cout << "USER CONTROLLER" << endl;		cout << "# ERR: SQLException in " << __FILE__;

		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << " ERR : " << e1.what();
		cout << " (MySQL error code : " << e1.getErrorCode();
		cout << ", SQLState : " << e1.getSQLState() << " )" << endl;
	}

	return logout;
}

void UserController::testLogin(sql::Connection* conn, string userName) {

	cout << "Can access lah bro " << endl;
}

void UserController::makeComplaint(sql::Connection* conn, string userName) {

	string model, noSerial, detalis;
	string respond = "NOT PROCESS";
	int selPlace;

	sql::PreparedStatement* pstmtfindUser;
	sql::ResultSet* resfindUser;
	string findUserSQL = "Select UID from users where fullname = ?";
	pstmtfindUser = conn->prepareStatement(findUserSQL);
	pstmtfindUser->setString(1, userName);
	resfindUser = pstmtfindUser->executeQuery();
	int userID = 0;
	if (resfindUser->next()) {

		userID = resfindUser->getInt(1);
	}


	/* SYSTEM OUTPUT */
	//system("COLOR 0A");
	//system("cls");
	d.userCOLOR();
	cout << "Model\t\t\t: " << flush;
	d.userInput();
	getline(cin.ignore(), model);

	d.userCOLOR();
	cout << "Serial Number\t\t: "<< flush;
	d.userInput();
	getline(cin, noSerial);

	d.userCOLOR();
	cout << "Detalis\t\t\t: "<< flush;
	d.userInput();
	getline(cin, detalis);

	system("cls");

	d.userCOLOR();
	cout << "\nWhere is it ? " << endl;

	// Try to create a function on this [ Later Updates ]

	/* List Out Place */
	sql::PreparedStatement* pstmtListPlace;
	sql::ResultSet* resListPlace;
	string listPlace = "Select PlaceID,Lab from place";

	pstmtListPlace = conn->prepareStatement(listPlace);
	resListPlace = pstmtListPlace->executeQuery();

	cout << "\n-------------------------------------------------------------------------------" << endl;
	d.userTableHeader();
	cout << setw(15) << "ID" << setw(15) << "Lab" << endl;
	d.userCOLOR();
	cout << "-------------------------------------------------------------------------------" << endl;

	d.userTableData();
	while (resListPlace->next()) {

		cout << setw(15) << resListPlace->getInt(1) << setw(15) << resListPlace->getString(2) << endl;
	}
	d.userCOLOR();
	cout << "-------------------------------------------------------------------------------\n" << endl;
	cout << endl;

	d.select();
	cout << "Select Place\t: " << flush;
	cin >> selPlace;

	/* Sending Data to Database */
	sql::PreparedStatement* pstmtUpComp;
	string upCompSQL = "Insert into complaint(UID,PlaceID,model,noSerial,details,respond) values (?,?,?,?,?,?)";

	pstmtUpComp = conn->prepareStatement(upCompSQL);
	pstmtUpComp->setInt(1,userID);
	pstmtUpComp->setInt(2,selPlace);
	pstmtUpComp->setString(3,model);
	pstmtUpComp->setString(4,noSerial);
	pstmtUpComp->setString(5,detalis);
	pstmtUpComp->setString(6,respond);
	pstmtUpComp->execute();
	/* End of Sending Data to Database */

	system("cls");
	d.success();
	cout << "Successfully Made Complaint" << endl;
	d.userCOLOR();
	
}

void UserController::viewMyStatus(sql::Connection* conn, string userName) {


	sql::PreparedStatement* pstmtfindUser;
	sql::ResultSet* resfindUser;
	string findUserSQL = "Select UID from users where fullname = ?";
	pstmtfindUser = conn->prepareStatement(findUserSQL);
	pstmtfindUser->setString(1, userName);
	resfindUser = pstmtfindUser->executeQuery();
	int userID = 0;
	if (resfindUser->next()) {

		userID = resfindUser->getInt(1);
	}


	sql::PreparedStatement* pstmtVStatus;
	sql::ResultSet* resVStatus;
	string viewStatusSQL = "Select * from complaint where UID=?";
	pstmtVStatus = conn->prepareStatement(viewStatusSQL);
	pstmtVStatus->setInt(1, userID);
	resVStatus = pstmtVStatus->executeQuery();


	/* OUTPUT */
	d.userStatic();
	cout << "View Status" << endl;
	cout << "@User" << endl << endl;
	d.userCOLOR();

	cout << "Complainted Data" << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	d.userTableHeader();
	cout << "ID" << setw(20) << "Model" << setw(20) << "Serial Number" << setw(20) << "Status" << setw(25) << "Date" << endl;
	d.userCOLOR();
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	d.userTableData();

	while (resVStatus->next())
	{
		cout << resVStatus->getInt(1) << setw(20) << resVStatus->getString(5) << setw(20) << resVStatus->getString(6) << setw(20) << resVStatus->getString(8) << setw(25) << resVStatus->getString(9) << endl;

	}
	d.userCOLOR();
	cout << "---------------------------------------------------------------------------------------------------\n\n" << endl;
}

void UserController::viewProfile(sql::Connection* conn, string userName) {

	sql::PreparedStatement* pstmtVUser;
	sql::ResultSet* resVUser;
	string viewDUserSQL = "Select * from users where fullname = ?";

	pstmtVUser = conn->prepareStatement(viewDUserSQL);
	pstmtVUser->setString(1, userName);
	resVUser = pstmtVUser->executeQuery();

	/* OUTPUT */
	d.userStatic();
	cout << "View Profile" << endl;
	cout << "@User" << endl << endl;
	d.userCOLOR();
	cout << "----------------------------------------------------------------" << endl;

	d.userTableData();
	if (resVUser->next()) {

		cout << "Full name\t\t: " << resVUser->getString(4) << endl;
		cout << "Email\t\t\t: " << resVUser->getString(6) << endl;
		cout << "Contact\t\t\t: " << resVUser->getString(7) << endl;
		cout << "Department\t\t: " << resVUser->getString(8) << endl;
		cout << "Address\t\t\t: " << resVUser->getString(10) << endl;
		cout << "State\t\t\t: " << resVUser->getString(11) << endl;
		cout << "Country\t\t\t: " << resVUser->getString(12) << endl;
		cout << "Pin code\t\t: " << resVUser->getString(12) << endl;

	}
	d.userCOLOR();
	cout << "----------------------------------------------------------------\n\n" << endl;
	delete pstmtVUser;
	delete resVUser;

}

void UserController::updateProfile(sql::Connection* conn, string userName) {

	sql::PreparedStatement* pstmt;

	// Local Variable
	int uID;
	int sel;

	string fullname;
	string password;
	string email;
	string contact;
	string department;
	string status;
	string address;
	string state;
	string country;
	string pincode;

	sql::PreparedStatement* pstmtfindUser;
	sql::ResultSet* resfindUser;
	string findUserSQL = "Select UID from users where fullname = ?";
	pstmtfindUser = conn->prepareStatement(findUserSQL);
	pstmtfindUser->setString(1, userName);
	resfindUser = pstmtfindUser->executeQuery();
	int userID = 0;
	if (resfindUser->next()) {

		userID = resfindUser->getInt(1);
	}


	/* Selection */
	sql::PreparedStatement* pstmtUser1;
	sql::ResultSet* resUser1;

	pstmtUser1 = conn->prepareStatement("Select * from users where UID = ?");
	pstmtUser1->setInt(1, userID);
	resUser1 = pstmtUser1->executeQuery();


	if (resUser1->next()) {

		system("cls");
		d.userStatic();
		cout << "\nView Profile" << endl;
		cout << "@User\n" << endl;
		d.userCOLOR();

		cout << " Existing " << resUser1->getString("fullname") << " Data" << endl;
		cout << "------------------------------------------------------" << endl;

		d.userTableData();
		cout << "[1]\tEmail\t\t: " << resUser1->getString("email") << endl;
		cout << "[2]\tContact\t\t: " << resUser1->getString("contact") << endl;
		cout << "[3]\tDepartment\t: " << resUser1->getString("department") << endl;
		cout << "[4]\tAddress\t\t: " << resUser1->getString("address") << endl;
		cout << "[5]\tState\t\t: " << resUser1->getString("state") << endl;
		cout << "[6]\tCountry\t\t: " << resUser1->getString("country") << endl;
		cout << "[7]\tPincode\t\t: " << resUser1->getString("pincode") << endl;
		cout << "[8]\tChange All" << endl;
		cout << "[9]\tExit without Change " << endl;
		d.userCOLOR();
		cout << "------------------------------------------------------\n" << endl;

		d.select();
		cout << "Select\t: " << flush;
		cin >> sel;
		cout << endl << endl;


		d.userCOLOR();
		switch (sel)
		{
		case 1:
			cout << "Email\t\t: " << flush;
			d.userInput();
			cin >> email;
			pstmt = conn->prepareStatement("update users set email = ? where UID = ?");
			pstmt->setString(1, email);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 2:
			cout << "Contact\t\t: " << flush;
			d.userInput();
			cin >> contact;
			pstmt = conn->prepareStatement("update users set contact = ? where UID = ?");
			pstmt->setString(1, contact);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 3:
			cout << "Department\t: " << flush;
			d.userInput();
			cin >> department;
			pstmt = conn->prepareStatement("update users set department = ? where UID = ?");
			pstmt->setString(1, department);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 4:
			cout << "Address\t\t: " << flush;
			d.userInput();
			getline(cin.ignore(), address);
			pstmt = conn->prepareStatement("update users set address = ? where UID = ?");
			pstmt->setString(1, address);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 5:
			cout << "State\t\t: " << flush;
			d.userInput();
			cin >> state;
			pstmt = conn->prepareStatement("update users set state = ? where UID = ?");
			pstmt->setString(1, state);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 6:
			cout << "Country\t\t: " << flush;
			d.userInput();
			cin >> country;
			pstmt = conn->prepareStatement("update users set country = ? where UID = ?");
			pstmt->setString(1, country);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 7:
			cout << "Pincode\t\t: " << flush;
			d.userInput();
			cin >> pincode;
			pstmt = conn->prepareStatement("update users set pincode = ? where UID = ?");
			pstmt->setString(1, pincode);
			pstmt->setInt(2, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 8:
			d.userCOLOR();
			cout << "Email\t\t: " << flush;
			d.userInput();
			cin >> email;
			d.userCOLOR();
			cout << "Contact\t\t: " << flush;
			d.userInput();
			cin >> contact;
			d.userCOLOR();
			cout << "Department\t: " << flush;
			d.userInput();
			cin >> department;
			d.userCOLOR();
			cout << "Address\t\t: " << flush;
			d.userInput();
			cin >> address;
			d.userCOLOR();
			cout << "State\t\t: " << flush;
			d.userInput();
			cin >> state;
			d.userCOLOR();
			cout << "Country\t\t: " << flush;
			d.userInput();
			cin >> country;
			d.userCOLOR();
			cout << "Pincode\t\t: " << flush;
			d.userInput();
			cin >> pincode;
			d.userCOLOR();

			pstmt = conn->prepareStatement("update users set email = ?,contact = ?,department = ?,address = ?,state = ?,country = ?,pincode = ? where UID = ?");

			pstmt->setString(1, email);
			pstmt->setString(2, contact);
			pstmt->setString(3, department);
			pstmt->setString(4, address);
			pstmt->setString(5, state);
			pstmt->setString(6, country);
			pstmt->setString(7, pincode);
			pstmt->setInt(8, userID);
			pstmt->executeUpdate();
			delete pstmt;
			break;
		case 9:
			d.danger();
			PromptBox::taskAbort();
			break;
		default:
			cout << "Wrong Input" << endl;
		}
	}
	d.userCOLOR();
	delete pstmtUser1;
	delete resUser1;
}

void UserController::changePassword(sql::Connection* conn, string userName) {

	string oldPwd;
	string newPwd;
	string comfPwd;


	sql::PreparedStatement* pstmtfindUser;
	sql::ResultSet* resfindUser;
	string findUserSQL = "Select UID,password from users where fullname = ?";
	pstmtfindUser = conn->prepareStatement(findUserSQL);
	pstmtfindUser->setString(1, userName);
	resfindUser = pstmtfindUser->executeQuery();
	int userID = 0;
	string oripwd;
	if (resfindUser->next()) {

		userID = resfindUser->getInt(1);
		oripwd = resfindUser->getString(2);
	}

	/* Output */

	d.userStatic();
	cout << "View Profile" << endl;
	cout << "@User" << endl << endl;
	d.userCOLOR();

	cout << "Old Password\t\t: " << flush;
	d.userInput();
	cin >> oldPwd;
	d.userCOLOR();

	if (oripwd == oldPwd) {

		cout << "New Password\t\t: " << flush;
		d.userInput();
		cin >> newPwd;

		d.userCOLOR();
		cout << "Confirm Password\t: " << flush;
		d.userInput();
		cin >> comfPwd;
		d.userCOLOR();

		if (newPwd == comfPwd) {

			sql::PreparedStatement* pstmtPWD;
			string chaPwdSQL = "update users set password = ? where UID = ? ";
			pstmtPWD = conn->prepareStatement(chaPwdSQL);
			pstmtPWD->setString(1, newPwd);
			pstmtPWD->setInt(2, userID);
			pstmtPWD->execute();

			d.success();
			cout << "\nChanged " << endl;
			delete pstmtPWD;
			Sleep(3000);
		}
		else {

			d.danger();
			cout << "Not Same" << endl;
			Sleep(3000);
		}
	}
	else {

		d.danger();
		cout << "Invaild Password" << endl;
		Sleep(3000);
	}

	d.userCOLOR();


}

