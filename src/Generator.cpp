#include "Generator.h"

Generator::Generator(map<string,double> constantsMap) {
	equations = new EquationManager(constantsMap);

	NA = 0;
	Nt = 0;
	Et = 0;
	sigmaN = 0;
	sigmaP = 0;

	minDeltaN = 0;
	maxDeltaN = 0;
	deltaNStep = 0;
	minTemp = 0;
	maxTemp = 0;
	tempStep = 0;

	promptForDefectProperties();
	promptForRangeProperties();
	generateData();
	printDataToFile();
}

void Generator::promptForDefectProperties() {
	cout << "\nYou must define desired sample properties to simulate data\n";

	cout << "Enter a value for NA: ";
	cin >> NA;
	cout << "Enter a value for Nt: ";
	cin >> Nt;
	cout << "Enter a value for Et: ";
	cin >> Et;
	cout << "Enter a value for sigmaN: ";
	cin >> sigmaN;
	cout << "Enter a value for sigmaP: ";
	cin >> sigmaP;
}

void Generator::promptForRangeProperties() {
	cout << "\nYou must define the range to generate data for\n";

	cout << "Enter a minimum value for deltaN: ";
	cin >> minDeltaN;
	cout << "Enter a maximum value for deltaN: ";
	cin >> maxDeltaN;
	cout << "Enter a step size for deltaN: ";
	cin >> deltaNStep;
	cout << "Enter a minimum value for temperature: ";
	cin >> minTemp;
	cout << "Enter a maximum value for temperature: ";
	cin >> maxTemp;
	cout << "Enter a step size for temperature: ";
	cin >> tempStep;
}

void Generator::generateData() {
	// Outer for loop for deltaN
	for (double i = minDeltaN; i <= maxDeltaN; i += deltaNStep) {
		vector<double> lifetimes;
		// Inner for loop for temps
		for (double j = minTemp; j <= maxTemp; j += tempStep) {
			// Create row of lifetime at different temps
			lifetimes.push_back(equations->tSRH(j,i,NA,Nt,Et,sigmaN,sigmaP));
		}
		// Put a row of data
		generatedData[i] = lifetimes;
	}
}

void Generator::printDataToFile() {
	// Ask for file name
	string filename;
	cout << "\nEnter a filename to export data (if file already exists, data is overwritten): ";
	cin >> filename;

	// Open stream and print properties of data on first line
	ofstream output(filename);
	if (!output) {
		cerr << "\nError creating export file.\n";
		exit(1);
	}
	output << "NA=" << NA << " Nt=" << Nt << " Et=" << Et << " sigmaN=" << sigmaN << " sigmaP="
			<< sigmaP << " deltaN:[" << minDeltaN << "," << maxDeltaN << "] deltaNStep=" << deltaNStep
			<< " temp:[" << minTemp << "," << maxTemp << "] tempStep=" << tempStep << endl;

	// Print out the contents of the generated data map
	typedef map<double,vector<double> >::iterator it_type;
	for (it_type it = generatedData.begin(); it != generatedData.end(); it++) {
		output << it->first;
		for (int i = 0; i < it->second.size(); i++) {
			output << " " << it->second[i];
		}
		output << endl;
	} 


	output.close();
}