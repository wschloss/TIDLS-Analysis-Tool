/*

This class is responsible for generating simulated data
as well as exporting it to a txt file for further analysis

*/

#pragma once

#include "EquationManager.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Generator {
public:
	Generator(map<string,double>& constantsMap);
	void promptForDefectProperties();
	void promptForRangeProperties();
	void generateData();
	void printDataToFile();

private:
	EquationManager* equations;
	map<double,vector<double> > generatedData;
	// Variables necessary to define a defect for data generation
	double NA, Nt, Et, sigmaN, sigmaP;
	// Define range of data generation
	double minPowerN;
	double maxPowerN;
	double minTemp;
	double maxTemp;
	double tempStep;
};