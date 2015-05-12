#include <iostream>
#include "Analyzer/Analyzer.h"
#include "Generator/Generator.h"
#include "Loader/Loader.h"
#include "DataManager/DataManager.h"

using namespace std;


int main(int argc, char const *argv[]) {

	//User option variables
	bool done = false;
	int choice = -1;

	// Generates simulated data, exports to txt file
	Generator* generator = NULL;
	// Analyzes data imported from txt file
	Analyzer* analyzer = NULL;
	// Stores model data, constants and data for the fits
	DataManager* dataManager = NULL;

	cout << endl;
	cout << "/********* TIDLS Analyzer *********/" << endl;
	
	// Main loop
	while(!done) {
		// Prompt user to select option
		while (!(choice > -1 && choice < 4)) {
			cout << endl;
			cout << "(1) Load constants and/or data\n";
			cout << "(2) Generate perfect data from theory\n";
			cout << "(3) Analyze data\n";
			cout << "(0) Quit\n";
			cout << endl;
			cout << "Select an option: ";
			cin >> choice;
			if (cin.fail()){
				cin.clear();
				cin.ignore(100, '\n'); //ignore 100 characters or get to the end of the line.
				cout << "\nInput failed, try again:" << endl;
			}
		}
		// Perform desired operations
		switch(choice) {
			case 0:
			done = true;
			break;

			case 1:
			choice = -1;
			// Reinitialize dataManager
			if (dataManager != NULL)
				delete dataManager;
			// Prompts for data files
			dataManager = new DataManager();
			break;

			case 2:
			choice = -1;
			if (dataManager == NULL || dataManager->getConstants().size() == 0) {
				cout << "\nYou must first load constants for simulation\n";
				break;
			}
			if (generator != NULL)
				delete generator;
			// Will ask about output file name, temp range, etc.
			generator = new Generator(dataManager->getConstants());
			break;

			case 3:
			choice = -1;
			if (dataManager == NULL || dataManager->getConstants().size() == 0 || dataManager->getData().size() == 0) {
				cout << "\nYou must first load constants AND data for analysis.\n";
				break;
			}
			if (analyzer != NULL)
				delete analyzer;
			analyzer = new Analyzer(dataManager->getConstants(), dataManager->getData());
			break;
		}


	}

	// Release memory
	if (generator != NULL) {
		delete generator;
	}
	if (analyzer != NULL) {
		delete analyzer;
	}
	if (dataManager != NULL) {
		delete dataManager;
	}

	return 0;
}