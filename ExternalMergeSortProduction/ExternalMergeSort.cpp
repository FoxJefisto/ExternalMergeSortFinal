#include "stdafx.h"
#include "ExternalMergeSort.h"


ExternalMergeSort::ExternalMergeSort()
{
	ok = false;
}

ExternalMergeSort::ExternalMergeSort(FileManager file, long long sizeOfSegments)
{
	exception errorOfCreation;
	Responce resp = setParams(file, sizeOfSegments);
	if (resp!=Success)
	{
		throw errorOfCreation;
	}
}

Responce ExternalMergeSort::setParams(FileManager file, long long size)
{
	if (file.getState() != ReadAndWrite) {
		ok = false;
		return Responce::FileManagerFail;
	}
	if (size<=0){
		ok = false;
		return SizeError;
	}
	sizeOfSegments = size;
	fileManager = file;
	ok = true;
	return Responce::Success;
}


Responce ExternalMergeSort::createRuns()
{

	return Responce();
}

ExternalMergeSort::~ExternalMergeSort()
{
}
