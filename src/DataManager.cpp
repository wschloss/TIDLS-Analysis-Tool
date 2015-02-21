#include "DataManager.h"


DataManager::DataManager() {
	loader = new Loader();
	loadConstants();
	loadData();
}

DataManager::~DataManager() {
	if (loader != NULL)
		delete loader;
}

void DataManager::loadConstants() {
	// prompt user for file name
	string fileName;
	cout << "\nEnter the file name containing values for constants (or 0 to skip): ";
	getline(cin, fileName); //Consume \n char, cin.sync() is being weird right now

	loadFile(fileName);

	if (fileName == "0") {
		cout << "\nNo values for constants were loaded.\n";
		return;
	}

	loader->importConstantsFromFile(fileName, constants);

	//PRINTS MAP OF CONSTANTS FOR DEBUGGING
	typedef map<string,double>::iterator it_type;
	cout << "\nThe following constants were loaded:\n " << endl;
	for (it_type it = constants.begin(); it != constants.end(); it++) {
		cout << it->first << " = " << it->second << endl;
	}

}

void DataManager::loadData() {
	// prompt user for file name
	string fileName;
	cout << "\nEnter the file name containing data for lifetime values (or 0 to skip): ";
	
	loadFile(fileName);

	if (fileName == "0") {
		cout << "\nNo data for lifetimes were loaded.\n";
		return;
	}

	loader->importDataFromFile(fileName, lifetimeData);

	// Number of temps data taken at
	int tempLength = lifetimeData.size()/2;
	// Number of measurements in lifetimeData
	int mLength = lifetimeData[0].size();


	/* Rewrite for new data format

	//PRINTS DATA IN ORIGINAL FORMAT FOR DEBUGGING
	cout << "\nThe following data was loaded:\n " << endl;
	for (int i = 0; i < mLength; i++) {
		cout << "deltaN = " << lifetimeData[0][i] << ", ";
		for (int j = 1; j < tempLength; j++) {
			cout << "t" << j << " = " << lifetimeData[j][i] << ", ";
		}
		cout << endl;
	}
	*/

}

void DataManager::loadFile(string &fileName) {
	//cin.sync()
	getline(cin, fileName); //Consume \n char

	if (fileName == "0") { return; }

	ifstream ifile(fileName);
	if (!ifile) {
		cerr << "Error opening file: " << fileName << endl;
		cout << "\nPlease enter the correct file name (or 0 to skip): ";
		loadFile(fileName);
	}

}