#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
#include <cmath>
#include <ctime>
#include "pdf.h"

/* SQL LIB */
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

static bool getLines(
    const string& fileName,
    vector<string>& lines,
    string& errMsg
)
{
    ifstream in;

    in.open(fileName.c_str(), ios::binary);

    if (!in)
    {
        errMsg = "Could not open: [" + fileName + "]";
        return(false);
    }

    string line = "";

    for (;;)
    {
        char c = (char)in.get();

        if (in.eof())
        {
            if (line != "")
                lines.push_back(line);

            break;
        }

        line += c;

        if (c == '\n')
        {
            lines.push_back(line);
            line = "";
        }
    }

    in.close();

    return(true);
}

// ---------------------------------------------------
// Draw 'theText' at: [x, y] (using the specified
// font and font size) with a box around it
// ---------------------------------------------------

static void drawBoundedText(
    const string& theText,
    int           x,
    int           y,
    PDF::Font     theFont,
    int           fontSize,
    PDF& p
)
{
    p.setFont(theFont, fontSize);

    p.showTextXY(theText, x, y);

    int width = PDF::stringWidth(
        theFont, fontSize, theText
    );

    int offset = (int)(0.4 * fontSize + 0.5);

    p.drawRect(x, y - offset, width, fontSize + offset);
}



static void myPDF(PDF& p,sql::Connection* conn) {

	p.setFont(PDF::TIMES, 32);

	string h = "FTMK MAINTENANCE SYSTEM";
	vector<string> sv = p.wrapText(h, 512, true);

	for (int i = 0, n = sv.size(); i < n; i++) {

		p.showTextXY(sv[i], 50, 700);
	}
	p.showTextXY("_______________________________", 55, 690);

    ostringstream out1;
    ostringstream out2;
    ostringstream out3;
    ostringstream out4;
    ostringstream out5;
    ostringstream out6;


    sql::PreparedStatement* pstmt1;
    sql::ResultSet* res1;
    pstmt1 = conn->prepareStatement("SELECT COUNT('StaffID') FROM staff");
    res1 = pstmt1->executeQuery();
    if (res1->next()) {

        out1 << "Total Staff\t\t: " << res1->getString(1);
    }

    string totalStaff = out1.str();


    sql::PreparedStatement* pstmt2;
    sql::ResultSet* res2;
    pstmt2 = conn->prepareStatement("SELECT COUNT('UID') FROM users");
    res2 = pstmt2->executeQuery();
    if (res2->next()) {

        out2 << "Total User\t\t: " << res2->getString(1);
    }

    string totalUser = out2.str();

    string compTitle = "Complaint Data";
    string line = "____________________";

    sql::PreparedStatement* pstmt3;
    sql::ResultSet* res3;
    pstmt3 = conn->prepareStatement("SELECT COUNT('respond') FROM complaint where respond='NOT PROCESS'");
    res3 = pstmt3->executeQuery();
    if (res3->next()) {

        out3 << "NOT PROCESS\t\t: " << res3->getString(1);
    }

    string notProcess = out3.str();

    sql::PreparedStatement* pstmt4;
    sql::ResultSet* res4;
    pstmt4 = conn->prepareStatement("SELECT COUNT('respond') FROM complaint where respond='IN PROCESS'");
    res4 = pstmt4->executeQuery();
    if (res4->next()) {

        out4 << "IN PROCESS\t\t: " << res4->getString(1);
    }

    string inProcess = out4.str();


    sql::PreparedStatement* pstmt5;
    sql::ResultSet* res5;
    pstmt5 = conn->prepareStatement("SELECT COUNT('respond') FROM complaint where respond='SOLVED'");
    res5 = pstmt5->executeQuery();
    if (res5->next()) {

        out5 << "SOLVED\t\t: " << res5->getString(1);
    }

    string solved = out5.str();

    out6 << "Report Generate :\t" << __DATE__ << " @ " << __TIME__ ;
    string date = out6.str();

    p.setFont(PDF::TIMES, 24);
    p.showTextXY(totalStaff, 50, 620);
    p.showTextXY(totalUser, 50, 580);
    p.showTextXY(compTitle, 50, 520);
    p.showTextXY(line, 50, 515);
    p.showTextXY(notProcess, 50, 475);
    p.showTextXY(inProcess, 50, 435);
    p.showTextXY(solved, 50, 395);
    p.showTextXY(line, 50, 385);
    p.showTextXY(date, 50, 335);
    //p.showTextXY("_______________________________", 60, 690);



    delete pstmt1;
    delete pstmt2;
    delete pstmt3;
    delete pstmt4;
    delete pstmt5;
    delete res1;
    delete res2;
    delete res3;
    delete res4;
    delete res5;
}



static void printPDF(string filename,sql::Connection*conn ) {

    PDF p;
    string errMsg;

    cout << "Creating File : [ " << filename << " ]" << endl;

    myPDF(p,conn);

    if (!p.writeToFile(filename, errMsg)) {

        cout << errMsg << endl;
    }
    else {

        cout << "File Successfully " << endl;
    }
}