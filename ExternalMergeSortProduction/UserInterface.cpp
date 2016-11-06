#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>
#include "FileManager.h"

using namespace std;

void UserInterface::initSession()
{
	const string menu = "0. Выход\n1. Сгенерировать последовательность\n";
	const string ch = "Пожалуйста, сделайте выбор --> ";
	cout << menu.c_str() << ch.c_str();
	int choise = -1;
	cin >> choise;
	while (choise < 0 || choise > 1) {
		cout << "Вы ошиблись, пожалуйста, повторите --> ";
		cin >> choise;
	}
	while (callMethod(choise)) {
		system("pause");
		system("cls");
		cout << menu.c_str() << ch.c_str();
		cin >> choise;
		while (choise < 0 || choise > 1) {
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

bool UserInterface::callMethod(int choise)
{
	char* responceString[] = { "Успешно", "Ошибка генерации", "Файл не существует", "Ошибка размера", "Ошибка файл-менеджера" };
	Responce resp;
	switch (choise) {
	case 0: 
		return false;
	case 1:
		resp = callGenerate();
		if (resp == Success) {
			cout << "Генерация успешна!" << endl;
			return true;
		}
		else {
			cout << "Генерация завершилась с ошибкой: " << responceString[resp] << endl;
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
