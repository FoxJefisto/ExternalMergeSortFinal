#pragma once
#include "ExternalMergeSort.h"
class QuickExternalSort :
	public ExternalMergeSort
{
private:
	void QuickExternalSort::qSortI(long long *mas, long long size);
public:
	virtual void QuickExternalSort::sort(long long *mas, long long);
	QuickExternalSort();
	~QuickExternalSort();
};

