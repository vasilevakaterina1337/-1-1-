#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> 
#include <conio.h>   
#include "kursach.h"
using namespace std;

// Глобальные переменные (указатели)
int** matrix1;  // Матрица-спираль
int** matrix2;  // Матрица-змейка
int N;          // Размер матрицы

// Функция для очистки экрана 
void clearScreen() {
    system("cls");
}

// Функция для задержки
void delay(int milliseconds) {
    Sleep(milliseconds);
}

// Функция для печати матрицы (с использованием указателей)
void printMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << *(*(matrix + i) + j) << "\t";
        }
        cout << endl;
    }
}

// Функция для печати матрицы с выделенным элементом
void printMatrixHome(int** matrix, int N, int maxLine, int maxColumn) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == maxLine && j == maxColumn) {
                cout << "[" << *(*(matrix + i) + j) << "]" << "\t";
            }
            else {
                cout << *(*(matrix + i) + j) << "\t";
            }
        }
        cout << endl;
    }
}

// Функция для копирования матрицы
void copyMatrix(int** src, int** dst, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(dst + i) + j) = *(*(src + i) + j);
        }
    }
}

// Функция быстрой сортировки (работает с указателями)
void quickSort(int* arr, int begin, int end) {
    if (begin >= end) return;

    int left = begin;
    int right = end;
    int pivot = *(arr + (left + right) / 2);

    while (left <= right) {
        while (*(arr + left) < pivot) left++;
        while (*(arr + right) > pivot) right--;

        if (left <= right) {
            int temp = *(arr + left);
            *(arr + left) = *(arr + right);
            *(arr + right) = temp;

            left++;
            right--;
        }
    }

    if (begin < right) quickSort(arr, begin, right);
    if (left < end) quickSort(arr, left, end);
}

// Преобразование матрицы-змейки в одномерный массив
void matrixToArray(int** matrix, int* arr, int N) {
    int index = 0;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // Четные строки: слева направо
            for (int j = 0; j < N; j++) {
                *(arr + index) = *(*(matrix + i) + j);
                index++;
            }
        }
        else {
            // Нечетные строки: справа налево
            for (int j = N - 1; j >= 0; j--) {
                *(arr + index) = *(*(matrix + i) + j);
                index++;
            }
        }
    }
}

// Перестановка блоков по часовой стрелке
void clockPermutation(int** originalMatrix, int** finalMatrix, int N) {
    int half = N / 2;

    // Копируем исходную матрицу
    copyMatrix(originalMatrix, finalMatrix, N);

    // Выделяем память для временного блока
    int** block1 = new int* [half];
    for (int i = 0; i < half; i++) {
        *(block1 + i) = new int[half];
    }

    // Сохраняем левый верхний блок
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(block1 + i) + j) = *(*(finalMatrix + i) + j);
        }
    }

    // Левый верхний <- Левый нижний
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(finalMatrix + i) + j) = *(*(finalMatrix + i + half) + j);
        }
    }

    // Левый нижний <- Правый нижний
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(finalMatrix + i + half) + j) = *(*(finalMatrix + i + half) + j + half);
        }
    }

    // Правый нижний <- Правый верхний
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(finalMatrix + i + half) + j + half) = *(*(finalMatrix + i) + j + half);
        }
    }

    // Правый верхний <- Сохраненный блок
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *(*(finalMatrix + i) + j + half) = *(*(block1 + i) + j);
        }
    }

    // Освобождаем память
    for (int i = 0; i < half; i++) {
        delete[] * (block1 + i);
    }
    delete[] block1;
}

// Перестановка блоков по диагонали
void diagonalPermutation(int** originalMatrix, int** finalMatrix, int N) {
    int half = N / 2;
    copyMatrix(originalMatrix, finalMatrix, N);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Меняем левый верхний и правый нижний блоки
            int block = *(*(finalMatrix + i) + j);
            *(*(finalMatrix + i) + j) = *(*(finalMatrix + i + half) + j + half);
            *(*(finalMatrix + i + half) + j + half) = block;

            // Меняем правый верхний и левый нижний блоки
            block = *(*(finalMatrix + i) + j + half);
            *(*(finalMatrix + i) + j + half) = *(*(finalMatrix + i + half) + j);
            *(*(finalMatrix + i + half) + j) = block;
        }
    }
}

