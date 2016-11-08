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
	Counter counter;
	Responce createRuns(long long *);
	Responce mergeSequencesNew(FileManager *input1, FileManager *input2, FileManager *out, long long size);
	Responce mergeSequences(FileManager *input1, FileManager *input2, FileManager *out, long long size);
public:
	ExternalMergeSort();
	ExternalMergeSort(FileManager *file, long long sizeOfSegments);
	Responce setParams(FileManager *file, long long sizeOfSegments);
	Responce externalSort();
	
	virtual void sort(long int*, long long) = 0;
	virtual ~ExternalMergeSort();
};

