#include "stdafx.h"
#include "QuickExternalSort.h"
#define MAXSTACK 100000

void QuickExternalSort::sort(long long * mas, long long size)
{
	//run_sort(mas, 0, size-1);
	qSortI(mas, size);
}

QuickExternalSort::QuickExternalSort()
{
	
}


void QuickExternalSort::qSortI(long long *a, long long size) {

	long long i, j; // указатели, участвующие в разделении
	long long lb, ub; // границы сортируемого в цикле фрагмента

	long long lbstack[MAXSTACK], ubstack[MAXSTACK]; // стек запросов
											   // каждый запрос задаетс€ парой значений,
											   // а именно: левой(lbstack) и правой(ubstack)
											   // границами промежутка
	long long stackpos = 1; // текуща€ позици€ стека
	long long ppos; // середина массива
	long long pivot; // опорный элемент
	long long temp;

	lbstack[1] = 0;
	ubstack[1] = size - 1;

	do {
		// ¬з€ть границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// Ўаг 1. –азделение по элементу pivot
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

			// —ейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// ¬озможен случай, когда указатель i или j выходит за границу массива

			// Ўаги 2, 3. ќтправл€ем большую часть в стек и двигаем lb,ub
			counter.incComparsion(1);
			if (i < ppos) { // права€ часть больше
				counter.incComparsion(1);
				if (i < ub) { // если в ней больше 1 элемента - нужно
					stackpos++; // сортировать, запрос в стек
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j; // следующа€ итераци€ разделени€
						// будет работать с левой частью
			}
			else { // лева€ часть больше
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

QuickExternalSort::~QuickExternalSort()
{
}
