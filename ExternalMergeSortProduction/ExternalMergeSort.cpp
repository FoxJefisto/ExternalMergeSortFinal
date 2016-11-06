#include "stdafx.h"
#include "ExternalMergeSort.h"


ExternalMergeSort::ExternalMergeSort()
{
	ok = false;
}

ExternalMergeSort::ExternalMergeSort(FileManager *file, long long sizeOfSegments)
{
	exception errorOfCreation;
	Responce resp = setParams(file, sizeOfSegments);
	if (resp!=Success)
	{
		throw errorOfCreation;
	}
}

Responce ExternalMergeSort::setParams(FileManager *file, long long size)
{
	if (file->getState() != ReadAndWrite) {
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

Responce ExternalMergeSort::externalSort()
{
	Responce resp = createRuns();
	return resp;
}


Responce ExternalMergeSort::createRuns()
{
	if (ok == false) {
		return Responce::ParamsFail;
	}
	FileManager *bufA = new FileManager("bufA.txt", WriteOnly);
	FileManager *bufB = new FileManager("bufB.txt", WriteOnly);
	FileManager *cur = bufA;
	long int *bufArr = new long int[sizeOfSegments];
	if (bufArr == nullptr) {
		return MemoryError;
	}
	for (int i = 0; i < sizeOfSegments; i++) {
		bufArr[i] = -1;
	}
	bufA->clearOutFile();
	bufB->clearOutFile();
	long long * readNumber = new long long();
	Responce resp=Success;
	do{
		resp = fileManager->read(bufArr, sizeOfSegments, readNumber);
		sort(bufArr, *readNumber);
		cur->write(bufArr, *readNumber);
		if (cur == bufA) {
			cur = bufB;
		}
		else {
			if (cur == bufB) {
				cur = bufA;
			}
		}
	} while (resp != EndOfFile);
	return Success;
}

ExternalMergeSort::~ExternalMergeSort()
{
}
