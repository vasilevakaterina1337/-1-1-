#include <iostream>
#include <cstdlib>
#include <chrono>
#include "kursach.h"

const int N = 100;

int menu() {
    int typeOfSort;
    std::cout
        << "Выберите тип сортировки, который хотите использовать: " << std::endl
        << "1) Bubble Sort (Пузырьковая сортировка)" << std::endl
        << "2) Shaker Sort (Шейкерная сортировка)" << std::endl
        << "3) Selection Sort (Сортировка выбором)" << std::endl
        << "4) Insertion Sort (Сортировка вставками)" << std::endl
        << "5) Quick Sort (Быстрая сортировка)" << std::endl;
    std::cin >> typeOfSort;
    return typeOfSort;
}



void bubbleSort(int* arrBubble, int N) {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
            if (arrBubble[j] > arrBubble[j + 1]) {
                std::swap(arrBubble[j], arrBubble[j + 1]);
            }
        }
    }
}
void shakerSort(int* arrShaker, int N) {
    int left = 0, right = N - 1;
    while (left <= right) {
        // Проход слева направо
        for (int i = left; i < right; ++i) {
            if (arrShaker[i] > arrShaker[i + 1]) std::swap(arrShaker[i], arrShaker[i + 1]);
        }
        --right;

        // Проход справа налево
        for (int i = right; i > left; --i) {
            if (arrShaker[i] < arrShaker[i - 1]) std::swap(arrShaker[i], arrShaker[i - 1]);
        }
        ++left;
    }
}
void insertionSort(int* arrInsertion, int N) {
    for (int i = 1; i < N; ++i) {
        int key = arrInsertion[i];
        int j = i - 1;
        // Сдвигаем элементы, пока не найдем позицию для key
        while (j >= 0 && arrInsertion[j] > key) {
            arrInsertion[j + 1] = arrInsertion[j];
            --j;
        }
        arrInsertion[j + 1] = key;
    }
}
void selectionSort(int* arrSelection, int N) {
    for (int i = 0; i < N - 1; ++i) {
        int minIdx = i;
        // Поиск минимального элемента
        for (int j = i + 1; j < N; ++j) {
            if (arrSelection[j] < arrSelection[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arrSelection[i], arrSelection[minIdx]);
    }
}
void quicksort(int* arrQuick, int beginQuick, int endQuick) {
    if (beginQuick >= endQuick) return;

    int leftQuick = beginQuick;
    int rightQuick = endQuick;
    int midQuick = arrQuick[(leftQuick + rightQuick) / 2];

    while (leftQuick <= rightQuick) {
        while (arrQuick[leftQuick] < midQuick) leftQuick++;
        while (arrQuick[rightQuick] > midQuick) rightQuick--;

        if (leftQuick <= rightQuick) {
            std::swap(arrQuick[leftQuick], arrQuick[rightQuick]);
            leftQuick++;
            rightQuick--;
        }
    }

    if (beginQuick < rightQuick) quicksort(arrQuick, beginQuick, rightQuick);
    if (leftQuick < endQuick) quicksort(arrQuick, leftQuick, endQuick);
}
int binarySearch(int arrBubble[], int vvod, int start, int end) {
    if (end >= start) {
        int mid = start + (end - start) / 2;

        if (arrBubble[mid] == vvod) {
            return mid;
        }

        if (arrBubble[mid] > vvod) {
            return binarySearch(arrBubble, vvod, start, mid - 1);
        }

        return binarySearch(arrBubble, vvod, mid + 1, end);
    }

    return -1;
}
void mainMenu() {
    int arrBubble[N];
    int arrShaker[N];
    int arrInsertion[N];
    int arrSelection[N];
    int arrQuick[N];
    int maxBubbleNeots = 0;
    int minBubbleNeots = 0;
    int maxBubbleOts = 0;
    int minBubbleOts = 0;
    srand(time(nullptr));
    for (int i = 0; i < N; i++) {
        arrBubble[i] = rand() % 199 - 99;
    }
    for (int i = 0; i < N; i++) {
        arrShaker[i] = arrBubble[i];
        arrInsertion[i] = arrBubble[i];
        arrSelection[i] = arrBubble[i];
        arrQuick[i] = arrBubble[i];
    }
    int min, max;
    int choice;
    std::cout << "Введите номер задания (от 0 до 8) или 9 для выхода" << std::endl;
    std::cin >> choice;
    if (choice == 0) {
        shakerSort(arrShaker, N);
        std::cout << "\n\nDZ\n";
        int half = N / 2;
        int kolpol = 0;
        int kolotr = 0;
        for (int i = 0; i < half; i++) {
            std::swap(arrShaker[i], arrShaker[i + half]);
        }
        for (int i = 0; i < half; i++) {
            if (arrShaker[i] >= 0) {
                kolpol += 1;
            }
        }
        for (int i = half; i < N; i++) {
            if (arrShaker[i] < 0) {
                kolotr += 1;
            }
        }
        for (int i = 0; i < N; i++) {
            if (i == 0) {
                std::cout << "1 половина: ";
            }
            if (i == half) {
                std::cout << "\n2 половина: ";
            }
            std::cout << arrShaker[i] << " ";
        }
        std::cout << "\n\nКоличество положительных чисел в первой части: " << kolpol;
        std::cout << "\nКоличество отрицательных чисел во второй части: " << kolotr;
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 1) {
        std::cout << "Задание 1" << std::endl;
        srand(time(nullptr));
        for (int i = 0; i < N; i++) {
            arrBubble[i] = rand() % 199 - 99;
        }
        for (int i = 0; i < N; i++) {
            arrShaker[i] = arrBubble[i];
            arrInsertion[i] = arrBubble[i];
            arrSelection[i] = arrBubble[i];
            arrQuick[i] = arrBubble[i];
        }
        for (int i = 0; i < N - 1; ++i) {
            std::cout << arrBubble[i] << " ";
        }
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 2) {
        std::cout << "Задание 2" << std::endl;
        int typeOfSort = menu();
        if (typeOfSort == 1) {
            std::cout << "сортировка bubble sort:\n";
            auto startBubble = std::chrono::high_resolution_clock::now();
            //сама сортировка
            bubbleSort(arrBubble, N);
            auto stopBubble = std::chrono::high_resolution_clock::now();

            // Вычисляем длительность
            auto durationBubble = std::chrono::duration_cast<std::chrono::microseconds>(stopBubble - startBubble);
            for (int i = 0; i < N; i++) {
                std::cout << arrBubble[i] << " ";
            }
            std::cout << "\nВремя сортировки: " << durationBubble.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 2) {
            std::cout << "сортировка Shaker Sort\n";
            auto startShaker = std::chrono::high_resolution_clock::now();
            //сама сортировка
            shakerSort(arrShaker, N);
            auto stopShaker = std::chrono::high_resolution_clock::now();
            // Вычисляем длительность
            auto durationShaker = std::chrono::duration_cast<std::chrono::microseconds>(stopShaker - startShaker);
            for (int i = 0; i < N; i++) {
                std::cout << arrShaker[i] << " ";
            }
            std::cout << "\nВремя сортировки: " << durationShaker.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 3) {
            std::cout << "сортировка Selection Sort\n";
            auto startSelection = std::chrono::high_resolution_clock::now();
            //сама сортировка
            selectionSort(arrSelection, N);
            auto stopSelection = std::chrono::high_resolution_clock::now();
            // Вычисляем длительность
            auto durationSelection = std::chrono::duration_cast<std::chrono::microseconds>(stopSelection - startSelection);
            for (int i = 0; i < N; i++) {
                std::cout << arrSelection[i] << " ";
            }
            std::cout << "\nВремя сортировки: " << durationSelection.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 4) {
            std::cout << "сортировка Insertion Sort\n";
            auto startInsertion = std::chrono::high_resolution_clock::now();
            //сама сортировка

            insertionSort(arrInsertion, N);
            auto stopInsertion = std::chrono::high_resolution_clock::now();

            // Вычисляем длительность
            auto durationInsertion = std::chrono::duration_cast<std::chrono::microseconds>(stopInsertion - startInsertion);
            for (int i = 0; i < N; i++) {
                std::cout << arrInsertion[i] << " ";
            }
            std::cout << "\nВремя сортировки: " << durationInsertion.count() << " микросекунд\n\n";
        }
        else if (typeOfSort == 5) {
            std::cout << "сортировка quick Sort\n";
            auto startQuick = std::chrono::high_resolution_clock::now();
            //сама сортировка
            quicksort(arrQuick, 0, N - 1);
            auto stopQuick = std::chrono::high_resolution_clock::now();

            // Вычисляем длительность
            auto durationQuick = std::chrono::duration_cast<std::chrono::microseconds>(stopQuick - startQuick);
            for (int i = 0; i < N; i++) {
                std::cout << arrQuick[i] << " ";
            }
            std::cout << "\nВремя сортировки: " << durationQuick.count() << " микросекунд\n\n";
        }
        else menu();
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 3) {
        std::cout << "Задание 3" << std::endl;
        int maxBubbleNeots = arrBubble[0];
        int minBubbleNeots = arrBubble[0];
        auto startBubbleMaxNeots = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < N; i++) {
            if (arrBubble[i] < minBubbleNeots) {
                minBubbleNeots = arrBubble[i];
            }
            if (arrBubble[i] > maxBubbleNeots) {
                maxBubbleNeots = arrBubble[i];
            }
        }
        auto stopBubbleMaxNeots = std::chrono::high_resolution_clock::now();
        auto durationBubbleMaxNeots = std::chrono::duration_cast<std::chrono::nanoseconds>(stopBubbleMaxNeots - startBubbleMaxNeots);
        //Измеряем время max min ots
        bubbleSort(arrBubble, N);
        int maxBubbleOts = arrBubble[0];
        int minBubbleOts = arrBubble[0];
        auto startBubbleMaxOts = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < N; i++) {
            if (arrBubble[i] < minBubbleOts) {
                minBubbleOts = arrBubble[i];
            }
            if (arrBubble[i] > maxBubbleOts) {
                maxBubbleOts = arrBubble[i];
            }
        }
        auto stopBubbleMaxOts = std::chrono::high_resolution_clock::now();
        auto durationBubbleMaxOts = std::chrono::duration_cast<std::chrono::nanoseconds>(stopBubbleMaxOts - startBubbleMaxOts);
        std::cout << "max: " << maxBubbleOts;
        std::cout << "\nmin: " << minBubbleOts;
        std::cout << "\nВремя поиска макс и мин элементов в неотсортированном массиве:" << durationBubbleMaxNeots.count() << " наносекунд";
        std::cout << "\nВремя поиска макс и мин элементов в отсортированном массиве:" << durationBubbleMaxOts.count() << " наносекунд";
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 4) {
        std::cout << "Задание 4" << std::endl;
        int kolSrBubbleNeots = 0;
        auto startBubbleSrNeots = std::chrono::high_resolution_clock::now();
        int srBubbleNeots = round((maxBubbleNeots + minBubbleNeots) / 2);
        std::cout << "Среднее значение: " << srBubbleNeots;
        std::cout << "\nИндексы элеменов, равных ср значению ";
        for (int i = 0; i < N && arrBubble[i] == srBubbleNeots; i++) {
            kolSrBubbleNeots += 1;
            std::cout << i << ' ';

        }
        auto stopBubbleSrNeots = std::chrono::high_resolution_clock::now();
        auto durationBubbleSrNeots = std::chrono::duration_cast<std::chrono::nanoseconds>(stopBubbleSrNeots - startBubbleSrNeots);
        std::cout << "\nКоличество элеменов равных среднему макисмального и минимального: " << kolSrBubbleNeots;
        std::cout << "\nВремя поиска среднего значения в неотсортированном массиве: " << durationBubbleSrNeots.count();
        //среднее значение макс и мин ots
        bubbleSort(arrBubble, N);
        std::cout << "\n";
        int kolSrBubbleOts = 0;
        auto startBubbleSrOts = std::chrono::high_resolution_clock::now();
        int srBubbleOts = round((maxBubbleOts + minBubbleOts) / 2);
        for (int i = 0; i < N && arrBubble[i] == srBubbleOts; i++) {
            kolSrBubbleOts += 1;
            std::cout << i << ' ';
        }
        auto stopBubbleSrOts = std::chrono::high_resolution_clock::now();
        auto durationBubbleSrOts = std::chrono::duration_cast<std::chrono::nanoseconds>(stopBubbleSrOts - startBubbleSrOts);
        std::cout << "\nВремя поиска среднего значения в отсортированном массиве: " << durationBubbleSrOts.count();
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 5) {
        std::cout << "Задание 5" << std::endl;
        bubbleSort(arrBubble, N);
        int a;
        std::cout << "\nВведите число а: ";
        std::cin >> a;
        int kolBubbleA = 0;
        for (int i = 0; i < a; i++) {
            kolBubbleA += 1;
        }
        std::cout << "Kоличество элементов в отсортированном массиве, которые меньше числа a: " << kolBubbleA;
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 6) {
        std::cout << "Задание 6" << std::endl;
        bubbleSort(arrBubble, N);
        int b;
        std::cout << "\nВведите число b: ";
        std::cin >> b;
        int kolBubbleB = 0;
        for (int i = 0; i < N && i>b; i++) {
            kolBubbleB += 1;

        }
        std::cout << "Kоличество элементов в отсортированном массиве, которые больше числа b: " << kolBubbleB;
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 7) {
        std::cout << "Задание 7" << std::endl;
        bubbleSort(arrBubble, N);
        int vvod;
        std::cout << "\nВведите число: ";
        std::cin >> vvod;
        int kolVvodOb = 0;
        auto startObPoisk = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            if (arrBubble[i] == vvod) {
                kolVvodOb += 1;
            }
        }
        if (kolVvodOb > 0) {
            std::cout << "Введенных чисел " << kolVvodOb;
        }
        else {
            std::cout << "Введенных чисел нет ";
        }
        auto stopObPoisk = std::chrono::high_resolution_clock::now();
        auto durationObPoisk = std::chrono::duration_cast<std::chrono::nanoseconds>(stopObPoisk - startObPoisk);
        std::cout << "\nВремя обычным перебором: " << durationObPoisk.count() << " наносекунд";
        //есть ли введенное пользователем число в отсортированном массиве алгоритм бинарного поиска
        bubbleSort(arrBubble, N);
        auto startBin = std::chrono::high_resolution_clock::now();
        int start = 0;
        int end = 100;
        int nal = 0;
        int mid = 50;
        int size = sizeof(arrBubble) / sizeof(arrBubble[0]);

        int result = binarySearch(arrBubble, vvod, 0, size - 1);
        if (result == -1) {
            std::cout << "\nЭлемент не найден" << "\n";
        }
        else {
            std::cout << "\nЭлемент находится в позиции " << result << "\n";
        }

        auto stopBin = std::chrono::high_resolution_clock::now();
        auto durationBin = std::chrono::duration_cast<std::chrono::nanoseconds>(stopBin - startBin);
        std::cout << "Время бинарного поиска: " << durationBin.count() << " наносекунд";
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 8) {
        std::cout << "Задание 8" << std::endl;
        bubbleSort(arrBubble, N);
        int index1;
        int index2;
        std::cout << "Введите 1 индекс который хотите поменять ";
        std::cin >> index1;
        std::cout << "Введите 2 индекс который хотите поменять ";
        std::cin >> index2;
        auto startSwap = std::chrono::high_resolution_clock::now();
        std::swap(arrBubble[index1], arrBubble[index2]);
        auto stopSwap = std::chrono::high_resolution_clock::now();
        auto durationSwap = std::chrono::duration_cast<std::chrono::nanoseconds>(stopSwap - startSwap);
        std::cout << "Время swapa: " << durationSwap.count() << " наносекунд\n\n";
        for (int i = 0; i < N; i++) {
            std::cout << arrBubble[i] << " ";
        }
        std::cout << std::endl;
        mainMenu();
    }
    else if (choice == 9) {
        main();
    }
    else mainMenu();
}

void lab2() {
    setlocale(0, "RU");
    mainMenu();
}