// Перестановка блоков по вертикали
void verticalPermutation(int** originalMatrix, int** finalMatrix, int N) {
    int half = N / 2;
    copyMatrix(originalMatrix, finalMatrix, N);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Левая половина: меняем верх и низ
            int block = *(*(finalMatrix + i) + j);
            *(*(finalMatrix + i) + j) = *(*(finalMatrix + i + half) + j);
            *(*(finalMatrix + i + half) + j) = block;

            // Правая половина: меняем верх и низ
            block = *(*(finalMatrix + i) + j + half);
            *(*(finalMatrix + i) + j + half) = *(*(finalMatrix + i + half) + j + half);
            *(*(finalMatrix + i + half) + j + half) = block;
        }
    }
}

// Перестановка блоков по горизонтали
void horisontalPermutation(int** originalMatrix, int** finalMatrix, int N) {
    int half = N / 2;
    copyMatrix(originalMatrix, finalMatrix, N);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Верхняя половина: меняем лево и право
            int block = *(*(finalMatrix + i) + j);
            *(*(finalMatrix + i) + j) = *(*(finalMatrix + i) + j + half);
            *(*(finalMatrix + i) + j + half) = block;

            // Нижняя половина: меняем лево и право
            block = *(*(finalMatrix + i + half) + j);
            *(*(finalMatrix + i + half) + j) = *(*(finalMatrix + i + half) + j + half);
            *(*(finalMatrix + i + half) + j + half) = block;
        }
    }
}

// Выбор матрицы для перестановки блоков
void choiseMatrix(int N) {
    cout << "Выберите матрицу для перестановки блоков (1 - спираль, 2 - змейка): ";

    int choise;
    cin >> choise;

    int** matrix;
    if (choise == 1) {
        matrix = matrix1;
        cout << "Выбрана матрица-спираль\n";
    }
    else {
        matrix = matrix2;
        cout << "Выбрана матрица-змейка\n";
    }

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, N);

    cout << "\nНажмите Enter для продолжения...";
    cin.ignore();
    cin.get();
    clearScreen();

    // 1. Перестановка по часовой стрелке
    cout << "1. Перестановка по часовой стрелке:\n\n";
    int** result1 = new int* [N];
    for (int i = 0; i < N; i++) *(result1 + i) = new int[N];

    clockPermutation(matrix, result1, N);
    printMatrix(result1, N);

    for (int i = 0; i < N; i++) delete[] * (result1 + i);
    delete[] result1;

    cout << "\nНажмите Enter для продолжения...";
    cin.get();
    clearScreen();

    // 2. Перестановка по диагонали
    cout << "2. Перестановка по диагонали:\n\n";
    int** result2 = new int* [N];
    for (int i = 0; i < N; i++) *(result2 + i) = new int[N];

    diagonalPermutation(matrix, result2, N);
    printMatrix(result2, N);

    for (int i = 0; i < N; i++) delete[] * (result2 + i);
    delete[] result2;

    cout << "\nНажмите Enter для продолжения...";
    cin.get();
    clearScreen();

    // 3. Перестановка по вертикали
    cout << "3. Перестановка по вертикали:\n\n";
    int** result3 = new int* [N];
    for (int i = 0; i < N; i++) *(result3 + i) = new int[N];

    verticalPermutation(matrix, result3, N);
    printMatrix(result3, N);

    for (int i = 0; i < N; i++) delete[] * (result3 + i);
    delete[] result3;

    cout << "\nНажмите Enter для продолжения...";
    cin.get();
    clearScreen();

    // 4. Перестановка по горизонтали
    cout << "4. Перестановка по горизонтали:\n\n";
    int** result4 = new int* [N];
    for (int i = 0; i < N; i++) *(result4 + i) = new int[N];

    horisontalPermutation(matrix, result4, N);
    printMatrix(result4, N);

    for (int i = 0; i < N; i++) delete[] * (result4 + i);
    delete[] result4;
}

