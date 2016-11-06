#include "stdafx.h"
#include "FileManager.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

Responce FileManager::setFiles(string file, FileState st)
{
	iFile = nullptr;
	oFile = nullptr;
	ifstream f;
	switch (st) {
	case FileState::ReadOnly:
		iFile = new string();
		iFile->resize(file.size());
		iFile->assign(file);
		f.open(iFile->c_str());
		if (f.fail()) {
			state = FileState::NotEnable;
			return Responce::FileNotExist;
		}
		f.close();
		state = st;
		break;
	case FileState::WriteOnly:
		oFile = new string();
		oFile->resize(file.size());
		oFile->assign(file);
		state = st;
		break;
	default: state = FileState::NotEnable;
		break;
	}
	return Responce::Success;
}

Responce FileManager::setFiles(string inFile, string outFile)
{
	ifstream f;
	iFile = new string();
	iFile->resize(inFile.size());
	iFile->assign(inFile);
	f.open(iFile->c_str());
	if (f.fail()) {
		state = FileState::NotEnable;
		return Responce::FileNotExist;
	}
	f.close();
	oFile = new string();
	oFile->resize(outFile.size());
	oFile->assign(outFile);
	state = FileState::ReadAndWrite;
	return Responce::Success;
}



FileManager::FileManager(string file, FileState st)
{
	setFiles(file, st);
}

FileState FileManager::getState()
{
	return state;
}

FileManager::FileManager(string inFile, string outFile)
{
	setFiles(inFile, outFile);
}

FileManager::FileManager()
{
	iFile = nullptr;
	oFile = nullptr;
	state = FileState::NotEnable;
}

Responce FileManager::generateSequence(long long size, SeqType type)
{
	if (state != FileState::ReadAndWrite && state != FileState::WriteOnly) {
		return Responce::FileNotExist;
	}
	srand(time(0));
	ofstream file;
	file.open(*oFile);
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
		file << buf << " ";
		j++;
		if (j > size / 100) {
			proc++;
			j = 0;
			system("cls");
			cout << "Генерация последовательности:" << endl;
			cout << "Выполнение: " << proc << "%" << endl;
		}
	}
	file.close();
	return Responce::Success;
}

FileManager::~FileManager()
{
	state = FileState::NotEnable;
	iFile = nullptr;
	oFile = nullptr;
}
