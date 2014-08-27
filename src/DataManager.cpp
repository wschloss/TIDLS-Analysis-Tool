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
	cout << "\nEnter the file name containing values for constants: ";
	cin >> fileName;

	loader->importConstantsFromFile(fileName, constants);

	//PRINTS MAP OF CONSTANTS FOR DEBUGGING
	typedef map<string,double>::iterator it_type;
	cout << "The following constants were loaded:\n " << endl;
	for (it_type it = constants.begin(); it != constants.end(); it++) {
		cout << it->first << " = " << it->second << endl;
	}

}

void DataManager::loadData() {
	// prompt user for file name
	string fileName;
	cout << "\nEnter the file name containing data for lifetime values: ";
	cin >> fileName;

	loader->importDataFromFile(fileName, lifetimeData);

	//PRINTS MAP OF DATA FOR DEBUGGING
	typedef map<double,vector<double> >::iterator it_type;
	cout << "The following data was loaded:\n " << endl;
	for (it_type it = lifetimeData.begin(); it != lifetimeData.end(); it++) {
		cout << "deltaN = " << it->first << ", ";
		//Print out vector of lifetimes
		for (int i = 0; i < (it->second).size(); i++) {
			cout << "t" << i+1 << " = " << it->second[i] << ", ";
		}
		
		cout << endl;
	}

}