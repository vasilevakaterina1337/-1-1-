#include <iostream>
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

using namespace std;

int main()
{
    setlocale(0, "ru");
    srand(time(0));
    int choice, N;
    cout << "Введите номер лабораторной работы: " << endl
        << "Лабораторная работа №1 (ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ)" << endl
        << "Лабораторная работа №2 (ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ)" << endl
        << "Лабораторная работа №3 (ДВУМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ. УКАЗАТЕЛИ)" << endl
        << "Лабораторная работа №4 (РАБОТА СО СТРОКАМИ)" << endl;
    cin >> choice;
    switch (choice) {
        case 1: {
            system("cls");
            cout << "Лабораторная работа № 1 (ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ)" << endl;
            lab1();
            cout << endl;
            main();
            break;
        }
        case 2: {
            system("cls");
            cout << "Лабораторная работа № 2 (ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ)" << endl;
            lab2();
            break;
        }
        case 3: {
            system("cls");
            cout << "Лабораторная работа №3" << endl;
            lab3();
            break;
        }
        case 4: {
            system("cls");
            cout << "Лабораторная работа №4" << endl;
            lab4();
            break;
        }
        default: {
            cout << "Введён несуществующий номер. Введите другой номер" << endl;
            main();
            break;
        }
    }
}

