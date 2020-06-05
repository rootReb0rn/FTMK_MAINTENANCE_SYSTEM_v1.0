#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
#include <cmath>
#include "decoration.h"
//#include "pdf.h"

/* SQL Lib */
#include <cppconn/driver.h>
#include <cppconn/connection.h>

using namespace std;

class AdminController
{
private:
	decoration d;

	public:
		int countDay(int year, int month, int day); // DONE
		int masterCountDays(char compDate[19]); // IN PROCESS
		int addUser(sql::Connection* conn, string adminName,int adminID);  // DONE
		int updateUser(sql::Connection* conn,string adminName,int adminID); // DONE 
		void deleteUser(sql::Connection* conn); // 80% DONE
		void viewUser(sql::Connection* conn); // DONE
		int addStaff(sql::Connection* conn,string adminName, int adminID); // DONE
		int updateStaff(sql::Connection* conn,string adminName); // DONE
		void deleteStaff(sql::Connection* conn);
		void viewStaff(sql::Connection* conn);
		int addComplaint(sql::Connection* conn);
		int updateComplaint(sql::Connection* conn);
		void deleteComplaint(sql::Connection* conn);
		void viewComplaint(sql::Connection* conn);
		int addPlace(sql::Connection* conn);
		int updatePlace(sql::Connection* conn);
		void deletePlace(sql::Connection* conn);
		int assignComplaint(sql::Connection* conn);
		void openPDF();
		void displayGraph(sql::Connection* conn);
		
		// line 605
		// ADD-ONS
		void currentUser(sql::Connection* conn, string purpose, string role);
		void currentStaff(sql::Connection* conn, string purpose, string role);
		void userdetails(sql::Connection* conn, int userID);
		void viewComplaintAction(sql::Connection* conn, string respond,string role);
		void viewAllComplaintAction(sql::Connection* conn, string role);
		int countComplaintAction(sql::Connection* conn, string respond);
};

