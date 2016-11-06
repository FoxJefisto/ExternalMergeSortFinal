#pragma once
#include "Structures.h"

class UserInterface
{
private:
public:
	void initSession();
	bool callMethod(int ch);
	Responce callGenerate();
	UserInterface();
	~UserInterface();
};

