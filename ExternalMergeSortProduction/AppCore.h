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
	AppCore();
	~AppCore();
};

