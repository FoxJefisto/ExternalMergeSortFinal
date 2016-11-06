// ExternalMergeSortProduction.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	UserInterface ui;
	ui.initSession();
    return 0;
}

