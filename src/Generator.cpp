#include "Generator.h"

Generator::Generator(map<string,double>& constantsMap) {
	equations = new EquationManager(constantsMap);

	promptForRangeProperties();
	createDefects();
	createSample();
	printDataToFile();
}

void Generator::promptForRangeProperties() {
	minPowerN = 0;
	maxPowerN = 0;
	minTemp = 0;
	maxTemp = 0;
	tempStep = 0;

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

void Generator::createDefects() {
	// Prompt for defect, generate data for that defect, repeat...
	int choice;

	/* 
	Note to self:
	I place recursion at the end of both functions, instead of
	putting both recursive loops within this function. This is
	so we don't have to keep stepping out of a recursive loop
	when we're done.
	*/

	promptForDefectProperties();

	yesNoPrompt("\nWould you like to add another defect?\n", choice);
	if (choice == 1) createDefects();
}

void Generator::promptForDefectProperties() {
	int choice;
	string filename;

	NA = 0;
	Nt = 0;
	Et = 0;
	sigmaN = 0;
	sigmaP = 0;

	cout << "\nYou must define desired sample properties to simulate data\n";

	cout << "\nThe following are currently available:\n";
	cout << "(1) defect\n";
	cout << "(2) defect_textbook\n";
	cout << "(3) defect_Cr\n";
	cout << "(4) defect_CrB\n";
	cout << endl;

	cout << "Enter a choice: ";
	
	cin >> choice;
	switch(choice) {
		case 1:
		filename = "defect.txt";
		break;
		case 2:
		filename = "defect_textbook.txt";
		break;
		case 3:
		filename = "defect_Cr.txt";
		break;
		case 4:
		filename = "defect_CrB.txt";
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

	// For recording the file name:
	string defectName = filename;

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

	yesNoPrompt("\nIs this the defect you want?\n", choice);
	if (choice == 1) {
		generatedData.push_back(generateData());
		defectsList.push_back(defectName);
	}
	else if (choice == 2) promptForDefectProperties();
}

void Generator::yesNoPrompt(string query, int &choice) {

	cout << query;
	cout << "(1) Yes\n";
	cout << "(2) No\n";
	cout << endl;

	cout << "Enter a choice: ";

	cin >> choice;

	if (choice != 1 && choice != 2) {
		yesNoPrompt("\nInvalid, try again:\n", choice);
	}
	else; // "Breaks" out of recursive function
}

map<double, vector<double> > Generator::generateData() {
	map<double, vector<double> > data;

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
			data[k*pow(10,i)] = lifetimes;

		}
	}

	return data;
}

void Generator::createSample() {
	// Assumes equal concentrations of defects
	if (!finalData.empty()) {
		finalData.clear();
	}

	int n = generatedData.size();
	if (n > 1) {
		// Add lifetimes "in parallel"
		typedef map<double, vector<double> >::iterator it_type;
		// Iterate through each deltaN:
		for (it_type it = generatedData[0].begin(); it != generatedData[0].end(); it++) {
			// Iterate through each temperature:
			for (int j = 0; j < it->second.size(); j++) {
				double lifetime = 0;
				// Iterate through all defects:
				for (int i = 0; i < n; i++) {
					lifetime += 1 / generatedData[i][it->first][j];
				}
				finalData[it->first].push_back(1 / lifetime);
			}
		}
	}
	else if (n == 1) {
		finalData = generatedData[0];
	}
}

// REWRITE TO MATCH NEW DATA FORMAT
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

	output << "Defects used:[";
	for (int i = 0; i < defectsList.size(); i++) {
		output << defectsList[i] << ",";
	}

	output << "] deltaNPowers:[" << minPowerN << "," << maxPowerN << "] temp:[" << minTemp << "," 
		<< maxTemp << "] tempStep=" << tempStep << endl;

	// Print out the contents of the generated data map
	typedef map<double,vector<double> >::iterator it_type;
	for (it_type it = finalData.begin(); it != finalData.end(); it++) {
		output << it->first;
		for (int i = 0; i < it->second.size(); i++) {
			output << " " << it->second[i];
		}
		output << endl;
	} 


	output.close();
}