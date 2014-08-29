#include "Generator.h"

Generator::Generator(map<string,double> constantsMap) {
	equations = new EquationManager(constantsMap);
	cout << "\nGenerator successfully initialized, no implementation\n";
}