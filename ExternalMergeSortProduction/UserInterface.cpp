#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>
#include "FileManager.h"
#include "ExternalMergeSort.h"
#include <sstream>
#include "BubbleExternalSort.h"
#include "QuickExternalSort.h"
#include "HeapExternalSort.h"


//matrix_tim
#include <conio.h>
using namespace std;

void UserInterface::matrixTime() {
	string matr("matrix");
	string buf;
	cin.clear();
	cin >> buf;
	int f=0,i;
	i = 0;
	if (buf == matr) {
		char mas[6] = { '0','0' ,'0' ,'0' ,'0', '0' };
		system("cls");
		system("color 02");
		while (true) {
			cout << 10 + rand() % 90 << " ";
			if (_kbhit()) {
				if (i > 4) {
					for (int j = 0; j < 5; j++) {
						mas[j] = mas[j + 1];
					}
					i = 5;
				}
				mas[i] = _getch();
				i++;
			}
			if (mas[0] == matr.c_str()[0] && 
				mas[1] == matr.c_str()[1] && 
				mas[2] == matr.c_str()[2] && 
				mas[3] == matr.c_str()[3] && 
				mas[4] == matr.c_str()[4] && 
				mas[5] == matr.c_str()[5])
				break;
		}
		system("color 08");
		cout << "Bye!" << endl;
		system("cls");
	}
}

void UserInterface::initSession()
{
	const string ch = "Пожалуйста, сделайте выбор --> ";
	
	cout << menu.c_str() << ch.c_str();
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 5) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	while (callMethod(choise)) {
		system("pause");
		system("cls");
		cout << menu.c_str() << ch.c_str();
		cin >> choise;
		while (choise < 0 || choise > 5) {
			matrixTime();
			cout << "Вы ошиблись, пожалуйста, повторите --> ";
			cin >> choise;
		}
	}
}

void UserInterface::callGenerate() {
	cout << "Генерация последовательности:" << endl;
	cout << "Пожалуйста введите размер последовательности: " << endl;
	long long size;
	cin >> size;
	while (size < 0) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Пожалуйста введите путь к файлу генерации последовательности" << endl;
	char buf[50];
	cin >> buf;
	string file(buf);
	cout << "Пожалуйста выберите тип последовательности: " << endl << "0. Лучшая последовательность\n1. Средний случай\n2. Худший случай\n";
	int ch;
	cin >> ch;
	while (ch < 0 || ch > 2) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> ch;
	}
	FileManager fileManager(file, WriteOnly);
	Response resp = fileManager.generateSequence(size,SeqType(ch));
	if (resp == Success) {
		system("cls");
		cout << "Генерация последовательности:\nВыполнение: 100%\n" << "Генерация успешна!" << endl;
	}
	else {
		cout << "Генерация завершилась с ошибкой: " << responceString[resp] << endl;
	}
}

void UserInterface::callSetParams()
{
	cout << "Определение параметров сортировки: " << endl;
	cout << "Введите путь к исходной последовательности:" << endl;
	char buf[50];
	cin >> buf;
	string iFile(buf);
	cout << "Введите путь файла результата:" << endl;
	cin >> buf;
	string oFile(buf);
	FileManager *file = new FileManager(iFile, oFile);
	cout << "Введите размер сегментов: ";
	long long size;
	cin >> size;
	while (size < 0) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Выберите тип внутренней сортировки:" << endl << "0. Сортировка пузырьком\n1. Быстрая сортировка\n2. Пирамидальная сортировка\n";
	int ch;
	cin >> ch;
	while (ch < 0 || ch > 2) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> ch;
	}
	Response resp = setParams(file, size, TypeOfSort(ch));
	if (resp == Success) {
		system("cls");
		cout << "Параметры успешно заданы!" << endl;
	}
	else {
		cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] << endl;
	}
}

void UserInterface::callSort()
{	
	Response resp;
	cout << "Выполнение сортировки:" << endl;
	if (sort == nullptr) {
		resp = Response::ParamsFail;
	} else
		resp = sort->externalSort();
	if (resp == Success) {
		system("cls");
		cout << "Последовательность успешно отсортирована за " << sort->counter.getTimeInterval() << " миллисекунд!" << endl;
	}
	else {
		cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
	}
}

