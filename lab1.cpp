#include <cmath>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <typeinfo>
#include <string>  
#include "kursach.h"
using namespace std;

void lab1() {
	setlocale(0, "");
	int intNum;
	cin >> intNum;
	cout << (intNum << 1);




	cout << "\n\nЗадание 1 \n";
	cout << "int: " << sizeof(int) << " байта\n";
	cout << "short int: " << sizeof(short int) << " байта\n";
	cout << "long int: " << sizeof(long int) << " байта\n";
	cout << "float: " << sizeof(float) << " байта\n";
	cout << "double: " << sizeof(double) << " байт\n";
	cout << "long double: " << sizeof(long double) << " байт\n";
	cout << "char: " << sizeof(char) << " байт\n";
	cout << "bool: " << sizeof(bool) << " байт\n";





	cout << "\n\nЗадание 2 \n";
	int intNumber;
	cin >> intNumber;// Значение числа
	unsigned int order = 32; // Количество разрядов
	unsigned int mask = 1 << order - 1; // Маска побитового сравнения
	cout << "intNumber: " << &intNumber << " : " << intNumber << endl;
	for (int i = 0; i < order; i++)
	{
		if (intNumber & mask >> i) {
			cout << '1';
		}
		else {
			cout << '0';
		}
		if ((i + 1) % 8 == 0) {
			cout << ' ';
		}
	}




	cout << "\n\nЗадание 3 \n";

	union { float floatNumber; int intNumber1; }; cin >> floatNumber; //int принимает значение float


	int orderF = sizeof(float) * 8;
	unsigned int maskF = 1 << (orderF - 1);
	for (int i = 0; i < orderF; i++) {
		if (intNumber1 & maskF >> i) {
			cout << '1';
		}
		else {
			cout << '0';
		}
		if ((i + 1) % 8 == 0) {
			cout << ' ';
		}

	}



	cout << "\n\nЗадание 4 \n";

	union u {
		unsigned int arr[2];
		double numberDouble;
	} u;

	cin >> u.numberDouble;
	int totalSize = sizeof(int) * 8;
	for (int j = 2 - 1; j >= 0; j--) {
		for (int i = 0; i < totalSize; i++) {
			int shift = totalSize - 1 - i;
			int mask = 1 << shift;

			int nextDigit = (u.arr[j] & mask) >> shift;

			cout << nextDigit;

			if ((i + 1) % 8 == 0) {
				cout << " ";
			}
		}
	}




	cout << "\n\nЗадание 5 \n";
	//для int
	union c {
		int int_number;
		unsigned int uint_number;
	} c;

	cout << "Введите ваше число типа int: ";
	cin >> c.int_number;

	int totalSizeInt = sizeof(c.int_number) * 8;

	cout << "Введите номер бита, который нужно поменять: ";
	int numberBitInt;
	cin >> numberBitInt;

	unsigned int negatMask = 1 << numberBitInt;
	c.uint_number = c.uint_number ^ negatMask;
	for (int i = 0; i < totalSizeInt; i++) {
		int shiftInt = totalSizeInt - 1 - i;
		int maskInt = 1 << shiftInt;

		int nextDigitInt = (c.uint_number & maskInt) >> shiftInt;
		cout << nextDigitInt;

		if ((i + 1) % 8 == 0) {
			cout << " ";
		}
	}
	cout << c.uint_number << endl;


	//для float
	union f {
		float float_number;
		unsigned int ffloat_number;
	} f;

	cout << "\n\nВведите ваше число типа float: ";
	cin >> f.float_number;

	int totalSizeFloat = sizeof(f.float_number) * 8;

	cout << "Введите номер бита, который нужно поменять: ";
	int numberBitFloat;
	cin >> numberBitFloat;

	unsigned int negatMaskFloat = 1 << numberBitFloat;
	f.ffloat_number = f.ffloat_number ^ negatMaskFloat;

	for (int i = 0; i < totalSizeFloat; i++) {
		int shiftFloat = totalSizeFloat - 1 - i;
		int maskFloat = 1 << shiftFloat;

		int nextDigitFloat = (f.ffloat_number & maskFloat) >> shiftFloat;
		cout << nextDigitFloat;

		if ((i + 1) % 8 == 0) {
			cout << " ";
		}
	}
	cout << f.ffloat_number << endl;



	//для double
	union d {
		double double_number;
		unsigned int arr[2];
	} d;

	cout << "\n\nВведите ваше число типа double: ";
	cin >> d.double_number;

	int totalSizeDouble = sizeof(int) * 8;

	cout << "Введите номер бита, который нужно поменять: ";
	int numberBitDouble;
	cin >> numberBitDouble;

	unsigned int negatMaskDouble = 1 << numberBitDouble;
	if (numberBitDouble < 32) {
		d.arr[0] = d.arr[0] ^ negatMaskDouble;
	}
	else {
		d.arr[1] = d.arr[1] ^ negatMaskDouble;
	}
	for (int j = 2 - 1; j >= 0; j--) {
		for (int i = 0; i < totalSizeDouble; i++) {
			int shiftDouble = totalSizeDouble - 1 - i;
			int maskDouble = 1 << shiftDouble;

			int nextDigitDouble = (d.arr[j] & maskDouble) >> shiftDouble;

			cout << nextDigitDouble;

			if ((i + 1) % 8 == 0) {
				cout << " ";
			}
		}
	}
	cout << d.arr[2] << endl;
}