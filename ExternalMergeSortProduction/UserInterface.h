#pragma once
#include "Structures.h"
#include "AppCore.h"

class UserInterface
{
private:
	AppCore *appCore;
	const string menu = "0. Выход\n1. Сгенерировать последовательность\n2. Задать параметры сортировки\n";
	bool callMethod(int ch);
	Responce callGenerate();
	Responce callSetParams();
public:
	void initSession();
	UserInterface();
	~UserInterface();
};

