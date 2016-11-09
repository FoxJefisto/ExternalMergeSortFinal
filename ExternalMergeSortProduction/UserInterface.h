#pragma once
#include "Structures.h"
#include "ExternalMergeSort.h"

class UserInterface
{
private:
	ExternalMergeSort *sort;
	const string menu = "0. Выход\n1. Сгенерировать последовательность\n2. Задать параметры сортировки\n3. Отсоритровать последовательность\n4. Оценить характеристики сортировки\n5. Получение зависимостей\n";
	bool callMethod(int ch);
	void callGenerate();
	void callSetParams();
	void callSort();
	void callEstimate();
	void callGetDependencies();
	char **responceString;
	Responce setParams(FileManager *file, long long sizeOfSegments, TypeOfSort type);
public:
	void initSession();
	UserInterface();
	~UserInterface();
};

