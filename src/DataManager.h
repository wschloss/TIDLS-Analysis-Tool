/*

This class is responsible for storing data for model constants
and data for fitting techniques.

*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include "Loader.h"

using namespace std;

class DataManager {
public:
	DataManager();
	~DataManager();

	void loadConstants();
	void loadData();

	map<string,double>& getConstants() {return constants;}
	vector< vector<double> >& getData() {return lifetimeData;}

private:
	Loader* loader;
		// Key = name, value = constant value
	map<string,double> constants;

		// Data categorized by temps, with the first vector being deltaN
		// i.e. { {deltaN1, deltaN2,...}, {temp11, temp12,...}, {temp21, temp22,...},... }
	vector < vector<double> > lifetimeData;
};