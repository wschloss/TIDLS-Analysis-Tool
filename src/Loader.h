/*

This class is responsible for loading model data from a
txt file specified by the user.  Currently, model constants
will be loaded from txt.  It may also be used to load and
contain the data for analysis in the class Analyzer.

*/

#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Loader {
public:
	Loader();

	void importConstantsFromFile(const string &fileName, map<string,double> &dataMap);
	void importDataFromFile(const string &fileName, vector< vector<double> > &lifetimeData);

private:

};