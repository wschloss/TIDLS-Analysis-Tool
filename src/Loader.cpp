#include "Loader.h"

Loader::Loader() {
}

void Loader::importConstantsFromFile(const string &fileName, map<string,double> &dataMap) {
	// Open file, read data, store in map
	ifstream input(fileName);
	if (!input) {
		cerr << "Error opening file: " << fileName << ".\n";
		exit(1);
	}

	// line and buffer string
	string definition, buffer;
	// string stream for splitting
	stringstream* stream = NULL;
	// vector of the resulting tokens
	vector<string> tokens;

	//THROWS OUT FIRST LINE OF TXT
	getline(input, definition);

	while (getline(input, definition)) {
		if (stream != NULL)
			delete stream;
		// stream of new line
		stream = new stringstream(definition);
		// split line
		while (*stream >> buffer) {
			tokens.push_back(buffer);
		}
		// add new constant to data map
		dataMap[tokens[0]] = atof(tokens[1].c_str());
		tokens.clear();
	}

	input.close();

}

void Loader::importDataFromFile(const string &fileName, map<double,vector<double> > &dataMap) {
	// Open file, read data, store in map
	ifstream input(fileName);
	if (!input) {
		cerr << "Error opening file: " << fileName << ".\n";
		exit(1);
	}

	// line and buffer string
	string definition, buffer;
	// string stream for splitting
	stringstream* stream = NULL;
	// vector of the resulting tokens
	vector<string> tokens;

	//THROWS OUT FIRST LINE OF TXT
	getline(input, definition);

	while (getline(input, definition)) {
		if (stream != NULL)
			delete stream;
		// stream of new line
		stream = new stringstream(definition);
		// split line
		while (*stream >> buffer) {
			tokens.push_back(buffer);
		}
		// add data (deltaN->t1, t2, t3, t4, ...) to map
		vector<double> lifetimes;
		for (int i = 1; i < tokens.size(); i++) {
			// Adds all lifetimes for different temps to the map key deltaN
			lifetimes.push_back(atof(tokens[i].c_str()));
		}
		dataMap[atof(tokens[0].c_str())] = lifetimes;
		
		tokens.clear();
	}

	input.close();

}