#include "stdafx.h"
#include "FileManager.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;
#include <sstream>

void FileManager::closeIFile()
{
	if (iFile->is_open()) {
		iFile->close();
	}
}

void FileManager::closeOFile()
{
	if (oFile->is_open()) {
		oFile->close();
	}
}

bool FileManager::getEndOfFile()
{
	return endOfFile;
}

void FileManager::setEndOfFile(bool b)
{
	endOfFile = b;
}

void FileManager::clearOutFile()
{
	if (oFileStr != nullptr) {
		oFile->open(oFileStr->c_str(), ios_base::trunc);
		oFile->close();
	}
}

Response FileManager::read(long long *arr, long long size, long long *readNumber)
{
	if (iFile == nullptr)
		return Response::FileNotExist;
	if (state != FileState::ReadAndWrite && state != FileState::ReadOnly) {
		return Response::FileManagerFail;
	}
	if (!iFile->is_open()) {
		iFile->open(iFileStr->c_str());
	}
	long long buf = 0;
	bool f = false;
	int n = 0;
	for (int i = 0; i < size; i++) {
		if (iFile->eof()) {
			n--;
			f = true;
			break;
		}
		n++;
		*iFile >> buf;
		arr[i] = buf;
	}
	*readNumber = n;
	if (f == false) {
		*iFile >> buf;
		if (iFile->eof()) {
			f = true;
		}
		else {
			ostringstream str;
			str << buf;
			int disp = str.str().length();
			iFile->seekg(-disp, ios::cur);
		}
	}
	if (f == true) {
		arr[n] = -1;
		iFile->close();
		endOfFile = true;
		return EndOfFile;
	}
	return Success;
}

Response FileManager::write(long long num)
{
	if (!oFile->is_open()) {
		oFile->open(oFileStr->c_str(), ios_base::app);
	}
	if (state != WriteOnly && state != ReadAndWrite) {
		return FileManagerFail;
	}
	*oFile << num << " ";
	return Success;
}


Response FileManager::write(long long * arr, long long size)
{
	if (!oFile->is_open()) {
		oFile->open(oFileStr->c_str(),ios_base::app);
	}
	if (state != WriteOnly && state != ReadAndWrite) {
		return FileManagerFail;
	}
	for (int i = 0; i < size; i++) {
		*oFile << arr[i] << " ";
	}
	return Success;
}

Response FileManager::setFiles(string file, FileState st)
{
	switch (st) {
	case FileState::ReadOnly:
		iFile = new ifstream();
		iFileStr = new string();
		iFileStr->resize(file.size());
		iFileStr->assign(file);
		iFile->open(iFileStr->c_str());
		if (iFile->fail()) {
			iFile = nullptr;
			state = FileState::NotEnable;
			return Response::FileNotExist;
		}
		iFile->close();
		state = st;
		break;
	case FileState::WriteOnly:
		oFile = new ofstream();
		oFileStr = new string();
		oFileStr->resize(file.size());
		oFileStr->assign(file);
		state = st;
		break;
	default: state = FileState::NotEnable;
		break;
	}
	return Response::Success;
}

Response FileManager::setFiles(string inFile, string outFile)
{
	iFile = new ifstream();
	iFileStr = new string();
	iFileStr->resize(inFile.size());
	iFileStr->assign(inFile);
	iFile->open(iFileStr->c_str());
	if (iFile->fail()) {
		iFile = nullptr;
		state = FileState::NotEnable;
		return Response::FileNotExist;
	}
	iFile->close();
	oFile = new ofstream();
	oFileStr = new string();
	oFileStr->resize(outFile.size());
	oFileStr->assign(outFile);
	state = FileState::ReadAndWrite;
	return Response::Success;
}



FileManager::FileManager(string file, FileState st)
{
	endOfFile = false;
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
	setFiles(file, st);
}

FileState FileManager::getState()
{
	return state;
}

bool FileManager::checkForEquality()
{
	if (state==ReadAndWrite && *iFileStr==*oFileStr)
		return true;
	return false;
}

FileManager::FileManager(string inFile, string outFile)
{
	endOfFile = false;
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
	setFiles(inFile, outFile);
}

FileManager::FileManager()
{
	endOfFile = false;
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
	state = FileState::NotEnable;
}

Response FileManager::generateSequence(long long size, SeqType type)
{
	if (state != FileState::ReadAndWrite && state != FileState::WriteOnly) {
		return Response::FileNotExist;
	}
	srand(time(0));
	oFile->open(*oFileStr);
	long long buf;
	int proc = 0;
	int j = 0;
	for (int i = 0; i < size; i++) {
		switch (type) {
		case SeqType::Average:
			buf = 1000 * (rand() % 1000) + rand() % 1000;
			break;
		case SeqType::Best:
			buf = i;
			break;
		case SeqType::Worst:
			buf = size - i;
			break;
		}
		*oFile << buf << " ";
		j++;
		if (j > size / 100) {
			proc++;
			j = 0;
			system("cls");
			cout << "????????? ??????????????????:" << endl;
			cout << "??????????: " << proc << "%" << endl;
		}
	}
	oFile->close();
	return Response::Success;
}

FileManager::~FileManager()
{
	state = FileState::NotEnable;
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
}
