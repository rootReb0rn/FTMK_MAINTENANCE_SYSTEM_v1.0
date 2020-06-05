#pragma once
#include <string>
#include "decoration.h"
/* SQL Lib */
#include <cppconn/driver.h>
#include <cppconn/connection.h>

using namespace std;

class StaffController
{
	public:
		int addUser(sql::Connection* conn, string staffName);
		int updateUser(sql::Connection* conn, string staffName);
		void deleteUser(sql::Connection* conn);
		void viewUser(sql::Connection* conn);
		void resetPassword(sql::Connection* conn);
		void viewComplaint(sql::Connection* conn, string staffName);    // Backup 
		int viewComplaint(sql::Connection* conn, string staffName , int staffID, string typeComplaint, string status);
		void selectedComplaintDetails(sql::Connection* conn, int staffID,int CompID);
		void receivedComplaint(sql::Connection* conn, string staffName, int staffID);
		void pendingComplaint(sql::Connection* conn, string staffName, int staffID);
		void solvedComplaint(sql::Connection* conn, string staffName, int staffID);
		//void receivedComplaint(sql::Connection* conn, string staffName);
private:
	decoration d;
};

