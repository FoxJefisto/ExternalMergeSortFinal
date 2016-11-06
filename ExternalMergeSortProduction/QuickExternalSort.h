#pragma once
#include "ExternalMergeSort.h"
class QuickExternalSort :
	public ExternalMergeSort
{
private:
	int QuickExternalSort::run_sort(long int *mas, long long first, long long last);
	long int * QuickExternalSort::swap(long int *mas, long long x, long long y);
	long long QuickExternalSort::pivot_mas(long int *mas, long long first, long long last);
public:
	virtual void QuickExternalSort::sort(long int *mas, long long);
	QuickExternalSort();
	~QuickExternalSort();
};

