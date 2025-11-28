#include "AVLtree.h"

void divide(int a[], int i, int j, int& i1) {
    int k = (i + j) / 2;  // Исправлено: средний элемент вместо остатка от деления
    int b = a[k];
    i1 = i;
    int j1 = j;

    do {
        while (a[j1] > b && j1 > i) j1--;
        while (a[i1] < b && i1 < j) i1++;
        if (i1 <= j1) {
            int temp = a[i1];
            a[i1] = a[j1];
            a[j1] = temp;
            i1++;
            j1--;
        }
    } while (i1 <= j1);
}

void quickSort(int a[], int i, int j) {
    // Итеративная версия быстрой сортировки для избежания переполнения стека
    int stack[1000]; // стек для хранения границ
    int top = -1;

    stack[++top] = i;
    stack[++top] = j;

    while (top >= 0) {
        j = stack[top--];
        i = stack[top--];

        if (i < j) {
            int i1;
            divide(a, i, j, i1);

            // Сначала добавляем правую часть в стек, затем левую
            // Это гарантирует, что мы обрабатываем меньшие части первыми
            if (i1 - i > j - i1) {
                // Левая часть больше - добавляем её последней
                if (i1 < j) {
                    stack[++top] = i1;
                    stack[++top] = j;
                }
                if (i < i1 - 1) {
                    stack[++top] = i;
                    stack[++top] = i1 - 1;
                }
            }
            else {
                // Правая часть больше или равна - добавляем её последней
                if (i < i1 - 1) {
                    stack[++top] = i;
                    stack[++top] = i1 - 1;
                }
                if (i1 < j) {
                    stack[++top] = i1;
                    stack[++top] = j;
                }
            }
        }
    }
}

void sortAVL(int* a, int n) {
    AVLTree<int> p(a, n);
    p.toSortedArray(a, n);
}