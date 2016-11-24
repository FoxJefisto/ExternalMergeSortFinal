#pragma once
#include "ExternalMergeSort.h"

/*!
\brief Класс внешней многофазной сортировки слиянием, использующий внутреннюю пирамидальную сортировку
\author Alexander Filippov
\date Ноябрь 2016 года

Наследуется от ExternalMergeSort, перегружает метод внутренней сортировки, который осуществляет пирамидальную сортировку последовательности.
*/
class HeapExternalSort :
	public ExternalMergeSort
{
private: 
	/*!
	\brief Получение нового опорного элемента
	\param[in] arr Сортируемый массив.
	\param[in] root Корневой элемент.
	\param[in] bottom Наименьший элемент.

	Получает новый опроный элемент пирамидальной сортировки, исходя из передаваемых параметров.
	*/
	void HeapExternalSort::siftDown(long long *arr, long long root, long long bottom);
	/*!
	\brief Сортирует последовательность длиной size методом пирамидальной сортировки.
	\param[in] arr Массив, который необходимо отсортировать.
	\param[in] size Длина массива.

	Виртуальный метод. Перегружен в классе.
	Сортирует последовательность длиной size методом пирамидальной сортировки.
	*/
	virtual void HeapExternalSort::sort(long long *numbers, long long array_size);
public:
	
	/*!
	\brief Пустой конструктор класса.

	Обнуляет атрибуты.
	*/
	HeapExternalSort();
	/*!
	\brief Пустой виртуальный деструктор класса.

	Освобождает выделенную память.
	*/
	~HeapExternalSort();
};

