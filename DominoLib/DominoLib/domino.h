#pragma once
#define SIZE 28
	class domino
	{
	private:
		struct bonetype {
			short int top;
			short int lower;
		};
	public:
		bonetype bone[SIZE];
		short int size;
	private:
		void shiftup(short int);
		void qsort(int left, int right);
		int exsist(short int, short int);
	public:
		domino();
		domino(short int);
		domino(short int, short int);
		domino copypart(short int beg, short int end);
		domino remove(const domino &);
		domino sort();
		void addbone(bonetype &);
		~domino();   //тривиальный
	};

