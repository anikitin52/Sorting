#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <clocale>

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
    std::cout << "2 - Эксперименты (сравнение алгоритмов на разных данных)" << std::endl;
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