// Математические операции с матрицами
void additionToMatrix(int** matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(matrix + i) + j) = *(*(matrix + i) + j) + value;
        }
    }
}

void subtractionToMatrix(int** matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(matrix + i) + j) = *(*(matrix + i) + j) - value;
        }
    }
}

void multiplicatoinToMatrix(int** matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(matrix + i) + j) = *(*(matrix + i) + j) * value;
        }
    }
}

void divisionToMatrix(int** matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(*(matrix + i) + j) = *(*(matrix + i) + j) / value;
        }
    }
}

// Интерфейс для операций с матрицами
void manipulateWithMatrix() {
    cout << "Выберите матрицу:\n";
    cout << "1. Матрица-спираль\n";
    cout << "2. Матрица-змейка\n";
    cout << "Ваш выбор (1 или 2): ";

    int matrixChoice;
    cin >> matrixChoice;

    int** selectedMatrix = nullptr;

    if (matrixChoice == 1) {
        selectedMatrix = matrix1;
        cout << "\nВыбрана матрица-спираль\n";
    }
    else if (matrixChoice == 2) {
        selectedMatrix = matrix2;
        cout << "\nВыбрана матрица-змейка\n";
    }
    else {
        cout << "Неверный выбор!\n";
        return;
    }

    cout << "\nИсходная матрица:\n";
    printMatrix(selectedMatrix, N);

    cout << "\nВыберите операцию:\n";
    cout << "1. Увеличить все элементы матрицы\n";
    cout << "2. Уменьшить все элементы матрицы\n";
    cout << "3. Умножить все элементы матрицы\n";
    cout << "4. Разделить все элементы матрицы\n";
    cout << "Ваш выбор (1-4): ";

    int operationChoice;
    cin >> operationChoice;

    cout << "\nМатрица до операции:\n";
    printMatrix(selectedMatrix, N);

    cout << "\nВведите число: ";
    int value;
    cin >> value;

    // Выполняем выбранную операцию
    switch (operationChoice) {
    case 1:
        additionToMatrix(selectedMatrix, N, value);
        cout << "\nВсе элементы увеличены на " << value << "\n";
        break;
    case 2:
        subtractionToMatrix(selectedMatrix, N, value);
        cout << "\nВсе элементы уменьшены на " << value << "\n";
        break;
    case 3:
        multiplicatoinToMatrix(selectedMatrix, N, value);
        cout << "\nВсе элементы умножены на " << value << "\n";
        break;
    case 4:
        if (value == 0) {
            cout << "\nОшибка: деление на ноль!\n";
            cout << "\nМатрица после операции:\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cout << "inf\t";
                }
                cout << endl;
            }
            return;
        }
        else {
            divisionToMatrix(selectedMatrix, N, value);
            cout << "\nВсе элементы разделены на " << value << "\n";
        }
        break;
    default:
        cout << "Неверный выбор операции!\n";
        return;
    }

    cout << "\nМатрица после операции:\n";
    printMatrix(selectedMatrix, N);
}

