#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <windows.h>
#include <map>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cstring>  
#include <cctype>
#include "kursach.h"

using namespace std;

// Глобальная переменная для текста (чтобы использовать в функциях поиска)
char* globalText = nullptr;

void clearScreen4() {
    system("cls");
}

// Функция для создания копии строки
char* copyString(const char* str) {
    if (!str) return nullptr;
    char* result = new char[strlen(str) + 1];
    strcpy_s(result, strlen(str) + 1, str);
    return result;
}

// Безопасное копирование строки с проверкой размера
void safeStrCat(char* dest, size_t destSize, const char* src) {
    size_t destLen = strlen(dest);
    size_t srcLen = strlen(src);

    if (destLen + srcLen + 1 <= destSize) {
        strcat_s(dest, destSize, src);
    }
}

// Безопасное копирование подстроки
void safeStrnCpy(char* dest, size_t destSize, const char* src, size_t count) {
    size_t copyCount = min(count, destSize - 1);
    if (copyCount > 0) {
        strncpy_s(dest, destSize, src, copyCount);
        dest[copyCount] = '\0';
    }
    else {
        dest[0] = '\0';
    }
}

// Перевод в нижний регистр
char* toLowerWin(const char* str) {
    if (!str) return nullptr;

    size_t len = strlen(str);
    char* result = new char[len + 1];
    strcpy_s(result, len + 1, str);

    for (size_t i = 0; result[i] != '\0'; i++) {
        char& c = result[i];
        // Заглавные русские буквы 
        if ((unsigned char)c >= 0xC0 && (unsigned char)c <= 0xDF && c != 0xD7) {
            c += 32;
        }
        // Буква Ё ( нижнем регистре)
        else if ((unsigned char)c == 0xC8) {
            c = (char)0xE8;
        }
        // Латинские заглавные буквы
        else if (c >= 'A' && c <= 'Z') {
            c = tolower(c);
        }
    }

    return result;
}

// Функция для извлечения слов из строки
vector<char*> extractWords(const char* text) {
    vector<char*> words;
    if (!text) return words;

    size_t length = strlen(text);
    int wordStart = -1;

    for (size_t i = 0; i <= length; i++) {
        char c = text[i];
        bool isWordChar = false;

        if (c != '\0') {
            // Для русских букв
            isWordChar = ((c >= 'a' && c <= 'z') ||
                ((unsigned char)c >= 0xE0 && (unsigned char)c <= 0xFF) || // русские строчные
                ((unsigned char)c >= 0xC0 && (unsigned char)c <= 0xDF) || // русские заглавные
                (c == (char)0xE8) || // буква ё строчная
                (c == (char)0xC8) || // буква Ё заглавная
                (c >= '0' && c <= '9') ||
                (c >= 'A' && c <= 'Z'));
        }

        if (isWordChar && wordStart == -1) {
            wordStart = (int)i;
        }
        else if ((!isWordChar || c == '\0') && wordStart != -1) {
            size_t wordLength = i - wordStart;
            char* word = new char[wordLength + 1];
            safeStrnCpy(word, wordLength + 1, text + wordStart, wordLength);
            words.push_back(word);
            wordStart = -1;
        }
    }

    return words;
}

