#pragma once
#include "ExternalMergeSort.h"
class HeapExternalSort :
	public ExternalMergeSort
{
private: 
	void HeapExternalSort::siftDown(long long *numbers, long long root, long long bottom);
public:
	virtual void HeapExternalSort::sort(long long *numbers, long long array_size);
	HeapExternalSort();
	~HeapExternalSort();
};

