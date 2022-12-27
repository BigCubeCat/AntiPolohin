#include <stdio.h>
#include <stdlib.h>

/*
 * SuperSort
 * void *array - array for sort
 * size_t n - size of array
 * size_t elemSize - size of array type
 * QuickSort for any-type array
 */
void SuperSort(void *array, size_t n, size_t elemSize,
               int (*cmp)(void *, void *)) {
    int pivot = rand() % n;
    int left = 0;
    int right = n - 1;
    while (left < right) {
        void *leftElement = array + elemSize * left;
        void *pivotElement = array + elemSize * pivot;
        for (; cmp(leftElement, pivotElement); leftElement += elemSize) {
        }
    }
    void *rightElement = array + elemSize * right;
    return;
}
