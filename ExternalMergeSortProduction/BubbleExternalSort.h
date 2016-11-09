#pragma once
#include "ExternalMergeSort.h"
class BubbleExternalSort :
	public ExternalMergeSort
{
public:
	virtual void sort(long long *, long long);
	BubbleExternalSort();
	~BubbleExternalSort();
};

