#pragma once

/* Add_On Lib*/
#include <string>
#include "decoration.h"

/* SQL Lib*/
#include <cppconn/driver.h>
#include <cppconn/connection.h>

using namespace std;

class login
{
private:
	decoration d;
public:
	void loginController(sql::Connection *conn);
	bool multiLogin(string usr, string pwd, sql::Connection *conn);
	bool registerUser(sql::Connection* conn);
};

