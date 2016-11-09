#include "stdafx.h"
#include "BubbleExternalSort.h"


void BubbleExternalSort::sort(long long *a, long long length)
{
	long long b;
	bool swapped;
	for (int i = 0; i < length - 1; i++) {
		swapped = false;
		for (int j = 0; j < length - i - 1; j++) {
			counter.incComparsion(1);
			if (a[j] > a[j + 1]) {
				b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
				swapped = true;
				counter.incSwaps();
			}
		}
		if (!swapped)
			break;
	}
}

BubbleExternalSort::BubbleExternalSort()
{
}


BubbleExternalSort::~BubbleExternalSort()
{
}
