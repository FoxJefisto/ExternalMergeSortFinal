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
	if (size % 2 == 1) {
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
	long long *sizeOfSequence = new long long();
	*sizeOfSequence = 0;
	Responce resp = createRuns(sizeOfSequence);
	FileManager *bufA = new FileManager("bufA.txt", "bufA.txt");
	FileManager *bufB = new FileManager("bufB.txt", "bufB.txt");
	FileManager *bufC = new FileManager("bufC.txt", "bufC.txt");
	bufC->clearOutFile();
	FileManager *bufD = new FileManager("bufD.txt", "bufD.txt");
	bufD->clearOutFile();
	FileManager *curOut = bufC;
	FileManager *input1 = bufA;
	FileManager *input2 = bufB;
	bool done = false;
	long long size = sizeOfSegments;
	while (!done) {
		input1->setEndOfFile(false);
		input2->setEndOfFile(false);
		do {
			resp = mergeSequences(input1, input2, curOut, size);
			if (curOut == bufA) {
				curOut = bufB;
			}
			else {
				if (curOut == bufB) {
					curOut = bufA;
				}
			}
			if (curOut == bufC) {
				curOut = bufD;
			}
			else {
				if (curOut == bufD) {
					curOut = bufC;
				}
			}
		} while (resp != EndOfFile);
		size = size * 2;
		if (size >= *sizeOfSequence) {
			done = true;
		}
		if (input1 == bufA) {
			input1 = bufC;
			input2 = bufD;
		}
		else {
			input1 = bufA;
			input2 = bufB;
		}
	}
	return resp;
}

Responce ExternalMergeSort::createRuns(long long *sizeOfSequence)
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
		*sizeOfSequence += *readNumber;
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

Responce ExternalMergeSort::mergeSequences(FileManager * input1, FileManager * input2, FileManager *out, long long size)
{
	long int *bufArrA = new long int[sizeOfSegments/2];
	long int *bufArrB = new long int[sizeOfSegments / 2];
	long long * readNumberA = new long long();
	long long * readNumberB = new long long();
	long long rest = size;
	long long cur=0;
	if (size < sizeOfSegments / 2) {
		cur =size;
	}
	else {
		cur = sizeOfSegments / 2;
	}
	
	long long ia;
	long long ib;
	while (rest > 0) {
		if (input1->getEndOfFile()) {
			*readNumberA = 0;
		} else 
			input1->read(bufArrA, cur, readNumberA);
		if (input2->getEndOfFile()) {
			*readNumberB = 0;
		} else
			input2->read(bufArrB, cur, readNumberB);
		for (ia = 0, ib = 0; (ia < *readNumberA) && (ib < *readNumberB);) {
			if (bufArrA[ia] < bufArrB[ib]) {
				//c[ic] = a[ia++];
				out->write(bufArrA[ia]);
				ia++;
			}
			else {
				//c[ic] = b[ib++];
				out->write(bufArrB[ib]);
				ib++;
			}
		}
			//далее выполнится только один из циклов в котором счетчик не достиг конца
		for (; ia < *readNumberA; ia++) out->write(bufArrA[ia]);
		for (; ib < *readNumberB; ib++) out->write(bufArrB[ib]);
		rest -= cur;
		if (rest < sizeOfSegments / 2) {
			cur = rest;
		}
		else {
			cur = sizeOfSegments / 2;
		}
	}
	if (input1->getEndOfFile() && input2->getEndOfFile()) {
		return EndOfFile;
	}
	return Success;
}


ExternalMergeSort::~ExternalMergeSort()
{
}
