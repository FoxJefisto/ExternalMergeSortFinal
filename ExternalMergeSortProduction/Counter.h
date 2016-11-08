#pragma once
#include <ctime>

using namespace std;

class Counter
{
private:
	long begTime;
	long endTime;
	long comparsion;
	long fileOp;
public:
	Counter();
	void setBegTime();
	long setEndTime();
	long getTimeInterval();
	void incComparsion(long n);
	long getComparsion();
	void incFileOp(long n);
	long getFileOp();
	void clear();
	~Counter();
};

