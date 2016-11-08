#include "stdafx.h"
#include "ExternalMergeSort.h"
#include <sstream>

ExternalMergeSort::ExternalMergeSort()
{
	ok = false;
	log = CLI;
}

ExternalMergeSort::ExternalMergeSort(FileManager *file, long long sizeOfSegments)
{
	exception errorOfCreation;
	Responce resp = setParams(file, sizeOfSegments);
	if (resp!=Success)
	{
		throw errorOfCreation;
	}
	log = CLI;
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
	counter.clear();
	counter.setBegTime();
	long long *sizeOfSequence = new long long();
	*sizeOfSequence = 0;
	print("Начало предформирования отрезков:\n");
	Responce resp = createRuns(sizeOfSequence);
	print("Выполнено!\n");
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
	stringstream bufstr;
	while (!done) {
		input1->setEndOfFile(false);
		input1->closeIFile();
		input2->setEndOfFile(false);
		input2->closeIFile();
		do {
			bufstr.seekp(0, ios::beg);
			bufstr << "Слияние последовательностей размера: " << size << "\n" << '\0';
			print(bufstr.str().c_str());
			resp = mergeSequencesNew(input1, input2, curOut, size);
			counter.incFileOp(size*4);
			bufstr.seekp(0, ios::beg);
			bufstr << "Выполнено!" << "\n" << '\0';
			print(bufstr.str().c_str());
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
		if (size * 2 >= *sizeOfSequence) {
			curOut = fileManager;
		}
	}
	counter.setEndTime();
	return Success;
}

Responce ExternalMergeSort::setLog(LogType log)
{
	this->log = log;
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
		counter.incFileOp(*readNumber);
		*sizeOfSequence += *readNumber;
		print("Выполнение внутренней сортировки:\n");
		sort(bufArr, *readNumber);
		print("Выполнено!\n");
		cur->write(bufArr, *readNumber);
		counter.incFileOp(*readNumber);
		cur->closeOFile();
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
	bool A=false, B=false;
	if (input1->getEndOfFile()) {
		ia = size;
	}
	else {
		input1->read(bufArrA, size / 2, readNumberA);
	}
	if (input2->getEndOfFile()) {
		ib = size;
	}
	else {
		input2->read(bufArrB, size / 2, readNumberB);
	}
	while (ia < size && ib < size) {
		counter.incComparsion(1);
		if (bufArrA[curA] < bufArrB[curB]) {
			out->write(bufArrA[curA]);
			ia++;
			curA++;
			if (input1->getEndOfFile() && !A) 
			{
				if (ia < size - *readNumberA) {
					ia = size - *readNumberA + 1;
				}
				A = true;
			}
			if (curA >= *readNumberA) {
				if (size / 2 > size - ia) {
					input1->read(bufArrA, size - 1 - ia, readNumberA);
				}
				else {
					input1->read(bufArrA, size/2, readNumberA);
				}
				curA = 0;
			}
		}
		else {
			out->write(bufArrB[curB]);
			ib++;
			curB++;
			if (input2->getEndOfFile() && !B) {
				if (ib < size - *readNumberB) {
					ib = size - *readNumberB + 1;
				}
				B = true;
			}
			if (curB >= *readNumberB) {
				if (size / 2 > size - ib) {
					input2->read(bufArrB, size - 1 - ib, readNumberB);
				}
				else {
					input2->read(bufArrB, size / 2, readNumberB);
				}
				curB = 0;
			}
		}
	}
	for (; ia < size;) {
		out->write(bufArrA[curA]);
		ia++;
		curA++;
		if (input1->getEndOfFile() && !A) {
			if (ia < size - *readNumberA) {
				ia = size - *readNumberA + 1;
			}
			A = true;
		}
		if (curA >= *readNumberA) {
			if (size / 2 > size - ia) {
				input1->read(bufArrA, size - 1 - ia, readNumberA);
			}
			else {
				input1->read(bufArrA, size / 2, readNumberA);
			}
			curA = 0;
		}
	}
	for (; ib < size;) {
		out->write(bufArrB[curB]);
		ib++;
		curB++;
		if (input2->getEndOfFile() && !B) {
			if (ib < size - *readNumberB) {
				ib = size - *readNumberB + 1;
			}
			B = true;
		}
		if (curB >= *readNumberB) {
			if (size / 2 > size - ib) {
				input2->read(bufArrB, size - 1 - ib, readNumberB);
			}
			else {
				input2->read(bufArrB, size / 2, readNumberB);
			}
			curB = 0;
		}
	}

	if (input1->getEndOfFile() && input2->getEndOfFile()) {
		out->closeOFile();
		return EndOfFile;
	}
	out->closeOFile();
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

void ExternalMergeSort::print(const char * msg)
{
	if (log == WithOut) return;
	if (log == CLI) {
		cout << msg;
	}
	else {
		fstream log;
		log.open("log.txt");
		log << msg;
	}
}


ExternalMergeSort::~ExternalMergeSort()
{
}
