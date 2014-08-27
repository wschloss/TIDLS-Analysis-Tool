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
	cout << "\nLoader::importDataFromFile() is not implemented" << endl;
}