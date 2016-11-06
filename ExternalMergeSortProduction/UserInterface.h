#pragma once
#include "Structures.h"

class UserInterface
{
private:
	const string menu = "0. Выход\n1. Сгенерировать последовательность\n2. Задать параметры сортировки\n";
	bool callMethod(int ch);
	Responce callGenerate();
	Responce callSetParams();
public:
	void initSession();
	UserInterface();
	~UserInterface();
};

