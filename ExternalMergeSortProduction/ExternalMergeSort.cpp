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
		input1->closeIFile();
		input2->setEndOfFile(false);
		input2->closeIFile();
		do {
			cout << "Begin" << endl;
			resp = mergeSequences(input1, input2, curOut, size);
			cout << "End" << endl;
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
			bufA->clearOutFile();
			bufB->clearOutFile();
			input1 = bufC;
			input2 = bufD;
			curOut = bufA;
		}
		else {
			bufC->clearOutFile();
			bufD->clearOutFile();
			input1 = bufA;
			input2 = bufB;
			curOut = bufC;
		}
	}
	return Success;
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


Responce ExternalMergeSort::mergeSequencesNew(FileManager * input1, FileManager * input2, FileManager *out, long long size)
{
	long int *bufArrA = new long int[size/2];
	long int *bufArrB = new long int[size/2];
	long long * readNumberA = new long long();
	long long * readNumberB = new long long();
	long long ia = 0, ib = 0;
	long long curA = 0, curB = 0;
	input1->read(bufArrA, size/2, readNumberA);
	input2->read(bufArrB, size/2, readNumberB);
	if (input1->getEndOfFile())
		ia = size - *readNumberA;
	if (input2->getEndOfFile())
		ib = size - *readNumberB;
	for (; (ia < size) && (ib < size);) {
		if (*bufArrA < *bufArrB) {
			out->write(bufArrA[ia]);
			ia++;
			curA++;
			if (curA >= *readNumberA) {
				input1->read(bufArrA, size / 2, readNumberA);
				curA = 0;
			}
			if (input1->getEndOfFile())
				ia = size - *readNumberA;
		}
		else {
			out->write(bufArrB[ib]);
			ib++;
			curB++;
			if (curB >= *readNumberB) {
				input2->read(bufArrB, size / 2, readNumberB);
				curB = 0;
			}
			if (input2->getEndOfFile())
				ib = size - *readNumberB;
		}
	}

	for (; ia < size; ia++) {

		out->write(bufArrA[ia]);
		ia++;
		curA++;
		if (curA >= *readNumberA) {
			input1->read(bufArrA, size / 2, readNumberA);
			curA = 0;
		}
		if (input1->getEndOfFile())
			ia = size - *readNumberA;
	}
	for (; ib < size; ib++) {

		out->write(bufArrB[ib]);
		ib++;
		curB++;
		if (curB >= *readNumberB) {
			input2->read(bufArrB, size / 2, readNumberB);
			curB = 0;
		}
		if (input2->getEndOfFile())
			ib = size - *readNumberB;
	}
	if (input1->getEndOfFile() && input2->getEndOfFile()) {
		return EndOfFile;
	}

	return Success;
}


Responce ExternalMergeSort::mergeSequences(FileManager * input1, FileManager * input2, FileManager *out, long long size)
{
	long int *bufArrA = new long int();
	long int *bufArrB = new long int();
	long long * readNumberA = new long long();
	long long * readNumberB = new long long();
	long long ia = 0, ib = 0;
	*bufArrA = LLONG_MAX;
	*bufArrB = LLONG_MAX;
	input1->read(bufArrA, 1, readNumberA);
	input2->read(bufArrB, 1, readNumberB);
	if (input1->getEndOfFile())
		ia = size;
	if (input2->getEndOfFile())
		ib = size;
	for (; (ia < size) && (ib < size);) {
		if (*bufArrA < *bufArrB) {
			ia++;
			out->write(*bufArrA);
			if (input1->getEndOfFile()) {
				ia = size;
				break;
			}
			if (ia != size)
				input1->read(bufArrA, 1, readNumberA);
		}
		else {
			ib++;
			out->write(*bufArrB);
			if (input2->getEndOfFile()) {
				ib = size;
				break;
			}
			if (ib != size)
				input2->read(bufArrB, 1, readNumberB);
		}
	}

	for (; ia < size; ia++) {
		
		out->write(*bufArrA);
		if (input1->getEndOfFile()) {
			ia = size;
			break;
		}
		if (ia !=size-1)
			input1->read(bufArrA, 1, readNumberA);
	}
	for (; ib < size; ib++) {
		
		out->write(*bufArrB);
		if (input2->getEndOfFile()) {
			ib = size;
			break;
		}
		if (ib != size - 1)
			input2->read(bufArrB, 1, readNumberB);
	}
	if (input1->getEndOfFile() && input2->getEndOfFile()) {
		return EndOfFile;
	}
	
	return Success;
}


ExternalMergeSort::~ExternalMergeSort()
{
}
