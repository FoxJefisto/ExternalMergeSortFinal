#include "stdafx.h"
#include "QuickExternalSort.h"


void QuickExternalSort::sort(long int * mas, long long size)
{
	run_sort(mas, 0, size-1);
}

QuickExternalSort::QuickExternalSort()
{
	
}


int QuickExternalSort::run_sort(long int *mas, long long first, long long last) {
	int pivot = 0;
	if (first < last) {
		pivot = pivot_mas(mas, first, last);
		run_sort(mas, first, pivot - 1);
		run_sort(mas, pivot + 1, last);
	}
	return 1;
}

long int * QuickExternalSort::swap(long int *mas, long long x, long long y) {
	int buf = 0;
	buf = mas[x];
	mas[x] = mas[y];
	mas[y] = buf;
	return mas;
}

long long QuickExternalSort::pivot_mas(long int *mas, long long first, long long last) {
	long long PivotValue = mas[first];
	long long	PivotPoint = first;
	long long index = 0;
	for (index = first + 1; index <= last; index++) {
		if (mas[index] < PivotValue) {
			PivotPoint = PivotPoint + 1;
			mas = swap(mas, PivotPoint, index);
		}
	}
	mas = swap(mas, first, PivotPoint); // перенососевогозначениянанужноеместо
	return PivotPoint;

}

QuickExternalSort::~QuickExternalSort()
{
}
