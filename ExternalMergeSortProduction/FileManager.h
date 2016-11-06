#pragma once
#include <fstream>
#include "Structures.h"
using namespace std;

class FileManager
{
private:
	ifstream *iFile;
	ofstream *oFile;
	string *oFileStr;
	string *iFileStr;
	FileState state;
public:
	void clearOutFile();
	Responce read(long int * arr,long long size, long long* readNumber);
	Responce write(long int *arr, long long size);
	Responce setFiles(string file, FileState st);
	Responce setFiles(string inFile, string outFile);
	FileState getState();
	bool checkForEquality();
	Responce generateSequence(long long size, SeqType type);
	FileManager(string iFile, FileState state);
	FileManager(string inFile,string outFile);
	FileManager();
	~FileManager();
};

