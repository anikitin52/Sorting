#include "AVLtree.h"

void divide(int a[], int i, int j, int& i1) {
    int k = (i + j) / 2;  // СРЕДНИЙ элемент, а не остаток от деления!
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
    if (i < j) {
        int i1;
        divide(a, i, j, i1);
        quickSort(a, i, i1 - 1);
        quickSort(a, i1, j);  
    }
}

void sortAVL(int* a, int n) {
    AVLTree<int> p(a, n);
    p.toSortedArray(a, n);
}