// Функция для удаления дубликатов слов
vector<char*> removeDuplicates(const vector<char*>& words) {
    vector<char*> uniqueWords;

    for (size_t i = 0; i < words.size(); i++) {
        char* currentWord = words[i];
        bool found = false;

        for (size_t j = 0; j < uniqueWords.size(); j++) {
            char* existingWord = uniqueWords[j];
            if (strcmp(currentWord, existingWord) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            char* copy = new char[strlen(currentWord) + 1];
            strcpy_s(copy, strlen(currentWord) + 1, currentWord);
            uniqueWords.push_back(copy);
        }
    }

    return uniqueWords;
}

// Функция для вывода слов в алфавитном порядке
void printSortedWords(const vector<char*>& words) {
    if (words.empty()) {
        cout << "Слова не найдены!\n";
        return;
    }
    cout << "\nСлова в алфавитном порядке:\n";
    for (size_t i = 0; i < words.size(); ++i) {
        cout << i + 1 << ". " << words[i] << "\n";
    }
}

// Функция сравнения для сортировки
bool compareStrings(const char* a, const char* b) {
    return strcmp(a, b) < 0;
}

// Функция для чтения всего текста до конечной точки
char* readUntilFinalDot() {
    const size_t INITIAL_BUFFER_SIZE = 4096;
    size_t bufferSize = INITIAL_BUFFER_SIZE;
    char* text = new char[bufferSize];
    text[0] = '\0';

    char buffer[1024];

    cout << "Введите текст (завершите точкой):\n";

    while (true) {
        cin.getline(buffer, 1024);

        // Проверяем, поместится ли в текущий текст
        size_t currentLen = strlen(text);
        size_t bufferLen = strlen(buffer);

        if (currentLen + bufferLen + 1 >= bufferSize) {
            // Увеличиваем буфер
            size_t newSize = bufferSize * 2;
            char* newText = new char[newSize];
            strcpy_s(newText, newSize, text);
            delete[] text;
            text = newText;
            bufferSize = newSize;
        }

        safeStrCat(text, bufferSize, buffer);

        // Проверяем есть ли точка в тексте (кроме многоточий)
        char* searchPos = text;
        while (true) {
            char* dotPos = strchr(searchPos, '.');
            if (!dotPos) break;

            // Проверяем, это многоточие?
            size_t dotIndex = dotPos - text;
            size_t textLen = strlen(text);

            if (dotIndex + 2 < textLen &&
                text[dotIndex + 1] == '.' &&
                text[dotIndex + 2] == '.') {
                searchPos = dotPos + 3;
                continue;
            }
            if (dotIndex >= 2 &&
                text[dotIndex - 1] == '.' &&
                text[dotIndex - 2] == '.') {
                searchPos = dotPos + 1;
                continue;
            }
            if (dotIndex >= 1 && text[dotIndex - 1] == '.') {
                searchPos = dotPos + 1;
                continue;
            }

            // Нашли конечную точку
            size_t length = dotPos - text + 1;
            char* result = new char[length + 1];
            safeStrnCpy(result, length + 1, text, length);
            delete[] text;
            return result;
        }

        // Не нашли конечную точку
        safeStrCat(text, bufferSize, " ");
    }
}

// Функция для чтения из файла до конечной точки
char* readFileUntilFinalDot(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return nullptr;
    }

    const size_t INITIAL_BUFFER_SIZE = 8192;
    size_t bufferSize = INITIAL_BUFFER_SIZE;
    char* text = new char[bufferSize];
    text[0] = '\0';

    char buffer[1024];

    while (file.getline(buffer, 1024)) {
        // Проверяем, поместится ли в текущий текст
        size_t currentLen = strlen(text);
        size_t bufferLen = strlen(buffer);

        if (currentLen + bufferLen + 2 >= bufferSize) {
            // Увеличиваем буфер
            size_t newSize = bufferSize * 2;
            char* newText = new char[newSize];
            strcpy_s(newText, newSize, text);
            delete[] text;
            text = newText;
            bufferSize = newSize;
        }

        safeStrCat(text, bufferSize, buffer);
        safeStrCat(text, bufferSize, " ");

        // Проверяем есть ли точка в тексте (кроме многоточий)
        char* searchPos = text;
        while (true) {
            char* dotPos = strchr(searchPos, '.');
            if (!dotPos) break;

            // Проверяем, это многоточие?
            size_t dotIndex = dotPos - text;
            size_t textLen = strlen(text);

            if (dotIndex + 2 < textLen &&
                text[dotIndex + 1] == '.' &&
                text[dotIndex + 2] == '.') {
                searchPos = dotPos + 3;
                continue;
            }
            if (dotIndex >= 2 &&
                text[dotIndex - 1] == '.' &&
                text[dotIndex - 2] == '.') {
                searchPos = dotPos + 1;
                continue;
            }
            if (dotIndex >= 1 && text[dotIndex - 1] == '.') {
                searchPos = dotPos + 1;
                continue;
            }

            // Нашли конечную точку
            size_t length = dotPos - text + 1;
            char* result = new char[length + 1];
            safeStrnCpy(result, length + 1, text, length);
            delete[] text;
            file.close();
            return result;
        }
    }

    file.close();

    // Если не нашли точку, возвращаем весь текст
    char* result = new char[strlen(text) + 1];
    strcpy_s(result, strlen(text) + 1, text);
    delete[] text;
    return result;
}