void UserInterface::callEstimate()
{
	cout << "Оценка характеристик сортировки:" << endl;
	Response resp;
	if (sort == nullptr) {
		resp = Response::ParamsFail;
	}
	else
		resp = sort->externalSort();
	if (resp == Success) {
		system("cls");
		cout << "Последовательность успешно отсортирована за " << sort->counter.getTimeInterval() << " миллисекунд!" << endl;
		cout << "Количество чтений и записей в файл: " << sort->counter.getFileOp() << endl;
		cout << "Количество сравнений: " << sort->counter.getComparsion() << endl;
		cout << "Количество перестановок: " << sort->counter.getSwaps() << endl;
	}
	else {
		cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
	}
}

void UserInterface::callGetDependenceSize() {
	cout << "Получение зависимости от размера последовательности: " << endl;
	cout << "Введите размер сегментов в процентах от размера последовательности:  ";
	int size;
	cin >> size;
	while (size < 1 || size >100) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Выберите тип внутренней сортировки:" << endl << "0. Сортировка пузырьком\n1. Быстрая сортировка\n2. Пирамидальная сортировка\n";
	int ch;
	cin >> ch;
	while (ch < 0 || ch > 2) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> ch;
	}
	FileManager *file;
	Response resp;
	for (long i = 100; i < 1000000; i = i * 10) {
		stringstream buf;
		buf << "input" << i << ".txt" << '\0';
		file = new FileManager(buf.str(), WriteOnly);
		file->generateSequence(i, SeqType::Worst);
	}
	system("cls");
	long long sizeOfS;
	for (long i = 100; i < 1000000; i = i * 10) {
		stringstream buf;
		buf << "input" << i << ".txt" << '\0';
		string out("out.txt");
		file = new FileManager(buf.str(), out);
		sizeOfS = i / 100 *size;
		resp = setParams(file, sizeOfS, TypeOfSort(ch));
		if (resp != Success) {
			cout << "Размер входной последовательности: " << i << endl;
			cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] <<   endl << endl;
			continue;
		}
		sort->setLog(WithOut);
		resp = sort->externalSort();
		if (resp != Success) {
			cout << "Размер входной последовательности: " << i << endl;
			cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
			continue;
		}
		cout << "Размер входной последовательности: " << i << endl;
		cout << "Время сортировки: " << sort->counter.getTimeInterval() << endl;
		cout << "Число операций с файлами: " << sort->counter.getFileOp() << endl;
		cout << "Число сравнений: " << sort->counter.getComparsion() << endl;
		cout << "Число перестановок: " << sort->counter.getSwaps() << endl;
		cout << endl;
	}
}

void UserInterface::callGetDependenceSizeOfSegments() {
	cout << "Получение зависимости от размера сегментов:" << endl;
	stringstream buf;
	cout << "Введите размер тестовой последовательности: ";
	long long size;
	cin >> size;

	while (size < 0) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Выберите тип внутренней сортировки:" << endl << "0. Сортировка пузырьком\n1. Быстрая сортировка\n2. Пирамидальная сортировка\n";
	int ch;
	cin >> ch;
	while (ch < 0 || ch > 2) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> ch;
	}
	buf << "input" << size << ".txt" << '\0';
	FileManager *file;
	file = new FileManager(buf.str(), WriteOnly);
	file->generateSequence(size, SeqType::Worst);
	system("cls");
	string out("out.txt");
	file = new FileManager(buf.str(), out);
	Response resp;
	for (long long i = 100; i <= size; i = i * 10) {
		 resp = setParams(file, i, TypeOfSort(ch));
		 if (resp != Success) {
			 cout << "Размер сегментов: " << i << endl;
			 cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] << endl << endl;
			 continue;
		 }
		 sort->setLog(WithOut);
		 sort->externalSort();
		 if (resp != Success) {
			 cout << "Размер сегментов: " << i << endl;
			 cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
			 continue;
		 }
		 cout << "Размер сегментов: " << i << endl;
		 cout << "Время сортировки: " << sort->counter.getTimeInterval() << endl;
		 cout << "Число операций с файлами: " << sort->counter.getFileOp() << endl;
		 cout << "Число сравнений: " << sort->counter.getComparsion() << endl;
		 cout << "Число перестановок: " << sort->counter.getSwaps() << endl;
		 cout << endl;
	}
}