// Основная функция
void lab3() {
    setlocale(0, "RU");

    // Ввод размера матрицы
    cout << "Введите размер матрицы N (6, 8, 10): ";
    cin >> N;

    // Инициализация генератора случайных чисел
    srand(time(0));
    clearScreen();

    // Генерация случайных чисел
    int elements = N * N;
    int* randomNum = new int[elements];

    cout << "Сгенерированные случайные числа:\n";
    for (int i = 0; i < elements; i++) {
        *(randomNum + i) = rand() % (N * N) + 1;
        cout << *(randomNum + i) << " ";
        if ((i + 1) % N == 0) cout << endl;
    }

    // Создание и визуализация матрицы-спирали
    cout << "\nНажмите Enter для создания матрицы-спирали...";
    cin.ignore();
    cin.get();
    clearScreen();

    cout << "Создание матрицы-спирали:\n\n";
    matrix1 = new int* [N];
    for (int i = 0; i < N; i++) {
        *(matrix1 + i) = new int[N];
        for (int j = 0; j < N; j++) {
            *(*(matrix1 + i) + j) = 0;
        }
    }

    // Отображаем пустую матрицу
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " . ";
        }
        cout << endl;
    }

    delay(1000);

    // Заполнение спирали с визуализацией
    int randomIndex = 0;
    int left = 0, right = N - 1;
    int up = 0, down = N - 1;

    while (up <= down && left <= right) {
        // Вправо
        for (int j = left; j <= right; j++) {
            *(*(matrix1 + up) + j) = *(randomNum + randomIndex);
            randomIndex++;

            clearScreen();
            cout << "Заполнение спирали:\n\n";

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    int val = *(*(matrix1 + r) + c);
                    if (val == 0) cout << " . ";
                    else if (r == up && c == j) cout << val;
                    else cout << " " << val << " ";
                }
                cout << endl;
            }
            delay(300);
        }
        up++;

        // Вниз
        for (int i = up; i <= down; i++) {
            *(*(matrix1 + i) + right) = *(randomNum + randomIndex);
            randomIndex++;

            clearScreen();
            cout << "Заполнение спирали:\n\n";

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    int val = *(*(matrix1 + r) + c);
                    if (val == 0) cout << " . ";
                    else if (r == i && c == right) cout << val;
                    else cout << " " << val << " ";
                }
                cout << endl;
            }
            delay(300);
        }
        right--;

        // Влево
        if (up <= down) {
            for (int j = right; j >= left; j--) {
                *(*(matrix1 + down) + j) = *(randomNum + randomIndex);
                randomIndex++;

                clearScreen();
                cout << "Заполнение спирали:\n\n";

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        int val = *(*(matrix1 + r) + c);
                        if (val == 0) cout << " . ";
                        else if (r == down && c == j) cout << val;
                        else cout << " " << val << " ";
                    }
                    cout << endl;
                }
                delay(300);
            }
            down--;
        }

        // Вверх
        if (left <= right) {
            for (int i = down; i >= up; i--) {
                *(*(matrix1 + i) + left) = *(randomNum + randomIndex);
                randomIndex++;

                clearScreen();
                cout << "Заполнение спирали:\n\n";

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        int val = *(*(matrix1 + r) + c);
                        if (val == 0) cout << " . ";
                        else if (r == i && c == left) cout << val;
                        else cout << " " << val << " ";
                    }
                    cout << endl;
                }
                delay(300);
            }
            left++;
        }
    }

    // Создание и визуализация матрицы-змейки
    randomIndex = 0;
    cout << "\nНажмите Enter для создания матрицы-змейки...";
    cin.get();
    clearScreen();

    cout << "Создание матрицы-змейки:\n\n";
    matrix2 = new int* [N];
    for (int i = 0; i < N; i++) {
        *(matrix2 + i) = new int[N];
        for (int j = 0; j < N; j++) {
            *(*(matrix2 + i) + j) = 0;
        }
    }

    // Заполнение змейки с визуализацией
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // Четные строки: слева направо
            for (int j = 0; j < N; j++) {
                *(*(matrix2 + i) + j) = *(randomNum + randomIndex);
                randomIndex++;

                clearScreen();
                cout << "Заполнение змейки:\n\n";

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        int val = *(*(matrix2 + r) + c);
                        if (val == 0) cout << " . ";
                        else cout << " " << val << " ";
                    }
                    cout << endl;
                }
                delay(300);
            }
        }
        else {
            // Нечетные строки: справа налево
            for (int j = N - 1; j >= 0; j--) {
                *(*(matrix2 + i) + j) = *(randomNum + randomIndex);
                randomIndex++;

                clearScreen();
                cout << "Заполнение змейки:\n\n";

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        int val = *(*(matrix2 + r) + c);
                        if (val == 0) cout << " . ";
                        else cout << " " << val << " ";
                    }
                    cout << endl;
                }
                delay(300);
            }
        }
    }

    // Показ готовых матриц
    cout << "\nНажмите Enter для просмотра готовых матриц...";
    cin.get();
    clearScreen();

    cout << "Готовые матрицы:\n\n";
    cout << "a) Матрица-спираль:\n\n";
    printMatrix(matrix1, N);

    cout << "\nб) Матрица-змейка:\n\n";
    printMatrix(matrix2, N);

    // Перестановка блоков
    cout << "\nНажмите Enter для выбора матрицы для перестановки блоков...";
    cin.get();
    choiseMatrix(N);

    // Сортировка массива из матрицы-змейки
    int* arr = new int[N * N];
    matrixToArray(matrix2, arr, N);

    clearScreen();
    cout << "Массив из матрицы-змейки до сортировки:\n";
    for (int i = 0; i < N * N; i++) {
        cout << *(arr + i) << " ";
    }

    quickSort(arr, 0, N * N - 1);

    cout << "\n\nНажмите Enter для просмотра отсортированного массива...";
    cin.get();
    clearScreen();

    cout << "Массив из матрицы-змейки после сортировки:\n";
    for (int i = 0; i < N * N; i++) {
        cout << *(arr + i) << " ";
    }

    // Операции с матрицами
    cout << "\n\nНажмите Enter для операций с матрицами...";
    cin.get();
    clearScreen();

    manipulateWithMatrix();

    // Домашнее задание (2 вариант)
    cout << "\n\nНажмите Enter для просмотра домашнего задания (2 вариант)...";
    cin.ignore();
    cin.get();
    clearScreen();

    // Создание матрицы для домашнего задания
    int** matrix3 = new int* [N];
    int maxNum = N * N;

    for (int i = 0; i < N; i++) {
        *(matrix3 + i) = new int[N];
        for (int j = 0; j < N; j++) {
            *(*(matrix3 + i) + j) = rand() % maxNum + 1;
        }
    }

    // Поиск максимального элемента
    int maxValue = *(*(matrix3 + 0) + 0);
    int maxLine = 0, maxColumn = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (*(*(matrix3 + i) + j) > maxValue) {
                maxValue = *(*(matrix3 + i) + j);
                maxLine = i;
                maxColumn = j;
            }
        }
    }

    cout << "Исходная матрица:\n";
    printMatrix(matrix3, N);
    cout << "\nМаксимальный элемент: " << maxValue;
    cout << "\nЕго положение: строка " << maxLine + 1 << ", столбец " << maxColumn + 1 << endl;

    cout << "\n\nНажмите Enter для визуализации перемещения...";
    cin.get();

    // Перемещение максимального элемента в левый верхний угол
    while (*(*(matrix3 + 0) + 0) != maxValue) {
        // Движение влево
        for (int col = maxColumn; col > 0; col--) {
            *(*(matrix3 + maxLine) + col) = *(*(matrix3 + maxLine) + col - 1);
            *(*(matrix3 + maxLine) + col - 1) = maxValue;
            maxColumn = col - 1;

            clearScreen();
            cout << "Перемещение максимального элемента:\n\n";
            printMatrixHome(matrix3, N, maxLine, maxColumn);
            delay(1000);
        }

        // Движение вверх
        for (int row = maxLine; row > 0; row--) {
            *(*(matrix3 + row) + maxColumn) = *(*(matrix3 + row - 1) + maxColumn);
            *(*(matrix3 + row - 1) + maxColumn) = maxValue;
            maxLine = row - 1;

            clearScreen();
            cout << "Перемещение максимального элемента:\n\n";
            printMatrixHome(matrix3, N, maxLine, maxColumn);
            delay(1000);
        }
    }

    cout << "\n\nНажмите Enter для просмотра итоговой матрицы...";
    cin.get();
    clearScreen();

    cout << "Итоговая матрица (максимальный элемент в левом верхнем углу):\n";
    printMatrix(matrix3, N);

    // Освобождение памяти
    delete[] arr;
    delete[] randomNum;

    for (int i = 0; i < N; i++) {
        delete[] * (matrix1 + i);
        delete[] * (matrix2 + i);
        delete[] * (matrix3 + i);
    }

    delete[] matrix1;
    delete[] matrix2;
    delete[] matrix3;

    cout << "\nПрограмма завершена. Нажмите Enter для выхода...";
    main();
}