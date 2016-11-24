#pragma once
#include "ExternalMergeSort.h"

/*!
\brief Класс внешней многофазной сортировки слиянием, использующий внутреннюю пузырьковую сортировку.
\author Alexander Filippov
\date Ноябрь 2016 года

Наследуется от ExternalMergeSort, перегружает метод внутренней сортировки, который осуществляет пузырьковую сортировку последовательности.
*/
class BubbleExternalSort :
	public ExternalMergeSort
{
private:
	/*!
	\brief Сортирует последовательность длиной size методом пузырьковой сортировки.
	\param[in] arr Массив, который необходимо отсортировать.
	\param[in] size Длина массива.

	Виртуальный метод. Перегружен в классе.
	Сортирует последовательность длиной size методом пузырьковой сортировки.
	*/
	virtual void sort(long long *arr, long long size);
public:
	
	/*!
	\brief Пустой конструктор класса.

	Обнуляет атрибуты.
	*/
	BubbleExternalSort();
	/*!
	\brief Пустой виртуальный деструктор класса.

	Освобождает выделенную память.
	*/
	~BubbleExternalSort();
};

