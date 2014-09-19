/*

This class is responsible for storing data for model constants
and data for fitting techniques.

Author: Walter Schlosser

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

		map<string,double> getConstants() {return constants;}
		map<double,vector<double> > getData() {return lifetimeData;}

	private:
		Loader* loader;
		// Key = name, value = constant value
		map<string,double> constants;
		// Key = deltaN, value = lifetime at different temps
		map<double,vector<double> > lifetimeData;
};