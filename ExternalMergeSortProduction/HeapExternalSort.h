#pragma once
#include "ExternalMergeSort.h"
class HeapExternalSort :
	public ExternalMergeSort
{
private: 
	void HeapExternalSort::iswap(long long &n1, long long &n2);
public:
	virtual void HeapExternalSort::sort(long long*  heap, long long n);
	HeapExternalSort();
	~HeapExternalSort();
};

