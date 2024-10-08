// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>

using namespace std;
#include "StudentDb.h"
#include "SimpleUI.h"
#include <sstream>
#include <string>
#include <fstream>

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main() {
	//TODO: Add your program code here
	cout << "StudentDataBase started." << endl << endl;

	StudentDb db;
	SimpleUI ui(db);
	ui.run();
	return 0;

}

