//============================================================================
// Name        : ripoff.cpp
// Author      : Sau00
// Version     :
// Copyright   : Your copyright notice
// Description : My first C++ application
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

/* Reading input file */
vector <string> readFile(string inputFilename) {

	// @TODO Add file exist checking

	ifstream fileStream;
	string currentLine;
	vector <string> stringVector;

	/* Opening file stream */
	fileStream.open(inputFilename.c_str());

	/* Filling the Vector with file strings */
	while(!fileStream.eof()) {
		getline(fileStream, currentLine);
		if(!currentLine.empty()) {
			stringVector.push_back(currentLine);
		}
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

/* Parsing words from strings */
vector <string> parseWords(vector <string> Input) {
	vector <string> words;
	string currentWord;
	int start;

	for(int i = 0; i < Input.size(); i++) {
		while((start = Input[i].find(" ")) != string::npos) {
			currentWord = Input[i].substr(0, start);
			if(!currentWord.empty()) {
				words.push_back(currentWord);
			}
			Input[i].replace(0, start + 1, "");
		}
		if(!currentWord.empty()) {
			words.push_back(currentWord);
		}
	}

	return words;
}

int main(int argc, char* argv[]) {

	string inputFilename;
	string outputFilename;

	for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		if((arg == "-h") || (arg == "--help")) {
			std::cout << arg << endl;
		} else if((arg == "-i") && ((i + 1) < argc)) {
			inputFilename = argv[i + 1];
		} else if((arg == "-o") && ((i + 1) < argc)) {
			outputFilename = argv[i + 1];
		}
	}

	setlocale(LC_ALL, "");
	vector <string> stringVectorInput;
	vector <string> stringVectorOutput;
	vector <string> words;


	stringVectorInput = normalizeString(readFile(inputFilename)); // Reading and normalizing file

	words = parseWords(stringVectorInput); // Spliting all string to words
	printStringVector(words); // Printing results

	return 0;
}
