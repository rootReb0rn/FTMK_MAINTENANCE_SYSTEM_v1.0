#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "decoration.h"

using namespace std;



class PromptBox {

private: 


public :

	void static successAdd() {

		system("cls");
		cout << "\nSuccessfully Added" << endl;
		Sleep(3000);
		system("cls");
	}

	void static successUpdate() {

		system("cls");
		cout << "\nSuccessfully Updated" << endl;
		Sleep(3000);
		system("cls");
	}

	void static successDelete() {

		system("cls");
		cout << "\nSuccessfully Delete" << endl;
		Sleep(3000);
		system("cls");
	}

	void static successRegister() {


		system("cls");
		cout << endl;
		cout << " +-+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+" << endl;
		cout << " |S|u|c|c|e|s|s|f|u|l|l|y| |R|e|g|i|s|t|e|r|" << endl;
		cout << " +-+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+" << endl;
		Sleep(3000);
		system("cls");
	}

	void static unauthorized() {


		system("cls");
		cout << endl;
		cout << " +-+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+" << endl;
		cout << " |U|n|a|u|t|h|o|r|i|z|e|d| |A|c|c|e|s|s|" << endl;
		cout << " +-+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+" << endl;
		Sleep(3000);
		system("cls");
	}

	void static exiting() {

		system("cls");
		cout << endl;
		cout << " +-+-+-+-+-+-+-+ " << endl;
		cout << " |E|x|i|t|i|n|g| " << endl;
		cout << " +-+-+-+-+-+-+-+ " << endl;
		Sleep(3000);
		system("cls");
	}

	void static taskAbort() {

		system("cls");
		cout << endl;
		cout << " +-+-+-+-+ +-+-+-+-+-+ " << endl;
		cout << " |T|a|s|k| |A|b|o|r|t| " << endl;
		cout << " +-+-+-+-+ +-+-+-+-+-+ " << endl;
		Sleep(3000);
		system("cls");
	}
};