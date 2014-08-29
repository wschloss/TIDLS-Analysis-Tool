/*

This class is responsible for generating simulated data
as well as exporting it to a txt file for further analysis

Author: Walter Schlosser

*/

#pragma once

#include "EquationManager.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Generator {
public:
	Generator(map<string,double> constantsMap);

private:
	EquationManager* equations;
};