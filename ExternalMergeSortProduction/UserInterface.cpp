#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>
#include "FileManager.h"
#include "ExternalMergeSort.h"
#include <sstream>

using namespace std;

void UserInterface::initSession()
{
	char *respString[] = { "Успешно", "Ошибка генерации", "Файл не существует", "Ошибка размера", "Ошибка файл-менеджера",
		"Исходный файл и файл результата совпадают", "Достигнут конец файла", "Ошибка выделения памяти", "Параметры не заданы или заданы неверно" };
	responceString = respString;
	appCore = new AppCore();
	const string ch = "Пожалуйста, сделайте выбор --> ";
	cout << menu.c_str() << ch.c_str();
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 5) {
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	while (callMethod(choise)) {
		system("pause");
		system("cls");
		cout << menu.c_str() << ch.c_str();
		cin >> choise;
		while (choise < 0 || choise > 5) {
			cout << "Вы ошиблись, пожалуйста, повторите --> ";
			cin >> choise;
		}
	}
}

Responce UserInterface::callGenerate() {
	cout << "Генерация последовательности:" << endl;
	cout << "Пожалуйста введите размер последовательности: " << endl;
	int size;
	cin >> size;
	while (size < 0) {
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
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> ch;
	}
	FileManager fileManager(file, WriteOnly);
	Responce resp = fileManager.generateSequence(size,SeqType(ch));
	if (resp == Success) {
		system("cls");
		cout << "Генерация последовательности:\nВыполнение: 100%\n" << "Генерация успешна!" << endl;
	}
	else {
		cout << "Генерация завершилась с ошибкой: " << responceString[resp] << endl;
	}
	return resp;
}

Responce UserInterface::callSetParams()
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
	int size;
	cin >> size;
	while (size < 0) {
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> size;
	}
	cout << "Выберите тип внутренней сортировки:" << endl << "0. Сортировка пузырьком\n1. Быстрая сортировка\n2. Пирамидальная сортировка\n";
	int ch;
	cin >> ch;
	Responce resp = appCore->setSortParams(file, size, TypeOfSort(ch));
	if (resp == Success) {
		system("cls");
		cout << "Параметры успешно заданы!" << endl;
	}
	else {
		cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] << endl;
	}
	return resp;
}

Responce UserInterface::callSort()
{	
	cout << "Выполнение сортировки:" << endl;
	Responce resp = appCore->externalSort();
	if (resp == Success) {
		system("cls");
		cout << "Последовательность успешно отсортирована за " << appCore->getCounter().getTimeInterval() << " миллисекунд!" << endl;
	}
	else {
		cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
	}
	return resp;
}

Responce UserInterface::callEstimate()
{
	cout << "Оценка характеристик сортировки:" << endl;
	Responce resp = appCore->externalSort();
	if (resp == Success) {
		system("cls");
		cout << "Последовательность успешно отсортирована за " << appCore->getCounter().getTimeInterval() << " миллисекунд!" << endl;
		cout << "Количество чтений и записей в файл: " << appCore->getCounter().getFileOp() << endl;
		cout << "Количество сравнений: " << appCore->getCounter().getComparsion() << endl;
		cout << "Количество перестановок: " << appCore->getCounter().getSwaps() << endl;
	}
	else {
		cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
	}
	return resp;
}

Responce UserInterface::callGetDependencies()
{
	cout << "Получение зависимости: " << endl;
	cout << "Выберите изменяемую характеристику:\n0. Размер последовательности\n1. Размер сегментов\n2. Тип внутренней сортировки\n->>";
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 2) {
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	switch (choise) {
	case 0:
		//FileManager *file = new FileManager(iFile, oFile);
		cout << "Введите размер сегментов, 0 если размер сегментов равен размеру последовательности: ";
		int size;
		cin >> size;
		while (size < 0 || size >101) {
			cout << "Вы ошиблись, пожалуйста, повторите --> ";
			cin >> size;
		}
		cout << "Выберите тип внутренней сортировки:" << endl << "0. Сортировка пузырьком\n1. Быстрая сортировка\n2. Пирамидальная сортировка\n";
		int ch;
		cin >> ch;
		FileManager *file;
		Responce resp;
		for (long i = 100; i < 100000000; i = i * 10) {
			stringstream buf;
			buf << "input" << i << ".txt" << '\0';
			file = new FileManager(buf.str(), WriteOnly);
			file->generateSequence(i, SeqType::Worst);
		}
		system("cls");
		for (long i = 100; i < 100000000; i = i * 10) {
			stringstream buf;
			buf << "input" << i << ".txt" << '\0';
			string out("out.txt");
			file = new FileManager(buf.str(), out);
			if (size == 0) {
				resp = appCore->setSortParams(file, i, TypeOfSort(ch));
			} else
				resp = appCore->setSortParams(file, size, TypeOfSort(ch));
			if (resp != Success) {
				cout << "Ошибка! Не удалось задать параметры!" << endl;
				return resp;
			}
			appCore->setLog(WithOut);
			resp = appCore->externalSort();
			if (resp != Success) {
				cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
				return resp;
			}
			cout << "Размер входной последовательности: " << i << endl;
			cout << "Время сортировки: " << appCore->getCounter().getTimeInterval() << endl;
			cout << "Число операций с файлами: " << appCore->getCounter().getFileOp() << endl;
			cout << "Число сравнений: " << appCore->getCounter().getComparsion() << endl;
			cout << "Число перестановок: " << appCore->getCounter().getSwaps() << endl;
			cout << endl;
		}
		break;
	}
	return Success;
}

bool UserInterface::callMethod(int choise){
	Responce resp;
	system("cls");
	switch (choise) {
	case 0: 
		return false;
	case 1:
		resp = callGenerate();
		break;
	case 2:
		resp = callSetParams();
		break;
	case 3:
		resp = callSort();
		break;
	case 4:
		resp = callEstimate();
		break;
	case 5:
		resp = callGetDependencies();
		break;
	}
	return true;
}

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}