// Линейный поиск
vector<int> linearSearch(const char* text, const char* pattern) {
    vector<int> positions;
    if (!text || !pattern) return positions;

    int n = (int)strlen(text);
    int m = (int)strlen(pattern);

    if (m == 0 || n == 0 || m > n) {
        return positions;
    }

    for (int i = 0; i <= n - m; i++) {
        bool found = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            positions.push_back(i);
        }
    }

    return positions;
}

// Алгоритм Кнута-Морриса-Пратта (KMP) 
vector<int> kmpSearch(const char* text, const char* pattern) {
    vector<int> positions;
    if (!text || !pattern) return positions;

    int n = (int)strlen(text);
    int m = (int)strlen(pattern);

    if (m == 0 || n == 0 || m > n) {
        return positions;
    }

    // Создаем префикс-функцию
    vector<int> prefix(m, 0);
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        prefix[i] = k;
    }

    // Поиск с использованием префикс-функции
    k = 0;
    for (int i = 0; i < n; i++) {
        while (k > 0 && pattern[k] != text[i]) {
            k = prefix[k - 1];
        }
        if (pattern[k] == text[i]) {
            k++;
        }
        if (k == m) {
            positions.push_back(i - m + 1);
            k = prefix[k - 1];
        }
    }

    return positions;
}

