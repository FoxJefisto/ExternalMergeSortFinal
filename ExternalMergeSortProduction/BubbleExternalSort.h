#pragma once
#include "ExternalMergeSort.h"
class BubbleExternalSort :
	public ExternalMergeSort
{
public:
	virtual void sort(long int *, long long);
	BubbleExternalSort();
	~BubbleExternalSort();
};

