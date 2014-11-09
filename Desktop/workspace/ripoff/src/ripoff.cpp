//============================================================================
// Name        : ripoff.cpp
// Author      : Sau00
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

/* Reading input file */
vector <string> readFile() {
	ifstream fileStream;
	string currentLine;
	vector <string> stringVector;

	/* Opening file stream */
	fileStream.open("input.txt");

	/* Filling the Vector with file strings */
	while(!fileStream.eof()) {
		getline(fileStream, currentLine);
		stringVector.push_back(currentLine);
	}

	fileStream.close();

	return stringVector;
}

/* Printing Vector contents */
void printStringVector(vector <string> stringVector) {
	for(int i = 0; i < stringVector.size(); i++) {
		cout << stringVector[i] << endl;
	}
}

/* Getting stop-words array */
vector <string> getStopwords() {
	string stopWordsArray[] = {
			",", ".", ":", "«", "»", "—", "(", ")", "’", "!", "-", "=", "'", "[", "]"
	};

	vector <string> stopWordsVector;

	for(int i = 0; i < sizeof(stopWordsArray) / sizeof(stopWordsArray[0]); i++) {
		stopWordsVector.push_back(stopWordsArray[i]);
	}

	return stopWordsVector;
}

/* String to lower case */
vector <string> stringToLower(vector <string> Input) {
	for(int i = 0; i < Input.size(); i++) {
		transform(Input[i].begin(), Input[i].end(), Input[i].begin(), ::tolower);
	}

	return Input;
}

/* Normalizing String */
vector <string> normalizeString(vector <string> Input) {
	int start;

	vector <string> stopWords = getStopwords();

	for(int i = 0; i < stopWords.size(); i++) {
		for(int k = 0; k < Input.size(); k++) {
			while((start = Input[k].find(stopWords[i])) != string::npos) {
				Input[k].replace(start, stopWords[i].length(), "");
			}
		}
	}

	Input = stringToLower(Input);

	return Input;
}

int main() {
	setlocale(LC_ALL, "");
	vector <string> stringVectorInput;
	vector <string> stringVectorOutput;

	stringVectorInput = normalizeString(readFile()); // Reading and normalizing file

	printStringVector(stringVectorInput);

	return 0;
}
