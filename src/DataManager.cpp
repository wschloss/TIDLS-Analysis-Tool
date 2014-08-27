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

}

void DataManager::loadData() {
	// prompt user for file name
	string fileName;
	cout << "\nEnter the file name containing data for lifetime values: ";
	cin >> fileName;

	loader->importDataFromFile(fileName, lifetimeData);

}