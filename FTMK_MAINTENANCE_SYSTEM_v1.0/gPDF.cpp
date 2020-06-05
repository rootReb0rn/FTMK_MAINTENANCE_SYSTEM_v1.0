/**************************
 * Headers
 **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <complex>
#include <cmath>
#include "pdf.h"


 /**************************
  * Using Declarations
  **************************/

using std::ostringstream;
using std::ifstream;
using std::complex;
using std::cout;
using std::endl;
using std::ios;

/**************************
 * Local Functions
 **************************/

static void demoOne(PDF& p)
{
    p.setFont(PDF::TIMES, 32);

    string h = "FTMK MAINTENANCE SYSTEM";
    vector<string> sv = p.wrapText(h, 512, true);

    for (int i = 0, n = sv.size(); i < n; i++)
    {

        p.showTextXY(sv[i], 50, 700);


    }
    p.showTextXY("_______________________________", 55, 690);


    string totalStaff = "Total Staff\t\t: 20";
    string totalUser = "Total User\t\t: 76";
    string compTitle = "Complaint Data";
    string line = "____________________";
    string notProcess = "NOT PROCESS\t\t: 12";
    string inProcess = "IN PROCESS\t\t: 50";
    string solved = "SOLVED\t\t: 100";
    p.setFont(PDF::TIMES, 24);
    p.showTextXY(totalStaff, 50, 620);
    p.showTextXY(totalUser, 50, 580);
    p.showTextXY(compTitle, 50, 520);
    p.showTextXY(line, 50, 515);
    p.showTextXY(notProcess, 50, 475);
    p.showTextXY(inProcess, 50, 435);
    p.showTextXY(solved, 50, 395);

    // cout << endl;

}

static void demoTwo(PDF& p)
{
    p.setFont(PDF::TIMES, 32);

    string h = "FTMK MAINTENANCE SYSTEM";
    vector<string> sv = p.wrapText(h, 512, true);

    for (int i = 0, n = sv.size(); i < n; i++)
    {

        p.showTextXY(sv[i], 50, 700);


    }
    p.showTextXY("_______________________________", 55, 690);


    string totalStaff = "Total Staff\t\t: 20";
    string totalUser = "Total User\t\t: 76";
    string compTitle = "Complaint Data";
    string line = "____________________";
    string notProcess = "NOT PROCESS\t\t: 12";
    string inProcess = "IN PROCESS\t\t: 50";
    string solved = "SOLVED\t\t: 100";
    p.setFont(PDF::TIMES, 24);
    p.showTextXY(totalStaff, 50, 620);
    p.showTextXY(totalUser, 50, 580);
    p.showTextXY(compTitle, 50, 520);
    p.showTextXY(line, 50, 515);
    p.showTextXY(notProcess, 50, 475);
    p.showTextXY(inProcess, 50, 435);
    p.showTextXY(solved, 50, 395);

    // cout << endl;

}



/**************************
 * Main
 **************************/

static int testMain()
{
    typedef void (*DemoFunction)(PDF &);

    DemoFunction functions[] =
    {
       demoOne,demoTwo
    };

    int n = sizeof(functions) / sizeof(functions[0]);

    for (int i = 3; i < n; i++)
    {
        ostringstream out;

        out << "example-" << i << ".pdf";

        string fileName = out.str();

        cout << "-----------------------------------------" << "\n";
        cout << "Creating File: [" << fileName << "]" << "\n";
        cout << "-----------------------------------------" << "\n";

        PDF pdf;

        functions[i](pdf);


        string errMsg;

        if (!pdf.writeToFile(fileName, errMsg))
        {
            cout << errMsg << endl;
        }
        else
        {
            cout << "(File Successfully Written)" << endl;
        }
    }
    
 
    //cout << endl;
 //}

    return(0);
}
