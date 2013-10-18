#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cctype>
#include <algorithm>

#include "hash.h"

using namespace std;

string validCharacters = "abcdefghijklmnopqrstuvwxyz0123456789-\'";
string ignoreCharacters = "0123456789";
hashTable dict(100000);

string toLowerCaseSTD(std::string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void loadDict() {
	string filename;
	cout << "Enter name of dictionary: ";
	cin >> filename;

	clock_t t1 = clock();
	ifstream inputDict(filename.c_str());
	if (!inputDict) {
		cerr << "Error: could not open " << filename << endl;
		exit(1);
	}

	string line;
	while (getline(inputDict, line)) {
		line = toLowerCaseSTD(line);
		if (line.find_first_not_of(validCharacters) != string::npos
				|| line.length() > 20) {
			continue;
		}
		dict.insert(line);
	}
	inputDict.close();

	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;
}

void spellCheck() {
	string filenameIn, filenameOut, line, word;
	unsigned int startIndex, stopIndex;
	cout << "Enter name of input file: ";
	cin >> filenameIn;
	ifstream input(filenameIn.c_str());
	if (!input) {
		cerr << "Error: could not open " << filenameIn << endl;
		exit(1);
	}
	cout << "Enter name of output file: ";
	cin >> filenameOut;
	ofstream output(filenameOut.c_str());
	if (!output) {
		cerr << "Error: could not open " << filenameOut << endl;
		exit(1);
	}
	unsigned int lineNum = 1;
	while (getline(input, line)) {
		line = toLowerCaseSTD(line);
		int startIndex = line.find_first_of(validCharacters);
		int stopIndex = line.find_first_not_of(validCharacters, startIndex);
		while (startIndex != string::npos) {
			if (stopIndex == string::npos) {
				stopIndex = line.length();
			}
			word = line.substr(startIndex, stopIndex - startIndex);
			if (word.length() > 20) {
				output << "Long word at line " << lineNum << ", starts: "
						<< word.substr(0, 20) << endl;
			}else if (word.find_first_of(ignoreCharacters) != string::npos){

			}else if (!dict.contains(word)){
				output << "Unknown word at line " << lineNum << ": "<< word << endl;
			}

			if (stopIndex != line.length()) {
				line = line.substr(stopIndex + 1);
			} else {
				break;
			}
			startIndex = line.find_first_of(validCharacters);
			stopIndex = line.find_first_not_of(validCharacters, startIndex);
		}
		lineNum++;
	}
	input.close();
	output.close();
}

int main() {
	loadDict();
	spellCheck();
	return 0;
}
;
