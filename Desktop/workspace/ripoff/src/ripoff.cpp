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

// Читаем файл
vector <string> readFile() {
	ifstream fileStream;
	string currentLine;
	vector <string> stringVector;

	// Читаем файл
	fileStream.open("input.txt");

	// Записываем файл в вектор строк
	while(!fileStream.eof()) {
		getline(fileStream, currentLine);
		stringVector.push_back(currentLine);
	}

	fileStream.close();

	return stringVector;
}

// Выводим файл
void printStringVector(vector <string> stringVector) {
	for(int i = 0; i < stringVector.size(); i++) {
		cout << stringVector[i] << endl;
	}
}

// Получаем стоп-слова в виде вектора
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

int main() {
	setlocale(LC_ALL, "");
	vector <string> stringVectorInput;
	vector <string> stringVectorOutput;
	vector <string> stopWords = getStopwords();

	stringVectorInput = readFile(); // Читаем файл

	int start;

	for(int i = 0; i < stopWords.size(); i++) {
		for(int k = 0; k < stringVectorInput.size(); k++) {
			while((start = stringVectorInput[k].find(stopWords[i])) != string::npos) {
				stringVectorInput[k].replace(start, stopWords[i].length(), "");
			}
		}
	}

	printStringVector(stringVectorInput);

	// @TODO Сделать возможность перевода в нижний регистр для русской кодировки
	// Собрать все в одну строку

	return 0;
}
