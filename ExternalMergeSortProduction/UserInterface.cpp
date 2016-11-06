#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>
#include "FileManager.h"
#include "ExternalMergeSort.h"


using namespace std;

void UserInterface::initSession()
{
	appCore = new AppCore();
	const string ch = "Пожалуйста, сделайте выбор --> ";
	cout << menu.c_str() << ch.c_str();
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 3) {
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	while (callMethod(choise)) {
		system("pause");
		system("cls");
		cout << menu.c_str() << ch.c_str();
		cin >> choise;
		while (choise < 0 || choise > 3) {
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
	return fileManager.generateSequence(size,SeqType(ch));
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
	return appCore->setSortParams(file, size, TypeOfSort(ch));
}

Responce UserInterface::callSort()
{	
	cout << "Выполнение сортировки:" << endl;
	return appCore->externalSort();
}

bool UserInterface::callMethod(int choise)
{
	char* responceString[] = { "Успешно", "Ошибка генерации", "Файл не существует", "Ошибка размера", "Ошибка файл-менеджера",
	"Исходный файл и файл результата совпадают", "Достигнут конец файла", "Ошибка выделения памяти", "Параметры не заданы или заданы неверно"};
	Responce resp;
	system("cls");
	switch (choise) {
	case 0: 
		return false;
	case 1:
		resp = callGenerate();
		if (resp == Success) {
			system("cls");
			cout << "Генерация последовательности:\nВыполнение: 100%\n" << "Генерация успешна!" << endl;
			return true;
		}
		else {
			cout << "Генерация завершилась с ошибкой: " << responceString[resp] << endl;
			return true;
		}
		break;
	case 2:
		resp = callSetParams();
		if (resp == Success) {
			system("cls");
			cout << "Параметры успешно заданы!" << endl;
			return true;
		}
		else {
			cout << "Не удалось задать параметры! Ошибка: " << responceString[resp] << endl;
			return true;
		}
		break;
	case 3:
		resp = callSort();
		if (resp == Success) {
			system("cls");
			cout << "Последовательность успешно отсортирована!" << endl;
			return true;
		}
		else {
			cout << "Не удалось отсортировать последовательность! Ошибка: " << responceString[resp] << endl;
			return true;
		}
		break;
	}
}

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}
