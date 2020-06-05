#include "decoration.h"

#include <iostream>
#include <Windows.h>
using namespace std;

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

void decoration::bannerMontage() {
                    
    system("COLOR 09");
    cout << endl;
    cout << " ####### ####### #     # #    #                                                         " << endl;
    cout << " #          #    ##   ## #   #                                                          " << endl;
    cout << " #          #    # # # # #  #                                                           " << endl;
    cout << " #####      #    #  #  # ###                                                            " << endl;
    cout << " #          #    #     # #  #                                                           " << endl;
    cout << " #          #    #     # #   #                                                          " << endl;
    cout << " #          #    #     # #    #                                                         " << endl;
    cout << "" << endl;
    cout << " #     #    #    ### #     # ####### ####### #     #    #    #     #  #####  #######    " << endl;
    cout << " ##   ##   # #    #  ##    #    #    #       ##    #   # #   ##    # #     # #          " << endl;
    cout << " # # # #  #   #   #  # #   #    #    #       # #   #  #   #  # #   # #       #          " << endl;
    cout << " #  #  # #     #  #  #  #  #    #    #####   #  #  # #     # #  #  # #       #####      " << endl;
    cout << " #     # #######  #  #   # #    #    #       #   # # ####### #   # # #       #          " << endl;
    cout << " #     # #     #  #  #    ##    #    #       #    ## #     # #    ## #     # #          " << endl;
    cout << " #     # #     # ### #     #    #    ####### #     # #     # #     #  #####  #######    " << endl;
    cout << "" << endl;
    cout << "  #####  #     #  #####  ####### ####### #     #                                        " << endl;
    cout << " #     #  #   #  #     #    #    #       ##   ##                                        " << endl;
    cout << " #         # #   #          #    #       # # # #                                        " << endl;
    cout << "  #####     #     #####     #    #####   #  #  #                                        " << endl;
    cout << "       #    #          #    #    #       #     #                                        " << endl;
    cout << " #     #    #    #     #    #    #       #     #                                        " << endl;
    cout << "  #####     #     #####     #    ####### #     #                                        " << endl;
    cout << "" << endl;
    
    Sleep(3000);
    system("cls");
}

void decoration::select() {

    SetConsoleTextAttribute(color, 6);
}

void decoration::title(){

    SetConsoleTextAttribute(color,10);
}

void decoration::input() {

    SetConsoleTextAttribute(color, 9);
}

void decoration::info() {

    SetConsoleTextAttribute(color, 10);
}

void decoration::success() {

    SetConsoleTextAttribute(color, 10);
}

void decoration::danger() {

    SetConsoleTextAttribute(color, 4);
}

void decoration::defaultCOLOR() {

    SetConsoleTextAttribute(color, 15);
}

void decoration::adminCOLOR() {

    SetConsoleTextAttribute(color, 9);
}

void decoration::adminStatic() {

    SetConsoleTextAttribute(color, 15);
}

void decoration::adminTableHeader() {

    SetConsoleTextAttribute(color, 6);
}

void decoration::adminTableData() {

    SetConsoleTextAttribute(color, 15);
}

void decoration::adminInput() {

    SetConsoleTextAttribute(color, 7);
}

void decoration::staffCOLOR() {

    SetConsoleTextAttribute(color, 2);
}

void decoration::staffStatic() {
    SetConsoleTextAttribute(color, 15);
}

void decoration::staffInput() {

    SetConsoleTextAttribute(color, 6);
}

void decoration::staffTableHeader() {

    SetConsoleTextAttribute(color, 6);
}
void decoration::staffTableData() 
{
    SetConsoleTextAttribute(color, 15);
}

void decoration::userCOLOR() {

    SetConsoleTextAttribute(color, 7);
}

void decoration::userInput() {

    SetConsoleTextAttribute(color, 10);
}

void decoration::userStatic() {

    SetConsoleTextAttribute(color, 5);
}

void decoration::userTableData() {

    SetConsoleTextAttribute(color, 11);
}

void decoration::userTableHeader() {

    SetConsoleTextAttribute(color, 6);
}

void decoration::user() {

    SetConsoleTextAttribute(color, 5);
}

void decoration::staff() {

    SetConsoleTextAttribute(color, 8);
}

void decoration::notprocess() {

    SetConsoleTextAttribute(color, 4);
}

void decoration::inprocess() {

    SetConsoleTextAttribute(color, 6);
}

void decoration::solve() {

    SetConsoleTextAttribute(color, 10);
}