#pragma once
#include "ExternalMergeSort.h"
class HeapExternalSort :
	public ExternalMergeSort
{
private: 
	void HeapExternalSort::iswap(long int &n1, long int &n2);
public:
	virtual void HeapExternalSort::sort(long int*  heap, long long n);
	HeapExternalSort();
	~HeapExternalSort();
};

