#include <iostream>
#include "Analyzer.h"
#include "Generator.h"
#include "Loader.h"

using namespace std;


int main(int argc, char const *argv[]) {

	//User option variables
	bool done = false;
	int choice = -1;

	// Generates simulated data, exports to txt file
	Generator* generator = NULL;
	// Analyzes data imported from txt file
	Analyzer* analyzer = NULL;
	// Loads user model data (currently loads constants)
	Loader* loader = NULL;

	cout << endl;
	cout << "/********* TIDLS Analyzer *********/" << endl;

	// Main loop
	while(!done) {
		// Prompt user to select option
		while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
			cout << endl;
			cout << "Enter 1 to load constants, 2 to generate simulated data, or 3 to analyze data (0 to quit): ";
			cin >> choice;
		}
		// Perform desired operations
		switch(choice) {
			case 0:
			done = true;
			break;

			case 1:
			choice = -1;
			cout << "\nThe desired option is not yet implemented" << endl;
			break;

			case 2:
			choice = -1;
			cout << "\nThe desired option is not yet implemented" << endl;
			break;

			case 3:
			choice = -1;
			cout << "\nThe desired option is not yet implemented" << endl;
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
	if (loader != NULL) {
		delete loader;
	}

	return 0;
}