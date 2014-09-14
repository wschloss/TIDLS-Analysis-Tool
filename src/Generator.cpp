#include "Generator.h"

Generator::Generator(map<string,double> constantsMap) {
	equations = new EquationManager(constantsMap);

	NA = 0;
	Nt = 0;
	Et = 0;
	sigmaN = 0;
	sigmaP = 0;

	minPowerN = 0;
	maxPowerN = 0;
	minTemp = 0;
	maxTemp = 0;
	tempStep = 0;

	promptForDefectProperties();
	promptForRangeProperties();
	generateData();
	printDataToFile();
}

void Generator::promptForDefectProperties() {
	int choice;
	string filename;

	cout << "\nYou must define desired sample properties to simulate data\n";

	cout << "\nThe following are currently available:\n";
	cout << "(1) defect\n" << endl;

	cout << "Enter a choice: ";
	
	cin >> choice;
	switch(choice) {
		case 1:
		filename = "defect.txt";
		break;
		default:
		filename = "defect.txt";
		break;
	}

	//read file
	ifstream input(filename);
	if (!input) {
		cerr << "\nError opening file.\n";
		exit(1);
	}
	//Throw out first line
	getline(input, filename);
	input >> NA;
	input >> Nt;
	input >> Et;
	input >> sigmaN;
	input >> sigmaP;

	cout << "\nDefect properties read:\n";
	cout << "NA: " << NA << endl;
	cout << "Nt: " << Nt << endl;
	cout << "Et: " << Et << endl;
	cout << "sigmaN: " << sigmaN << endl;
	cout << "sigmaP: " << sigmaP << endl;
}

void Generator::promptForRangeProperties() {
	cout << "\nYou must define the range to generate data over\n";

	cout << "Enter a minimum power of deltaN: ";
	cin >> minPowerN;
	cout << "Enter a maximum power or deltaN: ";
	cin >> maxPowerN;
	cout << "Enter a minimum value for temperature: ";
	cin >> minTemp;
	cout << "Enter a maximum value for temperature: ";
	cin >> maxTemp;
	cout << "Enter a step size for temperature: ";
	cin >> tempStep;
}

void Generator::generateData() {
	// Outer for loop for deltaN
	for (double i = minPowerN; i <= maxPowerN; i++) {
		// 10 values for this power
		for (double k = 1; k < 10; ++k) {
			vector<double> lifetimes;
			// Inner for loop for temps
			for (double j = minTemp; j <= maxTemp; j += tempStep) {
			// Create row of lifetime at different temps
				lifetimes.push_back(equations->tSRH(j,k*pow(10,i),NA,Nt,Et,sigmaN,sigmaP));
			}
			// Put a row of data
			generatedData[k*pow(10,i)] = lifetimes;

		}
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
	<< sigmaP << " deltaNPowers:[" << minPowerN << "," << maxPowerN << "] temp:[" << minTemp << "," 
		<< maxTemp << "] tempStep=" << tempStep << endl;

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