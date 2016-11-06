#include "stdafx.h"
#include "FileManager.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

void FileManager::clearOutFile()
{
	if (oFileStr != nullptr) {
		oFile->open(oFileStr->c_str(), ios_base::trunc);
	}
}

Responce FileManager::read(long int *arr, long long size, long long *readNumber)
{
	if (iFile == nullptr)
		return Responce::FileNotExist;
	if (state != FileState::ReadAndWrite && state != FileState::ReadOnly) {
		return Responce::FileManagerFail;
	}
	if (!iFile->is_open()) {
		iFile->open(iFileStr->c_str());
	}
	long int buf = 0;
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
	arr[n] = -1;
	*readNumber = n;
	if (f == true) {
		return EndOfFile;
	}
	return Success;
}

Responce FileManager::write(long int * arr, long long size)
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
	oFile->close();
	return Responce();
}

Responce FileManager::setFiles(string file, FileState st)
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
			return Responce::FileNotExist;
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
	return Responce::Success;
}

Responce FileManager::setFiles(string inFile, string outFile)
{
	iFile = new ifstream();
	iFileStr = new string();
	iFileStr->resize(inFile.size());
	iFileStr->assign(inFile);
	iFile->open(iFileStr->c_str());
	if (iFile->fail()) {
		iFile = nullptr;
		state = FileState::NotEnable;
		return Responce::FileNotExist;
	}
	iFile->close();
	oFile = new ofstream();
	oFileStr = new string();
	oFileStr->resize(outFile.size());
	oFileStr->assign(outFile);
	state = FileState::ReadAndWrite;
	return Responce::Success;
}



FileManager::FileManager(string file, FileState st)
{
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
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
	setFiles(inFile, outFile);
}

FileManager::FileManager()
{
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
	state = FileState::NotEnable;
}

Responce FileManager::generateSequence(long long size, SeqType type)
{
	if (state != FileState::ReadAndWrite && state != FileState::WriteOnly) {
		return Responce::FileNotExist;
	}
	srand(time(0));
	oFile->open(*oFileStr);
	long int buf;
	int proc = 0;
	int j = 0;
	for (int i = 0; i < size; i++) {
		switch (type) {
		case SeqType::Average:
			buf = 10000 * (rand() % size) + rand() % 10000;
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
			cout << "Генерация последовательности:" << endl;
			cout << "Выполнение: " << proc << "%" << endl;
		}
	}
	oFile->close();
	return Responce::Success;
}

FileManager::~FileManager()
{
	state = FileState::NotEnable;
	iFile = nullptr;
	oFile = nullptr;
	iFileStr = nullptr;
	oFileStr = nullptr;
}
