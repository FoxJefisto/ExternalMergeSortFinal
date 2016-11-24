#pragma once
#include "ExternalMergeSort.h"

/*!
\brief Класс внешней многофазной сортировки слиянием, использующий внутреннюю быструю сортировку.
\author Alexander Filippov
\date Ноябрь 2016 года

Наследуется от ExternalMergeSort, перегружает метод внутренней сортировки, который осуществляет быструю сортировку последовательности.
*/
class QuickExternalSort :
	public ExternalMergeSort
{
private:
	/*!
	\brief Сортирует последовательность длиной size методом быстрой сортировки итеративным методом.
	\param[in] arr Массив, который необходимо отсортировать.
	\param[in] size Длина массива.

	Сортирует последовательность длиной size методом быстрой сортировки.
	*/
	void QuickExternalSort::qSortI(long long *arr, long long size);
	/*!
	\brief Сортирует последовательность длиной size методом быстрой сортировки.
	\param[in] arr Массив, который необходимо отсортировать.
	\param[in] size Длина массива.

	Виртуальный метод. Перегружен в классе.
	Вызывет qSortI(...), который сортирует последовательность длиной size методом быстрой сортировки.
	*/
	virtual void QuickExternalSort::sort(long long *arr, long long size);
public:
	/*!
	\brief Пустой конструктор класса.

	Обнуляет атрибуты.
	*/
	QuickExternalSort();
	/*!
	\brief Пустой виртуальный деструктор класса.

	Освобождает выделенную память.
	*/
	~QuickExternalSort();
};

