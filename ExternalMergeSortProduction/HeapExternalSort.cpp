#include "stdafx.h"
#include "HeapExternalSort.h"


HeapExternalSort::HeapExternalSort()
{
}


void HeapExternalSort::siftDown(long long *numbers, long long root, long long bottom) {
	int done, maxChild, temp;
	done = 0;
	while ((root * 2 <= bottom) && (!done)) {
		counter.incComparsion(1);
		if (root * 2 == bottom)
			maxChild = root * 2;
		else if (numbers[root * 2] > numbers[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		counter.incComparsion(1);
		if (numbers[root] < numbers[maxChild]) {
			temp = numbers[root];
			counter.incSwaps();
			numbers[root] = numbers[maxChild];
			numbers[maxChild] = temp;
			root = maxChild;
		}
		else
			done = 1;
	}
}
void HeapExternalSort::sort(long long *numbers, long long array_size) {
	long long i, temp;
	for (i = (array_size / 2) - 1; i >= 0; i--)
		siftDown(numbers, i, array_size);
	for (i = array_size - 1; i >= 1; i--) {
		counter.incSwaps();
		temp = numbers[0];
		numbers[0] = numbers[i];
		numbers[i] = temp;
		siftDown(numbers, 0, i - 1);
	}
}


HeapExternalSort::~HeapExternalSort()
{
}