// Функция для вывода результатов поиска
void printSearchResults(const vector<int>& positions, const char* pattern,
    const char* algorithmName, const char* text) {
    cout << "\nРезультаты поиска (" << algorithmName << "):\n";

    if (positions.empty()) {
        cout << "Подстрока \"" << pattern << "\" не найдена.\n";
    }
    else {
        cout << "Подстрока \"" << pattern << "\" найдена " << positions.size()
            << " раз(а) на позициях: ";
        for (size_t i = 0; i < positions.size(); i++) {
            cout << positions[i];
            if (i != positions.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Освобождение памяти вектора строк
void freeStringVector(vector<char*>& vec) {
    for (char* str : vec) {
        delete[] str;
    }
    vec.clear();
}

void lab4() {
    // Для русского ввода
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char* input = nullptr;
    int choice;

    cout << "Выберите способ ввода:\n";
    cout << "1. С клавиатуры\n";
    cout << "2. Из файла\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore(1000, '\n'); // Очищаем буфер после ввода числа

    if (choice == 1) {
        input = readUntilFinalDot();

        if (!input || strlen(input) == 0) {
            cout << "Текст не содержит точку!\n";
            delete[] input;
            return;
        }
    }
    else if (choice == 2) {
        char filename[256];
        cout << "Введите имя файла: ";
        cin.getline(filename, 256);

        input = readFileUntilFinalDot(filename);
        if (!input || strlen(input) == 0) {
            cout << "Ошибка открытия файла или файл пустой!\n";
            delete[] input;
            return ;
        }
    }
    else {
        cout << "Неверный выбор!\n";
        return ;
    }

    // Сохраняем текст в глобальную переменную для задания 5
    if (globalText) delete[] globalText;
    globalText = copyString(input);

    // Преобразуем в нижний регистр для обработки текста
    char* lowerInput = toLowerWin(input);
    delete[] input;
    input = lowerInput;

    // Обработка текста (задание 1-2)
    char* textForProcessing = copyString(input);
    size_t procLen = strlen(textForProcessing);

    // Удаляем конечную точку если она есть
    if (procLen > 0 && textForProcessing[procLen - 1] == '.') {
        // Проверяем, это многоточие?
        if (procLen >= 3) {
            if (!(textForProcessing[procLen - 3] == '.' &&
                textForProcessing[procLen - 2] == '.')) {
                // Это одиночная точка 
                textForProcessing[procLen - 1] = '\0';
                procLen--;
            }
        }
        else {
            textForProcessing[procLen - 1] = '\0';
            procLen--;
        }
    }

    // Создаем результат с достаточным размером
    size_t resultSize = procLen * 2 + 100;
    char* result = new char[resultSize];
    result[0] = '\0';

    bool lastWasSpace = false;
    bool lastWasPunct = false;
    char lastPunct = '\0';

    bool inEllipsis = false;
    int ellipsisCount = 0;

    for (size_t i = 0; i < procLen; i++) {
        char c = textForProcessing[i];
        if (c == '.') {
            if (!inEllipsis) {
                inEllipsis = true;
                ellipsisCount = 1;
            }
            else {
                ellipsisCount++;
            }

            if (ellipsisCount == 3) {
                if (strlen(result) > 0 && !lastWasSpace) {
                    safeStrCat(result, resultSize, " ");
                }
                safeStrCat(result, resultSize, "...");
                lastWasSpace = false;
                lastWasPunct = true;
                lastPunct = '.';
                inEllipsis = false;
                ellipsisCount = 0;
            }
            continue;
        }
        else if (inEllipsis) {
            for (int j = 0; j < ellipsisCount; j++) {
                if (strlen(result) > 0 && !lastWasSpace) {
                    safeStrCat(result, resultSize, " ");
                }
                safeStrCat(result, resultSize, ".");
                lastWasSpace = false;
                lastWasPunct = true;
                lastPunct = '.';
            }
            inEllipsis = false;
            ellipsisCount = 0;

            // Пробелы
            if (c == ' ' || c == '\t') {
                if (!lastWasSpace && strlen(result) > 0) {
                    safeStrCat(result, resultSize, " ");
                    lastWasSpace = true;
                }
                lastWasPunct = false;
                continue;
            }
            // Знаки препинания
            if (c == ',' || c == '!' || c == '?' || c == ':' ||
                c == ';' || c == '-' || c == '(' || c == ')' ||
                c == '\"' || c == '\'') {

                if (!(lastWasPunct && c == lastPunct)) {
                    if (strlen(result) > 0 && !lastWasSpace) {
                        safeStrCat(result, resultSize, " ");
                    }
                    char temp[2] = { c, '\0' };
                    safeStrCat(result, resultSize, temp);
                    lastWasSpace = false;
                    lastWasPunct = true;
                    lastPunct = c;
                }
                continue;
            }
            // Все остальные символы
            char temp[2] = { c, '\0' };
            safeStrCat(result, resultSize, temp);
            lastWasSpace = false;
            lastWasPunct = false;
            continue;
        }
        // Пробелы и табуляции
        if (c == ' ' || c == '\t') {
            if (!lastWasSpace && strlen(result) > 0) {
                safeStrCat(result, resultSize, " ");
                lastWasSpace = true;
            }
            lastWasPunct = false;
            continue;
        }

        // Знаки препинания (кроме точки, которую обработали выше)
        if (c == ',' || c == '!' || c == '?' || c == ':' ||
            c == ';' || c == '-' || c == '(' || c == ')' ||
            c == '\"' || c == '\'') {

            // Не добавляем подряд одинаковые знаки препинания
            if (!(lastWasPunct && c == lastPunct)) {
                // Добавляем пробел перед знаком препинания, если нужно
                if (strlen(result) > 0 && !lastWasSpace) {
                    safeStrCat(result, resultSize, " ");
                }
                char temp[2] = { c, '\0' };
                safeStrCat(result, resultSize, temp);
                lastWasSpace = false;
                lastWasPunct = true;
                lastPunct = c;
            }
            continue;
        }

        // Все остальные символы (буквы, цифры)
        char temp[2] = { c, '\0' };
        safeStrCat(result, resultSize, temp);
        lastWasSpace = false;
        lastWasPunct = false;
    }

    if (inEllipsis) {
        for (int j = 0; j < ellipsisCount; j++) {
            if (strlen(result) > 0 && !lastWasSpace) {
                safeStrCat(result, resultSize, " ");
            }
            safeStrCat(result, resultSize, ".");
            lastWasSpace = false;
            lastWasPunct = true;
            lastPunct = '.';
        }
    }

    cout << "\nОбработанный текст:\n";
    cout << result << "\n";
    delete[] result;

    cout << "\n3 и 4 Задание\n";
    cout << "Вывод слов в алфавитном порядке и вертикально\n";

    // Для извлечения слов используем текст без конечной точки
    char* textForWords = copyString(textForProcessing);

    // Преобразуем весь текст в нижний регистр
    char* lowerText = toLowerWin(textForWords);

    // Извлекаем слова из текста
    vector<char*> allWords = extractWords(lowerText);

    // Удаляем дубликаты
    vector<char*> uniqueWords = removeDuplicates(allWords);

    // Сортируем слова в алфавитном порядке
    sort(uniqueWords.begin(), uniqueWords.end(), compareStrings);

    // Выводим результат
    printSortedWords(uniqueWords);

    // Освобождаем память
    freeStringVector(allWords);

    cout << "\n5 Задание: Поиск подстрок\n";

    // Запрашиваем у пользователя подстроку для поиска
    char searchPattern[256];
    cout << "\nВведите подстроку для поиска: ";
    cin.getline(searchPattern, 256);

    // Преобразуем поисковый шаблон в нижний регистр
    char* lowerSearchPattern = toLowerWin(searchPattern);

    if (strlen(lowerSearchPattern) == 0) {
        cout << "Подстрока не может быть пустой!\n";
        freeStringVector(uniqueWords);
        delete[] textForWords;
        delete[] lowerText;
        delete[] textForProcessing;
        delete[] lowerSearchPattern;
        return ;
    }

    // 1. Линейный поиск (обязательный для всех)
    cout << "\n1)Линейный поиск ";
    vector<int> linearPositions = linearSearch(lowerText, lowerSearchPattern);
    printSearchResults(linearPositions, lowerSearchPattern, "Линейный поиск", lowerText);

    // 2. Алгоритм КМП
    cout << "\n\n2)Алгоритм Кнута-Морриса-Пратта (KMP)";
    vector<int> algorithmPositions = kmpSearch(lowerText, lowerSearchPattern);
    printSearchResults(algorithmPositions, lowerSearchPattern, "Алгоритм КМП", lowerText);

    // Сравнение эффективности алгоритмов
    cout << "\nНайдено вхождений: " << linearPositions.size() << "\n";

    // Освобождаем оставшуюся память
    freeStringVector(uniqueWords);
    delete[] textForWords;
    delete[] lowerText;
    delete[] textForProcessing;
    delete[] lowerSearchPattern;

    std::cout << "\n\n\n\n\n\n===========Нажмите Enter для потрясающей концовки=================";
    std::cin.get();
    clearScreen4();
    cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tКонец! А кто смотрел - тот молодец:):):)\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    // Освобождаем глобальную память
    if (globalText) {
        delete[] globalText;
        globalText = nullptr;
    }
    main();
    return ;
}