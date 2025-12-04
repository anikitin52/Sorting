#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

// Объявления функций сортировки
void quickSort(int a[], int i, int j);
void sortAVL(int* a, int n);


// Вспомогательные функции
void generateRandomArray(int a[], int n, int min_val, int max_val, unsigned seed = 42) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min_val, max_val);

    for (int i = 0; i < n; i++) {
        a[i] = dist(rng);
    }
}

void generateSortedArray(int a[], int n, int min_val, int max_val, bool ascending = true) {
    if (n == 1) {
        a[0] = min_val;
        return;
    }

    double step = static_cast<double>(max_val - min_val) / (n - 1);

    if (ascending) {
        for (int i = 0; i < n; i++) {
            a[i] = min_val + static_cast<int>(i * step);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            a[i] = max_val - static_cast<int>(i * step);
        }
    }
}

bool isSorted(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            return false;
        }
    }
    return true;
}

// Функция для проведения одного эксперимента
void runExperiment(int n, int q, int w, const std::string& array_type,
    double& time_quick, double& time_avl) {
    std::vector<int> array(n);
    std::vector<int> array_copy(n);

    // Генерируем массив согласно типу
    if (array_type == "random") {
        generateRandomArray(array.data(), n, q, w, n + q + w);
    }
    else if (array_type == "ascending") {
        generateSortedArray(array.data(), n, q, w, true);
    }
    else if (array_type == "descending") {
        generateSortedArray(array.data(), n, q, w, false);
    }

    // Тестируем QuickSort
    array_copy = array;
    auto start_quick = std::chrono::high_resolution_clock::now();
    quickSort(array_copy.data(), 0, n - 1);
    auto end_quick = std::chrono::high_resolution_clock::now();
    time_quick = std::chrono::duration<double>(end_quick - start_quick).count();

    // Проверяем корректность сортировки
    if (!isSorted(array_copy.data(), n)) {
        std::cerr << "Ошибка: QuickSort отсортировал неправильно!" << std::endl;
    }

    // Тестируем AVL сортировку
    array_copy = array;
    auto start_avl = std::chrono::high_resolution_clock::now();
    sortAVL(array_copy.data(), n);
    auto end_avl = std::chrono::high_resolution_clock::now();
    time_avl = std::chrono::duration<double>(end_avl - start_avl).count();

    // Проверяем корректность сортировки
    if (!isSorted(array_copy.data(), n)) {
        std::cerr << "Ошибка: AVLSort отсортировал неправильно!" << std::endl;
    }
}

// Эксперимент 3.1: Зависимость времени от n
void experiment3_1() {
    std::cout << "=== ЭКСПЕРИМЕНТ 3.1: Зависимость времени от n ===" << std::endl;
    std::cout << "Параметры: q = 1, w = 1000000000" << std::endl;
    std::cout << std::endl;

    const int q = 1;
    const int w = 1000000000; // 10^9
    const int step = 10000;
    const int max_n = 1000001; // 10^6 + 1

    std::vector<std::string> array_types = { "random", "ascending", "descending" };

    for (const auto& array_type : array_types) {
        std::cout << "Тип массива: " << array_type << std::endl;
        std::cout << std::setw(8) << "n"
            << std::setw(12) << "QuickSort"
            << std::setw(12) << "AVLSort"
            << std::setw(15) << "Отношение" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (int n = 1; n <= max_n; n += step) {
            double time_quick, time_avl;
            runExperiment(n, q, w, array_type, time_quick, time_avl);

            double ratio = (time_quick > 0) ? time_avl / time_quick : 0;

            std::cout << std::setw(8) << n
                << std::setw(12) << std::fixed << std::setprecision(6) << time_quick
                << std::setw(12) << std::fixed << std::setprecision(6) << time_avl
                << std::setw(15) << std::fixed << std::setprecision(2) << ratio << std::endl;
        }
        std::cout << std::endl;
    }
}

// Эксперимент 3.2: Зависимость времени от w
void experiment3_2() {
    std::cout << "=== ЭКСПЕРИМЕНТ 3.2: Зависимость времени от w ===" << std::endl;
    std::cout << "Параметры: n = 1000000, q = 1" << std::endl;
    std::cout << std::endl;

    const int n = 1000000;
    const int q = 1;
    const int max_w = 100;

    std::vector<std::string> array_types = { "random", "ascending", "descending" };

    for (const auto& array_type : array_types) {
        std::cout << "Тип массива: " << array_type << std::endl;
        std::cout << std::setw(8) << "w"
            << std::setw(12) << "QuickSort"
            << std::setw(12) << "AVLSort"
            << std::setw(15) << "Отношение" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (int w = 1; w <= max_w; w++) {
            double time_quick, time_avl;
            runExperiment(n, q, w, array_type, time_quick, time_avl);

            double ratio = (time_quick > 0) ? time_avl / time_quick : 0;

            std::cout << std::setw(8) << w
                << std::setw(12) << std::fixed << std::setprecision(6) << time_quick
                << std::setw(12) << std::fixed << std::setprecision(6) << time_avl
                << std::setw(15) << std::fixed << std::setprecision(2) << ratio << std::endl;
        }
        std::cout << std::endl;
    }
}


void runExperiments() {
    std::cout << "ЭКСПЕРИМЕНТАЛЬНОЕ СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ" << std::endl;
    std::cout << "Алгоритм A: QuickSort" << std::endl;
    std::cout << "Алгоритм B: AVL-дерево" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << std::endl;

    // Запускаем эксперименты
    experiment3_1();
    experiment3_2();

    

}