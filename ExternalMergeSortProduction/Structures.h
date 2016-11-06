#pragma once
#include <iostream>;

enum FileState { NotEnable, ReadOnly, WriteOnly, ReadAndWrite };
enum Responce { Success, GenerateError, FileNotExist, SizeError, FileManagerFail};

enum SeqType {Best, Average, Worst};