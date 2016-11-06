#include "stdafx.h"
#include "BubbleExternalSort.h"


void BubbleExternalSort::sort(long int *a, long long length)
{
	int b;
	bool swapped;
	for (int i = 0; i < length - 1; i++) {
		swapped = false;
		for (int j = 0; j < length - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
				swapped = true;
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
