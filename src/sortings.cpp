#include "AVLtree.h"

void divide(int a[], int i, int j, int& i1) {
    int k = (i + j) / 2;
    int b = a[k];
    i1 = i;
    int j1 = j;

    // Переносим опорный элемент в начало
    int temp = a[k];
    a[k] = a[i];
    a[i] = temp;

    int pivot = a[i]; // опорный элемент теперь в позиции i
    i1 = i;
    j1 = j;

    while (i1 <= j1) {
        while (i1 <= j1 && a[i1] <= pivot) i1++;
        while (i1 <= j1 && a[j1] >= pivot) j1--;
        if (i1 < j1) {
            temp = a[i1];
            a[i1] = a[j1];
            a[j1] = temp;
        }
    }

    // Возвращаем опорный элемент на правильную позицию
    temp = a[i];
    a[i] = a[j1];
    a[j1] = temp;

    i1 = j1; // i1 теперь указывает на позицию опорного элемента
}

void quickSort(int a[], int i, int j) {
    // Итеративная версия с явным стеком
    const int MAX_STACK_SIZE = 1000;
    int stack[MAX_STACK_SIZE];
    int top = -1;

    stack[++top] = i;
    stack[++top] = j;

    while (top >= 0) {
        j = stack[top--];
        i = stack[top--];

        if (i < j) {
            int i1;
            divide(a, i, j, i1);

            // Добавляем в стек правую часть
            if (i1 + 1 < j) {
                stack[++top] = i1 + 1;
                stack[++top] = j;
            }

            // Добавляем в стек левую часть  
            if (i < i1 - 1) {
                stack[++top] = i;
                stack[++top] = i1 - 1;
            }
        }
    }
}

void sortAVL(int* a, int n) {
    AVLTree<int> p(a, n);
    p.toSortedArray(a, n);
}