void UserInterface::callGetDependenceType()
{
	cout << "Получение зависимости от типа сортировки: " << endl;
	cout << "Введите размер тестовой последовательности: ";
	long long size;
	cin >> size;
	while (size < 0 ) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Введите размер сегментов: ";
	long long sizeOfSegments;
	cin >> sizeOfSegments;
	while (sizeOfSegments < 0 || sizeOfSegments > size) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	FileManager *file;
	stringstream buf;
	buf << "input" << size << ".txt" << '\0';
	Response resp;
	file = new FileManager(buf.str(), WriteOnly);
	resp = file->generateSequence(size, SeqType::Worst);
	
	if (resp != Success) {
		cout << "Ошибка! Не удалось сгенерировать последовательность!" << endl;
	}
	string out("out.txt");
	file = new FileManager(buf.str(), out);
	for (int i = 0; i < 3; i++) {
		resp = setParams(file, sizeOfSegments, TypeOfSort(i));
		if (resp != Success) {
			cout << "Тип сортировки: " << i << endl;
			cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] << endl << endl;
			continue;
		}
		sort->setLog(WithOut);
		sort->externalSort();
		if (resp != Success) {
			cout << "Тип сортировки: " << i << endl;
			cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
			continue;
		}
		sort->setLog(WithOut);
		cout << "Тип сортировки: " << TypeOfSort(i) << endl;
		cout << "Время сортировки: " << sort->counter.getTimeInterval() << endl;
		cout << "Число операций с файлами: " << sort->counter.getFileOp() << endl;
		cout << "Число сравнений: " << sort->counter.getComparsion() << endl;
		cout << "Число перестановок: " << sort->counter.getSwaps() << endl;
		cout << endl;
	}
}

void UserInterface::callGetDependencies()
{
	cout << "Получение зависимости: " << endl;
	cout << "Выберите изменяемую характеристику:\n0. Размер последовательности\n1. Размер сегментов\n2. Тип внутренней сортировки\n->>";
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 2) {
		matrixTime();
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	switch (choise) {
	case 0: 
		callGetDependenceSize();
		break;
	case 1:
		callGetDependenceSizeOfSegments();
		break;
	case 2:
		callGetDependenceType();
		break;
	}
}

Response UserInterface::setParams(FileManager * file, long long sizeOfSegments, TypeOfSort type)
{
	if (file->getState() != ReadAndWrite) {
		return Response::FileManagerFail;
	}
	if (sizeOfSegments < 0) {
		return Response::SizeError;
	}
	if (sizeOfSegments % 2 == 1) {
		return Response::SizeError;
	}
	if (file->checkForEquality()) {
		return Response::InputAndOutputIsEqual;
	}
	ExternalMergeSort *s = nullptr;
	switch (type) {
	case Bubble:
		s = new BubbleExternalSort();
		s->setParams(file, sizeOfSegments);
		break;
	case Quick:
		s = new QuickExternalSort();
		s->setParams(file, sizeOfSegments);
		break;
	case Heap:
		s = new HeapExternalSort();
		s->setParams(file, sizeOfSegments);
		break;
	}
	sort = s;
	return Response::Success;
}

bool UserInterface::callMethod(int choise){
	system("cls");
	switch (choise) {
	case 0: 
		return false;
	case 1:
		callGenerate();
		break;
	case 2:
		callSetParams();
		break;
	case 3:
		callSort();
		break;
	case 4:
		callEstimate();
		break;
	case 5:
		callGetDependencies();
		break;
	}
	return true;
}

UserInterface::UserInterface()
{
	sort = nullptr;
}


UserInterface::~UserInterface()
{
}
