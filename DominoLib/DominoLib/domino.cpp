#include <stdexcept>
#include <stdlib.h>
#include "domino.h"
#include <ctime>
#pragma once
using namespace std;

domino::domino()   //пустой конструктор
{
	for (int i = 0; i < SIZE; i++) {
		bone[i].top = 0;
		bone[i].lower = 0;
	}
	size = 0;
}

domino::domino(short int amount) {    //рандомный конструктор
	int top, lower;
	if ((amount <= 0) || (amount > 28)) {
		throw invalid_argument("Such an amount of bone can not be created");
	}
	size = 0;
	srand(time(0));
	for (int i = 0; i < amount; i++) {
		do {
			top = rand() % 7;
			lower = rand() % 7;
		} while (this->exsist(top, lower));
		bone[i].top = top;
		bone[i].lower = lower;
		size++;
	}
	for (int i = amount; i < SIZE; i++) {
		bone[i].top = 0;
		bone[i].lower = 0;
	}
}

int domino::exsist(short int top, short int lower) {
	for (int i = 0; i < size; i++) {
		if ((bone[i].top == top) && (bone[i].lower == lower) || (bone[i].top == lower) && (bone[i].lower == top)) {
			return 1;
		}
	}
	return 0;
}

domino::domino(short int top, short int lower) {    //конструктор инициализирующий одну кость
	if ((top < 0) || (top > 6) || (lower < 0) || (lower > 6)) {
		throw invalid_argument("Incorrect number of points");
	}
	bone[0].top = top;
	bone[0].lower = lower;
	for (int i = 1; i < SIZE; i++) {
		bone[i].top = 0;
		bone[i].lower = 0;
	}
	size = 1;
}

void domino::shiftup(short int k) {   //смещение на один элемент вверх
	for (int i = k; i < size - 1; i++) {
		bone[i].top = bone[i + 1].top;
		bone[i].lower = bone[i + 1].lower;
	}
	size--;
}

domino domino::remove(const domino &b) {    //удаление костей
	if (size == 0) {
		throw logic_error("Class is empty");
	}
	if (b.size > 1) {
		throw invalid_argument("A copy contains more than one bone");
	}
	for (int i = 0; i < size; i++) {
		if ((bone[i].top == b.bone[0].top) && (bone[i].lower == b.bone[0].lower) || (bone[i].top == b.bone[0].lower) && (bone[i].lower == b.bone[0].top)) {
			shiftup(i);
			i--;
		}
	}
	return *this;
}


void domino::addbone(bonetype &exam) {
	if (size == 28) {
		throw logic_error("There is no place");
	}
	bone[size].top = exam.top;
	bone[size].lower = exam.lower;
	size++;
}

domino domino::sort() {
	if (size == 0) {
		throw logic_error("Class is empty");
	}
	this->qsort(0, size - 1);
	return *this;
}

void domino::qsort(int left, int right)   //быстрая сортировка
{
	int l = left;
	int r = right;
	bonetype foo;
	int mid = bone[(l + r) / 2].lower + bone[(l + r) / 2].top;
	while (l <= r) {
		while ((bone[l].lower + bone[l].top < mid) && (l <= right)) {
			l++;
		}
		while ((bone[r].lower + bone[r].top > mid) && (r >= left)) {
			r--;
		}
		if (l <= r) {
			foo.lower = bone[l].lower;
			foo.top = bone[l].top;
			bone[l].top = bone[r].top;
			bone[l].lower = bone[r].lower;
			bone[r].top = foo.top;
			bone[r].lower = foo.lower;
			l++;
			r--;
		}
	}
	if (r > left) {
		this->qsort(left, r);
	}
	if (l < right) {
		this->qsort(l, right);
	}
	return;
}

domino domino::copypart(short int beg, short int end)
{
	domino buf;
	for (short int i = beg; i < end; i++) {
		buf.bone[i - beg] = bone[i];
	}
	buf.size = end - beg;
	return buf;
}

domino::~domino()
{
}

