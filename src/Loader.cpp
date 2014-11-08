#include "Loader.h"

Loader::Loader() {
}

void Loader::importConstantsFromFile(const string &fileName, map<string,double> &dataMap) {
	// Open file, read data, store in map
	ifstream input(fileName);
	if (!input) {
		cerr << "Error opening file: " << fileName << "\n";
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

void Loader::importDataFromFile(const string &fileName, vector< vector<double> > &lifetimeData) {
	// Open file, read data, sort data into a multidimensional vector
	ifstream input(fileName);
	if (!input) {
		cerr << "Error opening file: " << fileName << "\n";
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

	// stream of first line
	stream = new stringstream(definition);
	// split line
	while (*stream >> buffer) {
		tokens.push_back(buffer);
	}


	/*
	Possible error here:
	Pushing back m elements because the first line of text has m
	but not guarenteed we have m different data points since we could
	have an arbitrary number of different temp points
	*/

	// number of elements in a line
	int m = tokens.size();
	// fill in the 2-d vector with empty columns, so that we can assign values later
	for (int i = 0; i < m; i++) {
		vector<double> column;
		lifetimeData.push_back(column);
	}

	tokens.clear();

	// Sorts data into vectors categorized by temps, with the first vector being deltaN
	// i.e. { {deltaN1, deltaN2,...}, {temp11, temp12,...}, {temp21, temp22,...},... }
	while (getline(input, definition)) {
		if (stream != NULL)
			delete stream;
		// stream of new line
		stream = new stringstream(definition);
		// split line
		while (*stream >> buffer) {
			tokens.push_back(buffer);
		}

		m = tokens.size();

		// add data to the columns of the multidimensional vector
		for (int i = 0; i < m; i++) {
			lifetimeData[i].push_back( atof(tokens[i].c_str()) );
		}
		
		// For the next line, we clear the tokens and increase k
		tokens.clear();
	}

	input.close();

}