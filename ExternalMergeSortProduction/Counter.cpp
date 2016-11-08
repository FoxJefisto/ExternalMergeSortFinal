#include "stdafx.h"
#include "Counter.h"


Counter::Counter()
{
	clear();
}

void Counter::setBegTime()
{
	begTime = clock();
}

long Counter::setEndTime()
{
	endTime = clock();
	return getTimeInterval();
}

long Counter::getTimeInterval()
{
	return (endTime - begTime) * 1000 / CLOCKS_PER_SEC; //число миллисекунд
}

void Counter::incComparsion(long n)
{
	comparsion += n;
}

long Counter::getComparsion()
{
	return comparsion;
}

void Counter::incFileOp(long n)
{
	fileOp += n;
}

long Counter::getFileOp()
{
	return fileOp;
}

void Counter::clear()
{
	begTime = 0;
	endTime = 0;
	comparsion = 0;
	fileOp = 0;
}


Counter::~Counter()
{
}
