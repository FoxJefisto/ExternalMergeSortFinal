#pragma once
#include <ctime>

using namespace std;

class Counter
{
private:
	long long begTime;
	long long endTime;
	long long comparsion;
	long long fileOp;
	long long swaps;
public:
	Counter();
	void setBegTime();
	long setEndTime();
	long getTimeInterval();
	void incSwaps();
	long getSwaps();
	void incComparsion(long long n);
	long getComparsion();
	void incFileOp(long long n);
	long getFileOp();
	void clear();
	~Counter();
};

