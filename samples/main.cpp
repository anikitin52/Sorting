#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <clocale>
#include <random>
#include <iomanip>

#include "experiments.cpp"

// Объявления функций из sortings.cpp
void quickSort(int a[], int i, int j);
void sortAVL(int* a, int n);

// Объявление функции экспериментов
void runExperiments();

std::vector<int> readArrayFromFile(const std::string& filename) {
    std::vector<int> array;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return array;
    }

    int number;
    while (file >> number) {
        array.push_back(number);
    }

    file.close();
    return array;
}

void writeArrayToFile(const std::vector<int>& array, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < array.size(); ++i) {
        file << array[i];
        if (i < array.size() - 1) {
            file << " ";
        }
    }

    file.close();
}

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void runInteractiveExperiment() {
    std::cout << "=== ИНТЕРАКТИВНЫЙ ЭКСПЕРИМЕНТ ===" << std::endl;

    int n, q, w, fillType;
    std::string fillTypeStr;

    // Ввод параметров
    std::cout << "Введите количество элементов (n): ";
    std::cin >> n;

    std::cout << "Введите нижнюю границу значений (q): ";
    std::cin >> q;

    std::cout << "Введите верхнюю границу значений (w): ";
    std::cin >> w;

    std::cout << "Выберите способ заполнения массива:" << std::endl;
    std::cout << "1 - Псевдослучайное" << std::endl;
    std::cout << "2 - По неубыванию (автоматическое)" << std::endl;
    std::cout << "3 - По невозрастанию (автоматическое)" << std::endl;
    std::cout << "Ваш выбор: ";
    std::cin >> fillType;

    switch (fillType) {
    case 1: fillTypeStr = "random"; break;
    case 2: fillTypeStr = "ascending"; break;
    case 3: fillTypeStr = "descending"; break;
    default:
        std::cout << "Неверный выбор. Используется псевдослучайное заполнение." << std::endl;
        fillTypeStr = "random";
    }

    // Генерация массива
    std::vector<int> array(n);

    if (fillTypeStr == "random") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(q, w);

        for (int i = 0; i < n; ++i) {
            array[i] = dist(gen);
        }
    }
    else if (fillTypeStr == "ascending") {
        if (n == 1) {
            array[0] = q;
        }
        else {
            double step = static_cast<double>(w - q) / (n - 1);
            for (int i = 0; i < n; ++i) {
                array[i] = q + static_cast<int>(i * step);
            }
        }
    }
    else if (fillTypeStr == "descending") {
        if (n == 1) {
            array[0] = w;
        }
        else {
            double step = static_cast<double>(w - q) / (n - 1);
            for (int i = 0; i < n; ++i) {
                array[i] = w - static_cast<int>(i * step);
            }
        }
    }

    // QuickSort
    std::vector<int> arrayQuick = array;
    auto startQuick = std::chrono::high_resolution_clock::now();
    quickSort(arrayQuick.data(), 0, n - 1);
    auto endQuick = std::chrono::high_resolution_clock::now();
    double timeQuick = std::chrono::duration<double>(endQuick - startQuick).count();

    // AVL сортировка
    std::vector<int> arrayAVL = array;
    auto startAVL = std::chrono::high_resolution_clock::now();
    sortAVL(arrayAVL.data(), n);
    auto endAVL = std::chrono::high_resolution_clock::now();
    double timeAVL = std::chrono::duration<double>(endAVL - startAVL).count();

    // Вывод результатов
    std::cout << "\n=== РЕЗУЛЬТАТЫ ЭКСПЕРИМЕНТА ===" << std::endl;
    std::cout << "Параметры:" << std::endl;
    std::cout << "  n = " << n << std::endl;
    std::cout << "  q = " << q << ", w = " << w << std::endl;
    std::cout << "  Заполнение: " << fillTypeStr << std::endl;
    std::cout << "\nВремя выполнения:" << std::endl;
    std::cout << "  QuickSort (TA): " << std::fixed << std::setprecision(6) << timeQuick << " секунд" << std::endl;
    std::cout << "  AVLTree (TB): " << std::fixed << std::setprecision(6) << timeAVL << " секунд" << std::endl;

    // Проверка корректности
    bool quickCorrect = isSorted(arrayQuick);
    bool avlCorrect = isSorted(arrayAVL);

    std::cout << "\nКорректность сортировки:" << std::endl;
    std::cout << "  QuickSort: " << (quickCorrect ? "ДА" : "НЕТ") << std::endl;
    std::cout << "  AVLTree: " << (avlCorrect ? "ДА" : "НЕТ") << std::endl;

    // Сравнение производительности
    if (quickCorrect && avlCorrect) {
        std::cout << "\nСравнение:" << std::endl;
        if (timeQuick < timeAVL) {
            std::cout << "QuickSort быстрее в " << timeAVL / timeQuick << " раз" << std::endl;
        }
        else {
            std::cout << "AVLTree быстрее в " << timeQuick / timeAVL << " раз" << std::endl;
        }
    }
}

