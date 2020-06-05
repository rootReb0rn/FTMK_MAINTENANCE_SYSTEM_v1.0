/* Master Lib */
#include "AdminController.h"

/* Default Lib */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* Add_On Lib */
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
#include <cmath>
#include <Windows.h>
#include <iomanip>
#include <typeinfo>
#include <cstdlib>
#include "PromptBox.h"
#include "TextTable.h"
//#include "pdf.h"

	/* SQL LIB */
	#include <cppconn/driver.h>
	#include <cppconn/exception.h>
	#include <cppconn/resultset.h>
	#include <cppconn/statement.h>
	#include <cppconn/prepared_statement.h>

using namespace std;


//Completed 16/04/2020
int AdminController::countDay(int year, int month, int day) {

	int newDay = 0;

	if (month == 1) {

		newDay = 31 - (31 - day);

	}
	else if (month == 2) {

		if (year % 4 == 0) {
			newDay = 60 - (29 - day);
		}
		else {
			newDay = 60 - (28 - day);
		}
	}
	else if (month == 3) {

		newDay = 91 - (31 - day);
	}
	else if (month == 4) {

		newDay = 121 - (30 - day);
	}
	else if (month == 5) {

		newDay = 152 - (31 - day);
	}
	else if (month == 6) {

		newDay = 182 - (30 - day);
	}
	else if (month == 7) {

		newDay = 213 - (31 - day);
	}
	else if (month == 8) {

		newDay = 244 - (31 - day);
	}
	else if (month == 9) {

		newDay = 274 - (30 - day);
	}
	else if (month == 10) {

		newDay = 305 - (31 - day);
	}
	else if (month == 11) {

		newDay = 335 - (30 - day);
	}
	else if (month == 12) {

		newDay = 366 - (31 - day);
	}
	else {
	}

	return newDay;
}

//Completed 16/04/2020
int AdminController::masterCountDays(char compDate[19]) {

	int finalDayCount = 0;

	/* Current Date */
	struct tm newtime;
	time_t now = time(0);

	localtime_s(&newtime, &now);

	int currentYear = 1900 + newtime.tm_year;
	int currentMon = 1 + newtime.tm_mon;
	int currentDay = newtime.tm_mday;

	/* Complaint Date */

	const char* delim = " ,.-:";
	char* nullToken;
	tm* ltm = new tm;
	char* pch;

	/* Extracting Date*/
	pch = strtok_s(compDate, delim, &nullToken);
	ltm->tm_year = atoi(pch);
	ltm->tm_mon = atoi(strtok_s(NULL, delim, &nullToken));
	ltm->tm_mday = atoi(strtok_s(NULL, delim, &nullToken));

	/* Assigning Data */
	int compYear = ltm->tm_year;
	int compMon = ltm->tm_mon;
	int compDay = ltm->tm_mday;

	 /* End of Gathering Data */

	 /* Subtract between Current and Complaint Date */
	int tYear = currentYear - compYear;

	/* Assigning new Data */
	int newYear = 0;

	if (tYear >= 1) {

		int size = currentYear;
		for (int i = compYear; i < size; i++) {

			if (i % 4 == 0) {

				newYear = newYear + 366;
			}
			else {
				newYear = newYear + 365;
			}
		}

	}

	finalDayCount = ((countDay(currentYear, currentMon, currentDay)) - (countDay(compYear, compMon, compDay))) + newYear;


	

	return finalDayCount;
	delete& newtime;
	delete& now;
	delete delim;
	delete nullToken;
	delete ltm;
	delete pch;
}

// Completed 14/04/2020  CHECKED : 27/04/2020
int AdminController::addUser(sql::Connection* conn, string adminName,int adminID) {

	int success = -1;
	int verification = 0;

	// Start : Local Variable
	string fullname;
	string password = "abc123";
	string email;
	string contact;
	string department;
	string status = "USER";
	string address = "N/A";
	string state = "N/A";
	string country = "N/A";
	string pincode = "N/A";
	// End : Local Variable

	d.adminStatic();
	cout << "\nAdd User"<< adminName << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << "Fullname\t: " << flush;
	d.adminInput();
	cin >> fullname;
	d.adminCOLOR();
	cout << "Email\t\t: " << flush;
	d.adminInput();
	cin >> email;
	d.adminCOLOR();
	cout << "Contact\t\t: " << flush;
	d.adminInput();
	cin >> contact;
	d.adminCOLOR();
	cout << "Department\t: " << flush;
	d.adminInput();
	cin >> department;
	d.adminCOLOR();
	/*
	/* Get Admin Detalis

	sql::PreparedStatement* pstmtAdmin;
	sql::ResultSet* resAdmin;
	int adminID = 0;

	pstmtAdmin = conn->prepareStatement("Select AdminID from admin where fullname = ?");
	pstmtAdmin->setString(1, adminName);
	resAdmin = pstmtAdmin->executeQuery();
	if (resAdmin->next()) {

		adminID = resAdmin->getInt(1);
	}
	/* End Admin Detalis
	*/


	// Start : Verification User 

	sql::PreparedStatement* pstmtVerifyUsr;
	sql::ResultSet* resVerifyUsr;
	string verifySQL = "Select fullname from users where fullname = ?";

	pstmtVerifyUsr = conn->prepareStatement(verifySQL);
	pstmtVerifyUsr->setString(1, fullname);
	resVerifyUsr = pstmtVerifyUsr->executeQuery();

	if (resVerifyUsr->next()) {

		verification = 1;
	}


	// End : Verification User 

	if (verification == 0) {

		cout << endl << endl;
		d.info();
		cout << "Are you sure to register ? [ Y/N ]" << endl;
		d.select();

		string data;
		cout << "Select\t: " << flush;
		cin >> data;

		// convert string to upper case
		for_each(data.begin(), data.end(), [](char& c) {
			c = ::toupper(c);
			});

		if (data == "Y") {

			/* START : Adding User */

			sql::PreparedStatement* pstmt;
			string addSQL = "insert into users (AdminID,fullname,password,email,contact,department,status,address,state,country,pincode) values (?,?,?,?,?,?,?,?,?,?,?)";
			pstmt = conn->prepareStatement(addSQL);
			pstmt->setInt(1, adminID);
			pstmt->setString(2, fullname);
			pstmt->setString(3, password);
			pstmt->setString(4, email);
			pstmt->setString(5, contact);
			pstmt->setString(6, department);
			pstmt->setString(7, status);
			pstmt->setString(8, address);
			pstmt->setString(9, state);
			pstmt->setString(10, country);
			pstmt->setString(11, pincode);
			success = pstmt->execute();

			/* END : Adding User */

			PromptBox::successAdd();
			delete pstmt;
		}
		else {
			d.danger();
			PromptBox::exiting();
			d.defaultCOLOR();
		}


	}
	else {

		d.info();
		system("cls");
		cout << "This User Already Exist " << endl;
		Sleep(3000);
		d.adminCOLOR();
	}

	delete pstmtVerifyUsr;
	return success;

}

