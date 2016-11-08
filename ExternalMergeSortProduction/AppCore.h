#pragma once
#include "Structures.h"
#include "FileManager.h"
#include "ExternalMergeSort.h"


class AppCore
{
private:
	ExternalMergeSort *sort;
	TypeOfSort type;
public:
	Responce setSortParams(FileManager *file, long long sizeOfSegments, TypeOfSort type);
	Responce externalSort();
	Counter getCounter();
	void setLog(LogType type);
	AppCore();
	~AppCore();
};