void runMainProgram() {
    std::cout << "=== ЗАПУСК ОСНОВНОЙ ПРОГРАММЫ ===" << std::endl;

    // Читаем input.txt из основной папки проекта
    std::string inputPath = "../../input.txt";
    std::vector<int> inputArray = readArrayFromFile(inputPath);

    if (inputArray.empty()) {
        std::cerr << "Ошибка: файл input.txt не найден по пути " << inputPath << std::endl;
        std::cerr << "Поместите файл input.txt в основную папку проекта" << std::endl;
        return;
    }

    std::cout << "Прочитано " << inputArray.size() << " чисел" << std::endl;

    // QuickSort
    std::vector<int> arrayForQuickSort = inputArray;
    auto startQuick = std::chrono::high_resolution_clock::now();
    quickSort(arrayForQuickSort.data(), 0, static_cast<int>(arrayForQuickSort.size() - 1));
    auto endQuick = std::chrono::high_resolution_clock::now();
    auto durationQuick = std::chrono::duration_cast<std::chrono::microseconds>(endQuick - startQuick);

    // AVL сортировка
    std::vector<int> arrayForAVLSort = inputArray;
    auto startAVL = std::chrono::high_resolution_clock::now();
    sortAVL(arrayForAVLSort.data(), static_cast<int>(arrayForAVLSort.size()));
    auto endAVL = std::chrono::high_resolution_clock::now();
    auto durationAVL = std::chrono::duration_cast<std::chrono::microseconds>(endAVL - startAVL);

    // Записываем результаты в основную папку проекта
    std::string quickResultPath = "quicksort_result.txt";
    std::string avlResultPath = "avltree_result.txt";

    writeArrayToFile(arrayForQuickSort, quickResultPath);
    writeArrayToFile(arrayForAVLSort, avlResultPath);

    // Выводим информацию
    std::cout << "\n=== РЕЗУЛЬТАТЫ ===" << std::endl;
    std::cout << "QuickSort выполнена за: " << durationQuick.count() << " микросекунд" << std::endl;
    std::cout << "AVLTree сортировка выполнена за: " << durationAVL.count() << " микросекунд" << std::endl;
    std::cout << "\nРезультаты записаны в основную папку проекта:" << std::endl;
    std::cout << "  - " << quickResultPath << std::endl;
    std::cout << "  - " << avlResultPath << std::endl;

    // Проверяем корректность
    bool quickSortCorrect = isSorted(arrayForQuickSort);
    bool avlSortCorrect = isSorted(arrayForAVLSort);

    std::cout << "\nПроверка корректности:" << std::endl;
    std::cout << "  QuickSort: " << (quickSortCorrect ? " КОРРЕКТНА" : " ОШИБКА") << std::endl;
    std::cout << "  AVLTree: " << (avlSortCorrect ? " КОРРЕКТНА" : " ОШИБКА") << std::endl;

    // Сравнение производительности
    if (quickSortCorrect && avlSortCorrect) {
        std::cout << "\nСравнение производительности:" << std::endl;
        if (durationQuick < durationAVL) {
            std::cout << "QuickSort быстрее в " << static_cast<double>(durationAVL.count()) / durationQuick.count() << " раз" << std::endl;
        }
        else {
            std::cout << "AVLTree сортировка быстрее в " << static_cast<double>(durationQuick.count()) / durationAVL.count() << " раз" << std::endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ ===" << std::endl;
    std::cout << "Выберите режим работы:" << std::endl;
    std::cout << "1 - Основная программа (сортировка данных из файла)" << std::endl;
    std::cout << "2 - Предопределенные эксперименты" << std::endl;
    std::cout << "3 - Интерактивный эксперимент (с выбором параметров)" << std::endl;
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        runMainProgram();
        break;
    case 2:
        runExperiments();
        break;
    case 3:
        runInteractiveExperiment();
        break;
    default:
        std::cout << "Неверный выбор! Запускается основная программа..." << std::endl;
        runMainProgram();
        break;
    }

    std::cout << "\nПрограмма завершена. Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}



