#pragma once
#include "FileManager.h"

using namespace std;

class ExternalMergeSort
{
	FileManager fileManager;
	long long sizeOfSegments;
	bool ok;
public:
	ExternalMergeSort();
	ExternalMergeSort(FileManager file, long long sizeOfSegments);
	Responce setParams(FileManager file, long long sizeOfSegments);
	Responce externalSort();
	Responce createRuns();
	virtual ~ExternalMergeSort();
};

