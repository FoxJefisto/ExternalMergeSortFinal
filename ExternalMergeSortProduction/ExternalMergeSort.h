#pragma once
#include "FileManager.h"
#include "Counter.h"

using namespace std;

class ExternalMergeSort
{
private:
	FileManager *fileManager;
	long long sizeOfSegments;
	bool ok;
	
	Responce createRuns(long long *);
	Responce mergeSequencesNew(FileManager *input1, FileManager *input2, FileManager *out, long long size);
	LogType log;
	void print(const char *);
public:
	Counter counter;
	ExternalMergeSort();
	ExternalMergeSort(FileManager *file, long long sizeOfSegments);
	Responce setParams(FileManager *file, long long sizeOfSegments);
	Responce externalSort();
	Responce setLog(LogType log);
	virtual void sort(long long*, long long) = 0;
	virtual ~ExternalMergeSort();
};

