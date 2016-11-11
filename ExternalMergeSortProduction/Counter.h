#pragma once
#include <ctime>

using namespace std;


/*!
\brief Класс Счетчик.
\author Alexander Filippov
\date Ноябрь 2016 года

Класс, отвечающий за подсчет характеристик сортировки.
*/
class Counter
{
private:
	/*!
	\brief Начальное время.

	Число тактов программы на момент начала сортировки.
	*/
	long long begTime;
	/*!
	\brief Конечное время.

	Число тактов программы на момент оконачания сортировки.
	*/
	long long endTime;
	/*!
	\brief Число сравнений.

	*/
	long long comparsion;
	/*!
	\brief Число операций с файлами.
	Число записей в файл и чтений из файла чисел.
	*/
	long long fileOp;
	/*!
	\brief Число перестановок.
	Подсчет производится только в методе внутренней сортировки, т.к. вне её не имеет смысла.
	*/
	long long swaps;
public:
	/*!
	\brief Пустой конструктор класса.
	Обнуляет счетчие.
	*/
	Counter();
	/*!
	
	\brief Вызов необходимого метода.
	\param[in] ch Выбор пользователя
	\return Булево значение - если true, то продолжаем работу программу, если нет, то выход из бесконечного цикла.
	*/
	void setBegTime();
	long setEndTime();
	long getTimeInterval();
	void incSwaps();
	long getSwaps();
	void incComparsion(long long n);
	long getComparsion();
	void incFileOp(long long n);
	long getFileOp();
	void clear();
	~Counter();
};

