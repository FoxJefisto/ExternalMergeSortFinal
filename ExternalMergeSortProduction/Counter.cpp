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

long long Counter::setEndTime()
{
	endTime = clock();
	return getTimeInterval();
}

long long Counter::getTimeInterval()
{
	return (endTime - begTime) * 1000 / CLOCKS_PER_SEC; //число миллисекунд
}

void Counter::incSwaps()
{
	swaps++;
}

long long Counter::getSwaps()
{
	return swaps;
}

void Counter::incComparsion(long long n)
{
	comparsion += n;
}

long long Counter::getComparsion()
{
	return comparsion;
}

void Counter::incFileOp(long long n)
{
	fileOp += n;
}

long long Counter::getFileOp()
{
	return fileOp;
}

void Counter::clear()
{
	begTime = 0;
	endTime = 0;
	comparsion = 0;
	fileOp = 0;
	swaps = 0;
}


Counter::~Counter()
{
}