// Completed 14/04/2020 CHECKED : 27/04/2020
int AdminController::updateUser(sql::Connection* conn,string adminName,int adminID) {

	int success = -1;
	

	// START : Local Variable
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
	// END : Local Variable


	currentUser(conn, "Update", "Admin");
	d.select();
	cout << "Select User ID\t: " << flush;
	cin >> uID;
	d.adminCOLOR();

	// START  : View User Data to Update
	sql::PreparedStatement* pstmt;
	sql::PreparedStatement* pstmtUser1;
	sql::ResultSet* resUser1;

	pstmtUser1 = conn->prepareStatement("Select * from users where UID = ?");
	pstmtUser1->setInt(1, uID);
	resUser1 = pstmtUser1->executeQuery();

	if (resUser1->next()) {

		system("cls");
		d.adminStatic();
		cout << "\nUpdate User" << endl;
		cout << "@Admin\n" << endl;
		d.adminCOLOR();

		cout << " Existing " << resUser1->getString("fullname") << " Data"<< endl;
		cout << "------------------------------------------------------" << endl;

		d.adminTableData();
		cout << "[1]\tEmail\t\t: " << resUser1->getString("email") << endl;
		cout << "[2]\tContact\t\t: " << resUser1->getString("contact") << endl;
		cout << "[3]\tDepartment\t: " << resUser1->getString("department") << endl; 
		cout << "[4]\tAddress\t\t: " << resUser1->getString("address") << endl;
		cout << "[5]\tState\t\t: " << resUser1->getString("state") << endl;
		cout << "[6]\tCountry\t\t: " << resUser1->getString("country") << endl;
		cout << "[7]\tPincode\t\t: " << resUser1->getString("pincode") << endl;
		cout << "[8]\tChange All" << endl;
		cout << "[9]\tExit without change" << endl;
		d.adminCOLOR();
		cout << "------------------------------------------------------\n" << endl;
		d.select();
		cout << "Select\t: " << flush;
		cin >> sel;
		cout << endl << endl;
		d.adminCOLOR();


		switch (sel)
		{
		case 1:
			cout << "Email\t\t: " << flush;
			d.adminInput();
			cin >> email;
			pstmt = conn->prepareStatement("update users set email = ? where UID = ?");
			pstmt->setString(1, email);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 2:
			cout << "Contact\t\t: " << flush;
			d.adminInput();
			cin >> contact;
			pstmt = conn->prepareStatement("update users set contact = ? where UID = ?");
			pstmt->setString(1, contact);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 3:
			cout << "Department\t: " << flush;
			d.adminInput();
			cin >> department;
			pstmt = conn->prepareStatement("update users set department = ? where UID = ?");
			pstmt->setString(1, department);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 4:
			cout << "Address\t\t: " << flush;
			d.adminInput();
			getline(cin.ignore(), address);
			pstmt = conn->prepareStatement("update users set address = ? where UID = ?");
			pstmt->setString(1, address);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 5:
			cout << "State\t\t: " << flush;
			d.adminInput();
			cin >> state;
			pstmt = conn->prepareStatement("update users set state = ? where UID = ?");
			pstmt->setString(1, state);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 6:
			cout << "Country\t\t: " << flush;
			d.adminInput();
			cin >> country;
			pstmt = conn->prepareStatement("update users set country = ? where UID = ?");
			pstmt->setString(1, country);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 7:
			cout << "Pincode\t\t: " << flush;
			d.adminInput();
			cin >> pincode;
			pstmt = conn->prepareStatement("update users set pincode = ? where UID = ?");
			pstmt->setString(1, pincode);
			pstmt->setInt(2, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 8:
			cout << "Email\t\t: " << flush;
			d.adminInput();
			cin >> email;
			d.adminCOLOR();
			cout << "Contact\t\t: " << flush;
			d.adminInput();
			cin >> contact;
			d.adminCOLOR();
			cout << "Department\t: " << flush;
			d.adminInput();
			cin >> department;
			d.adminCOLOR();
			cout << "Address\t\t: " << flush;
			d.adminInput();
			cin >> address;
			d.adminCOLOR();
			cout << "State\t\t: " << flush;
			d.adminInput();
			cin >> state;
			d.adminCOLOR();
			cout << "Country\t\t: " << flush;
			d.adminInput();
			cin >> country;
			d.adminCOLOR();
			cout << "Pincode\t\t: " << flush;
			d.adminInput();
			cin >> pincode;

			pstmt = conn->prepareStatement("update users set email = ?,contact = ?,department = ?,address = ?,state = ?,country = ?,pincode = ? where UID = ?");

			pstmt->setString(1, email);
			pstmt->setString(2, contact);
			pstmt->setString(3, department);
			pstmt->setString(4, address);
			pstmt->setString(5, state);
			pstmt->setString(6, country);
			pstmt->setString(7, pincode);
			pstmt->setInt(8, uID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;

		case 9:
			break;

		default:
			
			cout << "Wrong Input" << endl;
			Sleep(3000);
		}

		d.success();
		PromptBox::successUpdate();
		d.adminCOLOR();
	}
	// END  : View User Data to Update

	
	delete pstmtUser1;
	delete resUser1;
	return success;
}

// Completed 14/04/2020 CHECKED : 27/04/2020	NEED UPDATE FEATURE
void AdminController::deleteUser(sql::Connection* conn) {

	sql::PreparedStatement* pstmt;
	int uID;
	string decision;


	currentUser(conn, "Delete", "Admin");
	d.select();
	cout << "Select User ID\t: " << flush;
	cin >> uID;
	d.info();
	cout << endl;
	cout << "Area you sure to delete ID " << uID << " ? " << endl;
	d.select();
	cout << "[ Y / N ] = " << flush;
	cin >> decision;

	if (decision == "Y") {

		string deleteSQL = "delete from users where UID = ?";

		pstmt = conn->prepareStatement(deleteSQL);
		pstmt->setInt(1, uID);
		pstmt->executeUpdate();

		delete pstmt;
		PromptBox::successDelete();
	}
	if (decision == "y") {

		string deleteSQL = "delete from users where UID = ?";

		pstmt = conn->prepareStatement(deleteSQL);
		pstmt->setInt(1, uID);
		pstmt->executeUpdate();

		delete pstmt;
		d.success();
		PromptBox::successDelete();
	}
	else {

		d.danger();
		PromptBox::taskAbort();
	}
	
	d.adminCOLOR();
}

// Completed 14/04/2020		CHECKED : 27/04/2020
void AdminController::viewUser(sql::Connection* conn) {

	
	int i = 0;

	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	string sql = "select * from users";

	pstmt = conn->prepareStatement(sql);
	res = pstmt->executeQuery();
	d.adminStatic();
	cout << "\nView User" << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << " U S E R S   D A T A" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << setw(5)<< "ID" << setw(25) <<"Full Name" << setw(35) << "Email" << setw(25) << "Contact" << setw(25) << "Register Date" << endl;
	d.adminCOLOR();
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

	/*
	TextTable t(' .', '|', '+');
	t.add("Fullname");
	t.add("Email");
	t.add("Contact");
	t.add("Address");
	t.add("State");
	t.add("Country");
	t.add("Pin Code");
	t.add("Register Date");
	t.endOfRow();


	Sleep(2000);
	while (res->next()) {

		//cout << res->getString(4) << setw(15) << res->getString(6) << setw(15) << res->getString(7) << setw(15) << res->getString(10) << setw(15) << res->getString(11) << setw(15) << res->getString(12) << setw(15) << res->getString(13) << setw(15) << res->getString(14) << endl;
		t.add(res->getString(4));
		t.add(res->getString(6));
		t.add(res->getString(7));
		t.add(res->getString(10));
		t.add(res->getString(11));
		t.add(res->getString(12));
		t.add(res->getString(13));
		t.add(res->getString(14));
		t.endOfRow();
		i++;
	}

	t.setAlignment(2, TextTable::Alignment::RIGHT);
	cout << t;
	*/
	d.adminTableData();
	Sleep(2000);
	while (res->next()) {

		cout << setw(5) << res->getInt(1) << setw(25) << res->getString(4) << setw(35) << res->getString(6) << setw(25) << res->getString(7) << setw(25) << res->getString(14) << endl;
		i++;
	
	}
	d.adminCOLOR();
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
	
	cout << "Total Users\t: " << i << endl;
	cout << endl << endl;
	d.info();
	int sel;
	cout << "[1] More details about an user" << endl;
	cout << "[2] Back to Main Menu" << endl << endl;
	d.select();
	cout << "Select : " << flush;
	cin >> sel;
	int user;

	switch (sel)
	{
	case 1:
		cout << "Select User\t: " << flush;
		cin >> user;
		system("cls");
		userdetails(conn, user);
		cout << endl;
		system("pause");
		break;
	case 2:
		d.danger();
		PromptBox::exiting();
		break;
	default:
		break;
	}
	d.adminCOLOR();
	delete pstmt;
	delete res;

}

// Completed 14/04/2020		CHECKED : 27/04/2020
int AdminController::addStaff(sql::Connection* conn,string adminName,int adminID) {

	//User user;
	int success = -1;
	int verification = 0;
	sql::PreparedStatement* pstmt;

	// Local Variable
	string fullname;
	string password = "abc123";
	string email;
	string contact;
	string status = "STAFF";
	string address = "N/A";
	string state = "N/A";
	string country = "N/A";
	string pincode = "N/A";
	// End of Local Variable
	d.adminStatic();
	cout << "\nAdd Staff"<< endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << "Fullname\t: " << flush;
	d.adminInput();
	cin >> fullname;
	d.adminCOLOR();
	cout << "Email\t\t: " << flush;
	d.adminInput();
	cin >> email;
	d.adminCOLOR();
	cout << "Contact\t\t: " << flush;
	d.adminInput();
	cin >> contact;
	d.adminCOLOR();
	// NEW FEATURE
	sql::PreparedStatement* pstmtVerifyUsr;
	sql::ResultSet* resVerifyUsr;
	string verifySQL = "Select fullname from staff where fullname = ?";

	pstmtVerifyUsr = conn->prepareStatement(verifySQL);
	pstmtVerifyUsr->setString(1, fullname);
	resVerifyUsr = pstmtVerifyUsr->executeQuery();

	if (resVerifyUsr->next()) {

		verification = 1;
	}


	// End : Verification User 

	if (verification == 0) {

		cout << endl << endl;
		d.info();
		cout << "Are you sure to register ? [ Y/N ]" << endl;
		d.select();

		string data;
		cout << "Select\t: " << flush;
		cin >> data;

		// convert string to upper case
		for_each(data.begin(), data.end(), [](char& c) {
			c = ::toupper(c);
			});

		if (data == "Y") {

			/* START : Adding User */
			/*
			sql::PreparedStatement* pstmt;
			string addSQL = "insert into users (AdminID,fullname,password,email,contact,department,status,address,state,country,pincode) values (?,?,?,?,?,?,?,?,?,?,?)";
			pstmt = conn->prepareStatement(addSQL);
			pstmt->setInt(1, adminID);
			pstmt->setString(2, fullname);
			pstmt->setString(3, password);
			pstmt->setString(4, email);
			pstmt->setString(5, contact);
			pstmt->setString(6, department);
			pstmt->setString(7, status);
			pstmt->setString(8, address);
			pstmt->setString(9, state);
			pstmt->setString(10, country);
			pstmt->setString(11, pincode);
			success = pstmt->execute();
			*/

			string addSQL = "insert into staff (AdminID,fullname,password,email,contact,status,address,state,country,pincode) values (?,?,?,?,?,?,?,?,?,?)";
			pstmt = conn->prepareStatement(addSQL);
			pstmt->setInt(1, adminID);
			pstmt->setString(2, fullname);
			pstmt->setString(3, password);
			pstmt->setString(4, email);
			pstmt->setString(5, contact);
			pstmt->setString(6, status);
			pstmt->setString(7, address);
			pstmt->setString(8, state);
			pstmt->setString(9, country);
			pstmt->setString(10, pincode);
			success = pstmt->execute();
			/* END : Adding User */
			d.success();
			PromptBox::successAdd();
			delete pstmt;
		}
		else {
			d.danger();
			PromptBox::exiting();
			d.defaultCOLOR();
		}

		d.adminCOLOR();
	}
	else {

		d.info();
		system("cls");
		cout << "This Staff Already Exist " << endl;
		Sleep(3000);
		d.adminCOLOR();
	}


	// END FEATURE





	/* Start Process to Adding User */
	/*
	string addSQL = "insert into staff (AdminID,fullname,password,email,contact,status,address,state,country,pincode) values (?,?,?,?,?,?,?,?,?,?)";
	pstmt = conn->prepareStatement(addSQL);
	pstmt->setInt(1, adminID);
	pstmt->setString(2, fullname);
	pstmt->setString(3, password);
	pstmt->setString(4, email);
	pstmt->setString(5, contact);
	pstmt->setString(6, status);
	pstmt->setString(7, address);
	pstmt->setString(8, state);
	pstmt->setString(9, country);
	pstmt->setString(10, pincode);
	success = pstmt->execute();
	*/
	/* End Process to Adding User */
	//PromptBox::successAdd();

	//delete pstmtAdmin;
	//delete resAdmin;
	
	//con->close();
	return success;

}

// Completed 14/04/2020
int AdminController::updateStaff(sql::Connection* conn,string adminName) {


	int success = -1;
	sql::PreparedStatement* pstmt;

	// Local Variable
	int sID;
	int sel;

	string fullname;
	string password;
	string email;
	string contact;
	string status;
	string address;
	string state;
	string country;
	string pincode;
	// End of Local Variable

	
	currentStaff(conn, "Update", "Admin");

	cout << "Select User ID\t: " << flush;
	cin >> sID;


	/* Selection */
	sql::PreparedStatement* pstmtUser1;
	sql::ResultSet* resUser1;

	pstmtUser1 = conn->prepareStatement("Select * from staff where StaffID = ?");
	pstmtUser1->setInt(1, sID);
	resUser1 = pstmtUser1->executeQuery();

	if (resUser1->next()) {

		system("cls");
		d.adminStatic();
		cout << "\nUpdate User" << endl;
		cout << "@Admin\n" << endl;
		d.adminCOLOR();
		cout << " Existing " << resUser1->getString("fullname") << " Data" << endl;
		cout << "------------------------------------------------------" << endl;
		d.adminTableData();
		cout << "[1]\tEmail\t\t: " << resUser1->getString("email") << endl;
		cout << "[2]\tContact\t\t: " << resUser1->getString("contact") << endl;
		cout << "[3]\tAddress\t\t: " << resUser1->getString("address") << endl;
		cout << "[4]\tState\t\t: " << resUser1->getString("state") << endl;
		cout << "[5]\tCountry\t\t: " << resUser1->getString("country") << endl;
		cout << "[6]\tPincode\t\t: " << resUser1->getString("pincode") << endl;
		cout << "[7]\tChange All" << endl;
		cout << "[8]\tExit without change" << endl;
		d.adminCOLOR();
		cout << "------------------------------------------------------\n" << endl;
		d.select();
		cout << "Select\t: " << flush;
		cin >> sel;
		cout << endl << endl;


		d.adminCOLOR();
		switch (sel)
		{
		case 1:
			cout << "Email\t\t: " << flush;
			d.adminInput();
			cin >> email;
			pstmt = conn->prepareStatement("update staff set email = ? where StaffID = ?");
			pstmt->setString(1, email);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 2:
			cout << "Contact\t\t: " << flush;
			d.adminInput();
			cin >> contact;
			pstmt = conn->prepareStatement("update staff set contact = ? where StaffID = ?");
			pstmt->setString(1, contact);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 3:
			cout << "Address\t\t: " << flush;
			d.adminInput();
			getline(cin.ignore(), address);
			pstmt = conn->prepareStatement("update staff set address = ? where StaffID = ?");
			pstmt->setString(1, address);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 4:
			cout << "State\t\t: " << flush;
			d.adminInput();
			cin >> state;
			pstmt = conn->prepareStatement("update staff set state = ? where StaffID = ?");
			pstmt->setString(1, state);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 5:
			cout << "Country\t\t: " << flush;
			d.adminInput();
			cin >> country;
			pstmt = conn->prepareStatement("update staff set country = ? where StaffID = ?");
			pstmt->setString(1, country);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 6:
			cout << "Pincode\t\t: " << flush;
			d.adminInput();
			cin >> pincode;
			pstmt = conn->prepareStatement("update staff set pincode = ? where StaffID = ?");
			pstmt->setString(1, pincode);
			pstmt->setInt(2, sID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 7:
			cout << "Email\t\t: " << flush;
			d.adminInput();
			cin >> email;
			d.adminCOLOR();
			cout << "Contact\t\t: " << flush;
			d.adminInput();
			cin >> contact;
			d.adminCOLOR();
			cout << "Status\t\t: " << flush;
			d.adminInput();
			cin >> status;
			d.adminCOLOR();
			cout << "Address\t\t: " << flush;
			d.adminInput();
			cin >> address;
			d.adminCOLOR();
			cout << "State\t\t: " << flush;
			d.adminInput();
			cin >> state;
			d.adminCOLOR();
			cout << "Country\t\t: " << flush;
			d.adminInput();
			cin >> country;
			d.adminCOLOR();
			cout << "Pincode\t\t: " << flush;
			d.adminInput();
			cin >> pincode;
			d.adminCOLOR();
			pstmt = conn->prepareStatement("update staff set email = ?,contact = ?,address = ?,state = ?,country = ?,pincode = ? where StaffID = ?");

			pstmt->setString(1, email);
			pstmt->setString(2, contact);
			pstmt->setString(3, address);
			pstmt->setString(4, state);
			pstmt->setString(5, country);
			pstmt->setString(6, pincode);
			pstmt->setInt(7, sID);

			success = pstmt->executeUpdate();

			delete pstmt;
			break;
		case 8:
			break;
		default:
			cout << "Wrong Input" << endl;
		}

		/*
		cout << "Fullname\t: " << flush;
		cin >> fullname;
		system("cls");
		cout << "Password\t: " << flush;
		cin >> password;
		cout << "Email\t\t: " << flush;
		cin >> email;
		cout << "Contact\t\t: " << flush;
		cin >> contact;
		cout << "Department\t: " << flush;
		cin >> department;
		cout << "Status\t\t: " << flush;
		cin >> status;
		cout << "Address\t\t: " << flush;
		cin >> address;
		cout << "State\t\t: " << flush;
		cin >> state;
		cout << "Country\t\t: " << flush;
		cin >> country;
		cout << "Pincode\t\t: " << flush;
		cin >> pincode;
		*/
		/*
		string updateSQL = "update users set password = ?,email = ?,contact = ?,department = ?,status = ?,address = ?,state = ?,country = ?,pincode = ? where fullname = ?";

		pstmt = conn->prepareStatement(updateSQL);

		pstmt->setString(1, password);
		pstmt->setString(2, email);
		pstmt->setString(3, contact);
		pstmt->setString(4, department);
		pstmt->setString(5, status);
		pstmt->setString(6, address);
		pstmt->setString(7, state);
		pstmt->setString(8, country);
		pstmt->setString(9, pincode);
		pstmt->setString(10, fullname);
		success = pstmt->executeUpdate();
		delete pstmt;
		*/

		if (success == 1) {
			d.success();
			PromptBox::successUpdate();
		}
		else {
			d.danger();
			PromptBox::taskAbort();
		}
		d.adminCOLOR();
		
	}

	/*
	cout << "Update User\n" << endl;
	cout << "Fullname\t: " << flush;
	cin >> fullname;
	system("cls");
	cout << "Password\t: " << flush;
	cin >> password;
	cout << "Email\t\t: " << flush;
	cin >> email;
	cout << "Contact\t\t: " << flush;
	cin >> contact;
	cout << "Status\t\t: " << flush;
	cin >> status;
	cout << "Address\t\t: " << flush;
	cin >> address;
	cout << "State\t\t: " << flush;
	cin >> state;
	cout << "Country\t\t: " << flush;
	cin >> country;
	cout << "Pincode\t\t: " << flush;
	cin >> pincode;

	string updateSQL = "update staff set password = ?,email = ?,contact = ?,status = ?,address = ?,state = ?,country = ?,pincode = ? where fullname = ?";

	pstmt = conn->prepareStatement(updateSQL);

	pstmt->setString(1, password);
	pstmt->setString(2, email);
	pstmt->setString(3, contact);
	pstmt->setString(4, status);
	pstmt->setString(5, address);
	pstmt->setString(6, state);
	pstmt->setString(7, country);
	pstmt->setString(8, pincode);
	pstmt->setString(9, fullname);
	success = pstmt->executeUpdate();
	
	delete pstmt;*/
	return success;
}

// Completed 14/04/2020
void AdminController::deleteStaff(sql::Connection* conn) {

	sql::PreparedStatement* pstmt;
	int sID;
	string decision;

	/*
	cout << "\nDelete Staff" << endl;
	cout << "@Admin\n" << endl;

	cout << "C U R R E N T   S T A F F " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "ID" << setw(20) << "Full Name" << endl;
	cout << "------------------------------------------------------" << endl;
	Sleep(2000);
	/* LIST USER 
	sql::PreparedStatement* pstmtUser;
	sql::ResultSet* resUser;

	pstmtUser = conn->prepareStatement("Select StaffID,fullname from staff");
	resUser = pstmtUser->executeQuery();
	while (resUser->next()) {

		//cout << res->getString(1) << "\t\t" << res->getString(2) << endl;
		cout << "[ " << resUser->getInt(1) << " ]" << setw(20) << resUser->getString(2) << endl;
	}
	cout << "------------------------------------------------------" << endl;
	*/

	currentStaff(conn, "Delete", "Admin");
	d.select();
	cout << "Select User ID\t: " << flush;
	cin >> sID;
	cout << endl;
	d.info();
	cout << "Area you sure to delete ID " << sID << " ?" << endl;
	d.select();
	cout<<" [Y / N] = " << flush;
	cin >> decision;
	d.adminCOLOR();
	if (decision == "Y") {

		string deleteSQL = "delete from staff where StaffID = ?";

		pstmt = conn->prepareStatement(deleteSQL);
		pstmt->setInt(1, sID);
		pstmt->executeUpdate();

		delete pstmt;
		d.success();
		PromptBox::successDelete();
	}
	else {

		d.danger();
		PromptBox::taskAbort();
	}


}

// Completed 15/04/2020
void AdminController::viewStaff(sql::Connection* conn) {


	string sql = "select * from staff";
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	int i = 0;

	pstmt = conn->prepareStatement(sql);
	res = pstmt->executeQuery();

	d.adminStatic();
	cout << "\nView Staff" << endl;
	cout << "@Admin\n" << endl;
	cout << " S T A F F   D A T A" << endl;
	//cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	//cout << "Full Name" << setw(15) << "Email" << setw(15) << "Contact" << setw(15) << "Address" << setw(15) << "State" << setw(15) << "Country" << setw(15) << "Pin Code" << setw(15) << "Register Date" << endl;
	//cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	TextTable t(' .', '|', '+');
	t.add("Fullname");
	t.add("Email");
	t.add("Contact");
	//t.add("Address");
	//t.add("State");
	//t.add("Country");
	//t.add("Pin Code");
	t.add("Register Date");
	t.endOfRow();


	Sleep(2000);
	while (res->next()) {

		//cout << res->getString(4) << setw(15) << res->getString(6) << setw(15) << res->getString(7) << setw(15) << res->getString(10) << setw(15) << res->getString(11) << setw(15) << res->getString(12) << setw(15) << res->getString(13) << setw(15) << res->getString(14) << endl;
		t.add(res->getString(3));
		t.add(res->getString(5));
		t.add(res->getString(6));
		//t.add(res->getString(8));
		//t.add(res->getString(9));
		//t.add(res->getString(10));
		//t.add(res->getString(11));
		t.add(res->getString(12));
		t.endOfRow();
		i++;
	}

	t.setAlignment(2, TextTable::Alignment::RIGHT);
	d.adminCOLOR();
	cout << t;
	cout << endl;
	d.info();
	cout << "Total Users\t: " << i << endl;
	d.adminCOLOR();
	system("pause");

	delete pstmt;
	delete res;

}

int AdminController::addComplaint(sql::Connection* conn) {

	//User user;
	int success = -1;
	sql::PreparedStatement* pstmt;

	// Local Variable
	string model;
	string noSerial;
	string respond;
	string details;
	// End of Local Variable

	cout << "Add Complaint\n" << endl;
	cout << "Model\t: " << flush;
	cin >> model;
	cout << "Serial Number\t: " << flush;
	cin >> noSerial;
	cout << "Detail\t\t: " << flush;
	cin >> details;
	cout << "Respond\t\t: " << flush;
	cin >> respond;

	/* Start Process to Adding User */

	string addSQL = "insert into complaint (model,noSerial,details,respond) values (?,?,?,?)";
	pstmt = conn->prepareStatement(addSQL);
	pstmt->setString(1, model);
	pstmt->setString(2, noSerial);
	pstmt->setString(3, details);
	pstmt->setString(4, respond);
	success = pstmt->execute();

	/* End Process to Adding User */

	delete pstmt;
	//con->close();
	return success;

}

int AdminController::updateComplaint(sql::Connection* conn) {


	int success = -1;
	sql::PreparedStatement* pstmt;

	// Local Variable
	string ID;
	string model;
	string noSerial;
	string respond;
	string details;
	// End of Local Variable

	cout << "Add Complaint\n" << endl;
	cout << "ID\t: " << flush;
	cin >> ID;
	cout << "Model\t: " << flush;
	cin >> model;
	cout << "Serial Number\t: " << flush;
	cin >> noSerial;
	cout << "Detail\t\t: " << flush;
	cin >> details;
	cout << "Respond\t\t: " << flush;
	cin >> respond;

	string updateSQL = "update complaint set model = ?,noSerial = ?,details = ?,respond = ? where CompID = ?";

	pstmt = conn->prepareStatement(updateSQL);

	pstmt->setString(1, model);
	pstmt->setString(2, noSerial);
	pstmt->setString(3, details);
	pstmt->setString(4, respond);
	pstmt->setString(5, ID);
	success = pstmt->executeUpdate();

	delete pstmt;
	return success;
}

void AdminController::deleteComplaint(sql::Connection* conn) {

	sql::PreparedStatement* pstmt;

	string compID;
	cout << "Delete User" << endl;
	cout << "Complaint ID\t: " << flush;
	cin >> compID;

	string deleteSQL = "delete from complaint where CompID = ?";

	pstmt = conn->prepareStatement(deleteSQL);
	pstmt->setString(1, compID);
	pstmt->executeUpdate();

	delete pstmt;
}

// Completed 16/04/2020
void AdminController::viewComplaint(sql::Connection* conn) {

	/*
	string sql = "select model, noSerial from complaint";
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	pstmt = conn->prepareStatement(sql);
	res = pstmt->executeQuery();

	while (res->next()) {

		cout << res->getString(1) << "\t\t" << res->getString(2) << endl;
	}

	delete pstmt;
	delete res;
	*/

	int sel;
	int i = 0;
	char cstr[19];

	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	cout << endl;
	d.adminStatic();
	cout << "View Complaint" << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << "[1]\t NOT PROCESS " << endl;
	cout << "[2]\t IN PROCESS " << endl;
	cout << "[3]\t SOLVED" << endl;
	cout << "[4]\t VIEW ALL" << endl << endl;
	d.select();
	cout << "Enter your choice\t: " << flush;
	cin >> sel;
	d.adminCOLOR();
	system("cls");
	switch (sel)
	{
	case 1:
		viewComplaintAction(conn, "NOT PROCESS","Admin");
		break;
	case 2:
		viewComplaintAction(conn, "IN PROCESS", "Admin");
		break;
	case 3:
		viewComplaintAction(conn, "SOLVED", "Admin");
		break;
	case 4:
		viewAllComplaintAction(conn, "Admin");
		break;
	default:
		break;
	}
}

// Completed 15/04/2020
int AdminController::addPlace(sql::Connection* conn) {

	int success = -1;
	string approve;
	sql::PreparedStatement* pstmt;

	/* Local Variable */
	string wing,floor,lab;
	int inWing, inFloor, inLab;
	/* Output */
	d.adminStatic();
	cout << endl;
	cout << "Add Place" << endl;
	cout << "@Admin\n" << endl;
	cout << endl;

	d.adminCOLOR();
	cout << "[1]\tLeft"<< endl;
	cout << "[2]\tRight" << endl;
	cout << endl;
	d.select();
	cout << "Wing\t: " << flush;
	cin >> inWing;
	if (inWing == 1) {

		wing = "LEFT";
	}
	if (inWing == 2) {

		wing = "RIGHT";
	}
	d.adminCOLOR();
	cout << "\n-------------------------------------------"<<endl;
	cout << endl;
	cout << "[1]\tFirst Floor" << endl;
	cout << "[2]\tSecond Floor" << endl;
	cout << "[3]\tThird Floor" << endl;
	cout << endl;
	d.select();
	cout << "Floor\t: " << flush;
	cin >> inFloor;
	if (inFloor == 1) {

		floor = "FIRST FLOOR";
	}
	if (inFloor == 2) {

		floor = "SECOND FLOOR";
	}
	if (inFloor == 3) {

		floor = "THIRD FLOOR";
	}
	d.adminCOLOR();
	cout << "\n-------------------------------------------" << endl;
	cout << endl;
	d.select();
	cout << "Lab\t\t: " << flush;
	getline(cin.ignore(), lab);
	d.adminCOLOR();

	cout << endl << endl;
	d.info();
	cout << "Are you sure to ADD ?" << endl;
	d.select();
	cout << "[Y / N]\t= " << flush;
	cin >> approve;
	if (approve == "Y") {

		/* Start Process to Adding Place */

		string addSQL = "insert into place (wing,floor,Lab) values (?,?,?)";
		pstmt = conn->prepareStatement(addSQL);
		pstmt->setString(1, wing);
		pstmt->setString(2, floor);
		pstmt->setString(3, lab);
		success = pstmt->execute();
		d.success();
		PromptBox::successAdd();
		/* End Process to Adding User */
	}
	else {
		d.danger();
		PromptBox::taskAbort();
	}
	return success;
}

// Completed 15/04/2020
int AdminController::updatePlace(sql::Connection* conn) {

	int success = -1;
	sql::PreparedStatement* pstmt;

	// Local Variable
	int pID, sel, inWing,inFloor;
	string wing, floor, lab;

	
	// End of Local Variable
	d.adminStatic();
	cout << "\nUpdate Place" << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << "C U R R E N T   P L A C E" << endl;
	cout << "------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << "ID" << "\t\t\t" << "NAME" << endl;
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	Sleep(2000);

	/* LIST PLACE */
	sql::PreparedStatement* pstmtPlace;
	sql::ResultSet* resPlace;
	d.adminTableData();
	pstmtPlace = conn->prepareStatement("Select PlaceID,Lab from place");
	resPlace = pstmtPlace->executeQuery();
	while (resPlace->next()) {

		//cout << res->getString(1) << "\t\t" << res->getString(2) << endl;
		cout << "[ " << resPlace->getInt(1) << " ]" << "\t\t\t" << resPlace->getString(2) << endl;
	}
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	d.select();
	cout << "Select Place ID\t: " << flush;
	cin >> pID;


	/* Selection */
	sql::PreparedStatement* pstmtPlace1;
	sql::ResultSet* resPlace1;

	pstmtPlace1 = conn->prepareStatement("Select * from place where PlaceID = ?");
	pstmtPlace1->setInt(1, pID);
	resPlace1 = pstmtPlace1->executeQuery();

	if (resPlace1->next()) {

		system("cls");
		d.adminStatic();
		cout << "\nUpdate Place" << endl;
		cout << "@Admin\n" << endl;
		d.adminCOLOR();

		cout << " Existing " << resPlace1->getString("Lab") << " Data" << endl;
		cout << "------------------------------------------------------" << endl;
		d.adminTableData();
		cout << "[1]\tWing\t\t: " << resPlace1->getString("wing") << endl;
		cout << "[2]\tFloor\t\t: " << resPlace1->getString("floor") << endl;
		cout << "[3]\tChange All" << endl;
		cout << "[4]\tExit without changing" << endl;
		d.adminCOLOR();
		cout << "------------------------------------------------------\n" << endl;
		d.select();
		cout << "Select\t: " << flush;
		cin >> sel;
		cout << endl << endl;


		d.adminCOLOR();
		switch (sel)
		{
		case 1:
			cout << "[1]\tLeft" << endl;
			cout << "[2]\tRight" << endl;
			cout << endl;
			d.select();
			cout << "Wing\t: " << flush;
			cin >> inWing;
			if (inWing == 1) {

				wing = "LEFT";
			}
			if (inWing == 2) {

				wing = "RIGHT";
			}

			pstmt = conn->prepareStatement("update place set wing = ? where PlaceID = ?");
			pstmt->setString(1, wing);
			pstmt->setInt(2, pID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;
		case 2:
			cout << "[1]\tFirst Floor" << endl;
			cout << "[2]\tSecond Floor" << endl;
			cout << "[3]\tThird Floor" << endl;
			cout << endl;
			d.select();
			cout << "Floor\t: " << flush;
			cin >> inFloor;
			if (inFloor == 1) {

				floor = "FIRST FLOOR";
			}
			if (inFloor == 2) {

				floor = "SECOND FLOOR";
			}
			if (inFloor == 3) {

				floor = "THIRD FLOOR";
			}
			pstmt = conn->prepareStatement("update place set floor = ? where PlaceID = ?");
			pstmt->setString(1, floor);
			pstmt->setInt(2, pID);
			success = pstmt->executeUpdate();
			delete pstmt;
			break;

		case 3:
			cout << "[1]\tLeft" << endl;
			cout << "[2]\tRight" << endl;
			cout << endl;
			d.select();
			cout << "Wing\t: " << flush;
			cin >> inWing;
			if (inWing == 1) {

				wing = "LEFT";
			}
			if (inWing == 2) {

				wing = "RIGHT";
			}
			d.adminCOLOR();
			cout << "\n-------------------------------------------" << endl;
			cout << endl;
			
			cout << "[1]\tFirst Floor" << endl;
			cout << "[2]\tSecond Floor" << endl;
			cout << "[3]\tThird Floor" << endl;
			cout << endl;
			d.select();
			cout << "Floor\t: " << flush;
			cin >> inFloor;
			if (inFloor == 1) {

				floor = "FIRST FLOOR";
			}
			if (inFloor == 2) {

				floor = "SECOND FLOOR";
			}
			if (inFloor == 3) {

				floor = "THIRD FLOOR";
			}
			d.adminCOLOR();
			cout << "\n-------------------------------------------" << endl;
			cout << endl;

			d.select();
			cout << "Lab\t\t: " << flush;
			getline(cin.ignore(), lab);

			pstmt = conn->prepareStatement("update place set wing = ?,floor = ?,Lab = ? where PlaceID = ?");
			pstmt->setString(1, wing);
			pstmt->setString(2, floor);
			pstmt->setString(3, lab);
			pstmt->setInt(4, pID);
			success = pstmt->executeUpdate();

			delete pstmt;
			break;
		case 4:
			d.danger();
			PromptBox::taskAbort();
			success = 1;
			break;
		default:
			cout << "Wrong Input" << endl;
		}

		if (success == 1) {
			d.success();
			PromptBox::successUpdate();
		}
		else {
			d.danger();
			PromptBox::exiting();
		}
	}

	
	return success;
}

// Completed 15/04/2020
void AdminController::deletePlace(sql::Connection* conn) {

	sql::PreparedStatement* pstmt;
	int pID;
	string decision;
	d.adminStatic();
	cout << "\nDelete Place" << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();
	cout << "C U R R E N T   P L A C E" << endl;
	cout << "------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << "ID" << "\t\t\t" << "NAME" << endl;
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	Sleep(2000);

	/* LIST PLACE */
	sql::PreparedStatement* pstmtPlace;
	sql::ResultSet* resPlace;

	pstmtPlace = conn->prepareStatement("Select PlaceID,Lab from place");
	resPlace = pstmtPlace->executeQuery();
	while (resPlace->next()) {

		//cout << res->getString(1) << "\t\t" << res->getString(2) << endl;
		cout << "[ " << resPlace->getInt(1) << " ]" << "\t\t\t" << resPlace->getString(2) << endl;
	}
	cout << "------------------------------------------------------" << endl;
	d.select();
	cout << "Select Place ID\t: " << flush;
	cin >> pID;
	cout << endl;
	d.info();
	cout << "Area you sure to delete ID " << pID << " ? "<< endl;
	d.select();
	cout << "[Y / N] = " << flush;
	cin >> decision;
	d.adminCOLOR();
	if (decision == "Y") {

		string deleteSQL = "delete from place where PlaceID = ?";

		pstmt = conn->prepareStatement(deleteSQL);
		pstmt->setInt(1, pID);
		pstmt->executeUpdate();

		delete pstmt;
		d.success();
		PromptBox::successDelete();
	}
	else {
		d.danger();
		PromptBox::taskAbort();
	}

	delete pstmtPlace;
	delete resPlace;
}

// Completed 16/04/2020 90%
int AdminController::assignComplaint(sql::Connection* conn) {

	int success = -1;
	int cID;
	int sel;
	char cstr[19];

	string sql = "select * from complaint where respond= 'NOT PROCESS'";
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	int i = 0;

	pstmt = conn->prepareStatement(sql);
	//pstmt->setInt(1, NULL);
	res = pstmt->executeQuery();

	d.adminStatic();
	cout << "\nAssign Complaint" << endl;
	cout << "@Admin\n" << endl;
	cout << " C O M P L A I N T   D A T A\n" << endl;
	d.adminCOLOR();

	/*
	TextTable t('.', '|', '+');
	t.add("ID");
	t.add("Model");
	t.add("Serial Number");
	t.add("Respond");
	t.add("Received Data");
	t.endOfRow();
	*/
	cout << "\n-----------------------------------------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << "ID\t\t" << "Model\t\t" << "Serial Number\t\t" << "Respond\t\t" << "Total Days" ;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.adminTableData();
	Sleep(2000);
	while (res->next()) {
	
		string newDetalis = res->getString(9);
		//cout << "TESTER\t: " << newDetalis << endl;

		//char cstr[19];
		strcpy_s(cstr, sizeof newDetalis, newDetalis.c_str());
		//cout << "TESTER 2 \t: " << cstr << endl;
		//cout << "Data Type\t: " << typeid(cstr).name() << endl;

		//cout << "TESTER 3\t: " << masterCountDays(cstr) << endl;
		//int outNew = int(masterCountDays(cstr));

		cout << res->getString(1) << "\t\t" << res->getString(5) <<"\t\t" << res->getString(6) <<"\t\t\t" << res->getString(8) <<"\t" << masterCountDays(cstr) << endl;
		
		//cout << "TESTER 3\t: " << masterCountDays(cstr) << endl;
		//cout << "TESTER 3\t: " << outNew << endl;
		// t.endOfRow();
		i++;

		//delete cstr;
	}

	//t.setAlignment(2, TextTable::Alignment::LEFT);
	//cout << t;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	cout << "Total Not Process Complaint\t: " << i << endl;

	cout << endl;
	d.select();
	cout << "Select Complaint\t: " << flush;
	cin >> cID;


	system("cls");
	d.adminStatic();
	cout << "\nAssign Complaint" << endl;
	cout << "@Admin\n" << endl;
	d.adminCOLOR();

	cout << "A S S I G N   S T A F F" << endl;
	cout << "------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << "ID" << "\t\t\t" << "Full Name" << endl;
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	Sleep(2000);

	/* LIST STAFF */
	sql::PreparedStatement* pstmtUser;
	sql::PreparedStatement* pstmtUp;
	sql::ResultSet* resUser;

	pstmtUser = conn->prepareStatement("Select StaffID,fullname from staff");
	resUser = pstmtUser->executeQuery();
	d.adminTableData();
	while (resUser->next()) {

		//cout << res->getString(1) << "\t\t" << res->getString(2) << endl;
		cout << "[ " << resUser->getInt(1) << " ]" << "\t\t\t" << resUser->getString(2) << endl;
	}
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;

	d.select();
	cout << "\nSelect Staff to Complaint ID " << cID << "\t: " << flush;
	cin >> sel;

	string updateSQL = "update complaint set StaffID = ? where CompID = ?";

	pstmtUp = conn->prepareStatement(updateSQL);

	pstmtUp->setInt(1, sel);
	pstmtUp->setInt(2, cID);
	success = pstmtUp->executeUpdate();


	d.success();
	PromptBox::successAdd();
	delete pstmt;
	delete res;
	return success;
	d.adminCOLOR();

}

void AdminController::openPDF() {

	char filename[50];
	ifstream bucky;
	cin.getline(filename, 50);
	bucky.open(filename);

	if (!bucky.is_open()) {

		exit(EXIT_SUCCESS);
	}

	
}

void AdminController::displayGraph(sql::Connection* conn) {

	cout << endl << endl;
	d.adminStatic();
	cout << "\tE - M A I N T E N A N C E   G R A P H" << endl;
	d.adminCOLOR();
	cout << "\t--------------------------------------------------------------\n" << endl;
	int countUser = 0;
	int countStaff = 0;
	//cout << "\tA C T I V  E   U S E R S \n\n" << endl;

	// USER
	sql::PreparedStatement* pstmtUser;
	sql::ResultSet* resUser;

	string USER = "Select * from users";
	pstmtUser = conn->prepareStatement(USER);
	resUser = pstmtUser->executeQuery();

	while (resUser->next()) {

		countUser = countUser + 1;
	}
	d.adminStatic();
	cout << "\tUSER\t\t| " << flush;
	d.user();
	for (int i = 0; i < countUser; i++) {

		cout << "X";
	}

	cout << endl;

	// STAFF
	sql::PreparedStatement* pstmtStaff;
	sql::ResultSet* resStaff;

	string STAFF = "Select * from staff";
	pstmtStaff = conn->prepareStatement(STAFF);
	resStaff = pstmtStaff->executeQuery();

	while (resStaff->next()) {

		countStaff = countStaff + 1;
	}
	d.adminStatic();
	cout << "\tSTAFF\t\t| " << flush;
	d.staff();
	for (int i = 0; i < countStaff; i++) {

		cout << "X";
	}

	cout << endl;
	/* --------------------------------------------------- */

	//cout << "\n\n\tC O M P L A I N T \n" << endl;

	// NOT PROCESS
	d.adminStatic();
	cout << "\tNOT PROCESS\t| " << flush;
	d.notprocess();
	for (int i = 0; i < countComplaintAction(conn, "NOT PROCESS"); i++) {

		cout << "X";
	}

	cout << endl;


	//cout << countComplaintAction(conn, "IN PROCESS") << endl;
	// IN PROCESS
	d.adminStatic();
	cout << "\tIN PROCESS\t| " << flush;
	d.inprocess();
	for (int i = 0; i < countComplaintAction(conn, "IN PROCESS"); i++) {

		cout << "X";
	}

	cout << endl;
	// SOLVED
	d.adminStatic();
	cout << "\tSOLVED\t\t| " << flush;
	d.solve();
	for (int i = 0; i < countComplaintAction(conn, "SOLVED"); i++) {

		cout << "X";
	}

	cout << endl << endl;
	// GOALS
	// << "DATA 1 \t: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	//cout << "DATA 2 \t: XXXXXXXXXXXX" << endl;
	//cout << "DATA 3 \t: XXXXXXXXXXXXXXXXX" << endl;
	d.adminCOLOR();
	cout << "\t--------------------------------------------------------------" << endl;
	d.select();
	cout << "\tGraph Generated on : " << __DATE__ << " @ " << __TIME__;
	d.adminCOLOR();
	cout << "\n\t--------------------------------------------------------------\n" << endl;

	/*
	cout << "\n\n\t[ S U M M A R Y   R E P O R T ]\n\n" << endl;
	cout << "\tUSER\t\t: " << countUser << endl;
	cout << "\tSTAFF\t\t: " << countStaff << endl << endl;
	cout << "\t>> COMPLAINT\n" << endl;
	cout << "\tNOT PROCESS\t: " << countComplaintAction(conn, "NOT PROCESS") << endl;
	cout << "\tIN PROCESS\t: " << countComplaintAction(conn, "IN PROCESS") << endl;
	cout << "\tSOLVED\t\t: " << countComplaintAction(conn, "SOLVED") << endl;
	*/
	cout << "\n\n" << endl;
	system("pause");

}

void AdminController::currentUser(sql::Connection* conn, string purpose, string role) {

	cout << endl;
	d.adminStatic();
	cout <<  purpose <<" User" << endl;
	cout << "@" << role << endl << endl;
	d.adminCOLOR();

	cout << "C U R R E N T   U S E R" << endl;
	cout << "------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << setw(5) << "ID" << setw(15) << "Full Name" << endl;
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	d.adminTableData();
	Sleep(2000);

	// SQL SETUP
	sql::PreparedStatement* pstmtUser;
	sql::ResultSet* resUser;

	pstmtUser = conn->prepareStatement("Select UID,fullname from users");
	resUser = pstmtUser->executeQuery();
	while (resUser->next()) {

		cout << setw(5) << resUser->getInt(1) << setw(15) << resUser->getString(2) << endl;
	}

	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;

	delete pstmtUser;
	delete resUser;
}

void AdminController::currentStaff(sql::Connection* conn, string purpose, string role) {

	cout << endl;
	d.adminStatic();
	cout << purpose <<" Staff" << endl;
	cout << "@" << role << endl << endl;
	d.adminCOLOR();
	cout << "C U R R E N T   S T A F F" << endl;
	cout << "------------------------------------------------------" << endl;
	d.adminTableHeader();
	cout << setw(5) << "ID" << setw(15) << "Full Name" << endl;
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	Sleep(2000);

	/* LIST STAFF */
	sql::PreparedStatement* pstmtUser;
	sql::ResultSet* resUser;

	pstmtUser = conn->prepareStatement("Select StaffID,fullname from staff");
	resUser = pstmtUser->executeQuery();
	d.adminTableData();
	while (resUser->next()) {

		cout << setw(5) << resUser->getInt(1) << setw(15) << resUser->getString(2) << endl;
	}
	d.adminCOLOR();
	cout << "------------------------------------------------------" << endl;
	
	delete pstmtUser;
	delete resUser;
}

void AdminController::userdetails(sql::Connection* conn, int userID) {

	sql::PreparedStatement* pstmtUserDetails;
	sql::ResultSet* resUserDetails;

	pstmtUserDetails = conn->prepareStatement("Select * from users where UID = ?");
	pstmtUserDetails->setInt(1, userID);
	resUserDetails = pstmtUserDetails->executeQuery();

	if (resUserDetails->next()) {

		system("cls");
		d.adminStatic();
		cout << "\nUser Data" << endl;
		cout << "@Admin\n" << endl;
		d.adminCOLOR();
		cout << " Existing " << resUserDetails->getString("fullname") << " Data" << endl;
		cout << "------------------------------------------------------" << endl;
		d.adminTableData();
		cout << "[1]\tEmail\t\t: " << resUserDetails->getString("email") << endl;
		cout << "[2]\tContact\t\t: " << resUserDetails->getString("contact") << endl;
		cout << "[3]\tDepartment\t: " << resUserDetails->getString("department") << endl;
		cout << "[4]\tAddress\t\t: " << resUserDetails->getString("address") << endl;
		cout << "[5]\tState\t\t: " << resUserDetails->getString("state") << endl;
		cout << "[6]\tCountry\t\t: " << resUserDetails->getString("country") << endl;
		cout << "[7]\tPincode\t\t: " << resUserDetails->getString("pincode") << endl;
		d.adminCOLOR();
		cout << "------------------------------------------------------\n" << endl;
	}

	delete pstmtUserDetails;
	delete resUserDetails;
}

void AdminController::viewComplaintAction(sql::Connection* conn, string respond, string role) {

	int i = 0;
	char cstr[19];
	int  countDay = 0;
	int dueDay = 0;

	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	pstmt = conn->prepareStatement("select * from complaint where respond= ? ");
	pstmt->setString(1, respond);
	res = pstmt->executeQuery();

	cout << endl;
	d.adminStatic();
	cout << respond << " Complaint " << endl;
	cout << "@" << role << endl << endl;
	cout << " C O M P L A I N T   D A T A\n" << endl;
	d.adminCOLOR();

	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.adminTableHeader();
	cout << setw(5) << "ID" << setw(15) << "Model" << setw(15) << "Serial Number" << setw(15) << "Status" << setw(15) << "Total Days" << setw(15) << "Due Days" << endl;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	Sleep(2000);
	d.adminTableData();
	while (res->next()) {

		string newDetalis = res->getString(9);
		strcpy_s(cstr, sizeof newDetalis, newDetalis.c_str());
		countDay = masterCountDays(cstr);
		//dueDay = countDay - 3;


			


		//cout << setw(5) << res->getInt(1) << setw(15) << res->getString(5) << setw(15) << res->getString(6) << setw(15) << res->getString(8) << setw(15) << masterCountDays(cstr) << setw(15) << "SS"  << endl;
		cout << setw(5) << res->getInt(1) << setw(15) << res->getString(5) << setw(15) << res->getString(6) << setw(15) << res->getString(8) << setw(15) << countDay;
			//setw(15) << countDay - 3  << endl;
		if (countDay <= 3) {

			d.success();
			dueDay = 0;
			cout << setw(15) << dueDay << endl;
		}
		else if ((countDay - 3) <= 3) {

			d.select();
			dueDay = countDay - 3;
			cout << setw(15) << dueDay << endl;
		}
		else {
			if (res->getString(8) == "SOLVED") {

				d.success();
				cout << setw(15) << "Accomplish" << endl;
			}
			else {
				d.danger();
				dueDay = countDay - 3;
				cout << setw(15) << dueDay << endl;
			}
		}
		i++;
		d.adminTableData();
		countDay = 0;
		dueDay = 0;
	}
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------" << endl;
	d.select();
	cout << "Last Update on : " << __DATE__ << " @ " << __TIME__;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.info();
	cout << "Total " << respond <<" Complaint\t: " << i << endl;
	d.adminCOLOR();
	system("pause");
	delete pstmt;
	delete res;
}

void AdminController::viewAllComplaintAction(sql::Connection* conn, string role) {

	int i = 0;
	char cstr[19];
	int  countDay = 0;
	int dueDay = 0;

	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	pstmt = conn->prepareStatement("select * from complaint");
	res = pstmt->executeQuery();

	cout << endl;
	d.adminStatic();
	cout << "All Complaint " << endl;
	cout << "@" << role << endl << endl;
	cout << " C O M P L A I N T   D A T A\n" << endl;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.adminTableHeader();
	cout << setw(5) << "ID" << setw(15) << "Model" << setw(15) << "Serial Number" << setw(15) << "Status" << setw(15) << "Total Days" << setw(15) << "Due Days" << endl;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.adminTableData();
	Sleep(2000);
	while (res->next()) {

		string newDetalis = res->getString(9);
		strcpy_s(cstr, sizeof newDetalis, newDetalis.c_str());
		countDay = masterCountDays(cstr);

		//cout << setw(5) << res->getInt(1) << setw(15) << res->getString(5) << setw(15) << res->getString(6) << setw(15) << res->getString(8) << setw(15) << masterCountDays(cstr) << endl;
		cout << setw(5) << res->getInt(1) << setw(15) << res->getString(5) << setw(15) << res->getString(6) << setw(15) << res->getString(8) << setw(15) << countDay ;
		if (countDay <= 3) {

			d.success();
			dueDay = 0;
			cout << setw(15) << dueDay << endl;
		}
		else if ((countDay - 3) <= 3) {

			d.select();
			dueDay = countDay - 3;
			cout << setw(15) << dueDay << endl;
		}
		else {
			
			if (res->getString(8) == "SOLVED") {

				d.success();
				cout << setw(15) << "Accomplish" << endl;
			}
			else {
				d.danger();
				dueDay = countDay - 3;
				cout << setw(15) << dueDay << endl;
			}
		}
		i++;
		d.adminTableData();
		countDay = 0;
		dueDay = 0;
		i++;

	}
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------" << endl;
	d.select();
	cout << "Last Update on : " << __DATE__ << " @ " << __TIME__ ;
	d.adminCOLOR();
	cout << "\n-----------------------------------------------------------------------------------------\n" << endl;
	d.info();
	cout << "Total Complaint\t: " << i << endl;
	d.adminCOLOR();
	system("pause");
	delete pstmt;
	delete res;
}

int AdminController::countComplaintAction(sql::Connection* conn, string respond) {

	int countComplaint = 0;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

	pstmt = conn->prepareStatement("select * from complaint where respond= ? ");
	pstmt->setString(1, respond);
	res = pstmt->executeQuery();

	while (res->next()) {

		countComplaint = countComplaint + 1;
	}

	delete pstmt;
	delete res;
	return countComplaint;

}