#pragma once
#include "Structures.h"
#include "AppCore.h"

class UserInterface
{
private:
	AppCore *appCore;
	const string menu = "0. Выход\n1. Сгенерировать последовательность\n2. Задать параметры сортировки\n3. Отсоритровать последовательность\n4. Оценить характеристики сортировки\n5. Получение зависимостей\n";
	bool callMethod(int ch);
	Responce callGenerate();
	Responce callSetParams();
	Responce callSort();
	Responce callEstimate();
	Responce callGetDependencies();
	char **responceString;
public:
	void initSession();
	UserInterface();
	~UserInterface();
};

