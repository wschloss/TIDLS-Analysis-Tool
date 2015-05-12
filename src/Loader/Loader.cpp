#include "Loader.h"

Loader::Loader() {
}

void Loader::importConstantsFromFile(const string &fileName, map<string,double> &dataMap) {
	// Open file, read data, store in map
	ifstream input(fileName);

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

	// line and buffer string
	string definition, buffer;
	// string stream for splitting
	stringstream* stream = NULL;
	// vector of the resulting tokens
	vector<string> tokens;

	// data begins at this line number (first line = 1)
	unsigned int startLine = 2;
	// Gets the specified line of text
	for (unsigned int i = 1; i <= startLine; i++) {
		getline(input, definition);
	}

	// stream of specified line
	stream = new stringstream(definition);
	// split line
	while (*stream >> buffer) {
		tokens.push_back(buffer);
	}
	
	// number of elements in a line
	int startLength = tokens.size();
	// empty vector for creating columns
	vector<double> column;
	// fill in the 2-d vector with empty columns, and fill in the first row with data
	for (int i = 0; i < startLength; i++) {
		lifetimeData.push_back(column);
		lifetimeData[i].push_back(atof(tokens[i].c_str()));
	}
	
	tokens.clear();

	// line number being taken from the file
	unsigned int lineNum = startLine;

	// Sorts data into vectors categorized by temps, with the first vector being deltaN
	// i.e. { {deltaN1_temp1, deltaN2_temp1,...}, {tau1_temp1, tau2_temp1,...}, {deltaN1_temp2, deltaN2_temp2,...}, {tau1_temp2, tau2_temp2,...},... }
	while (getline(input, definition)) {
		lineNum++;
		if (stream != NULL)
			delete stream;
		// stream of new line
		stream = new stringstream(definition);
		// split line
		while (*stream >> buffer) {
			tokens.push_back(buffer);
		}

		/*
		For now I'm cutting out any line that is not the same length as the first 
		line (of data - not any headers). We may need to make adjustments in the future.
		*/

		// if this line is the same length as the original starting line
		if (tokens.size() == startLength) {
			// add data to the columns of the multidimensional vector
			for (int i = 0; i < startLength; i++) {
				lifetimeData[i].push_back(atof(tokens[i].c_str()));
			}
		}

		else {
			cout << "\nLine Skipped: Line " << lineNum << " is not the same length as line " << startLine << endl;
		}
		
		tokens.clear();
	}

	input.close();

}