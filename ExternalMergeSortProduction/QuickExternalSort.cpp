#include "stdafx.h"
#include "QuickExternalSort.h"
#define MAXSTACK 10000

void QuickExternalSort::sort(long int * mas, long long size)
{
	//run_sort(mas, 0, size-1);
	qSortI(mas, size);
}

QuickExternalSort::QuickExternalSort()
{
	
}


void QuickExternalSort::qSortI(long int *a, long long size) {

	long i, j; // указатели, участвующие в разделении
	long lb, ub; // границы сортируемого в цикле фрагмента

	long lbstack[MAXSTACK], ubstack[MAXSTACK]; // стек запросов
											   // каждый запрос задается парой значений,
											   // а именно: левой(lbstack) и правой(ubstack)
											   // границами промежутка
	long stackpos = 1; // текущая позиция стека
	long ppos; // середина массива
	long int pivot; // опорный элемент
	long int temp;

	lbstack[1] = 0;
	ubstack[1] = size - 1;

	do {
		// Взять границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// Шаг 1. Разделение по элементу pivot
			ppos = (lb + ub) >> 1;
			i = lb; j = ub; pivot = a[ppos];
			do {
				while (a[i] < pivot) i++;
				while (pivot < a[j]) j--;
				counter.incComparsion(1);
				if (i <= j) {
					counter.incSwaps();
					temp = a[i]; a[i] = a[j]; a[j] = temp;
					i++; j--;
				}
			} while (i <= j);

			// Сейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// Возможен случай, когда указатель i или j выходит за границу массива

			// Шаги 2, 3. Отправляем большую часть в стек и двигаем lb,ub
			counter.incComparsion(1);
			if (i < ppos) { // правая часть больше
				counter.incComparsion(1);
				if (i < ub) { // если в ней больше 1 элемента - нужно
					stackpos++; // сортировать, запрос в стек
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j; // следующая итерация разделения
						// будет работать с левой частью
			}
			else { // левая часть больше
				counter.incComparsion(1);
				if (j > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = j;
				}
				lb = i;
			}
		} while (lb < ub); // пока в меньшей части более 1 элемента
	} while (stackpos != 0); // пока есть запросы в стеке
}


int QuickExternalSort::run_sort(long int *mas, long long first, long long last) {
	long long pivot = 0;
	counter.incComparsion(1);
	if (first < last) {
		pivot = pivot_mas(mas, first, last);
		//run_sort(mas, first, pivot - 1);
		last = pivot - 1;
		run_sort(mas, pivot + 1, last);
	}
	return 1;
}

long int * QuickExternalSort::swap(long int *mas, long long x, long long y) {
	counter.incSwaps();
	long int buf = 0;
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
		counter.incComparsion(1);
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
