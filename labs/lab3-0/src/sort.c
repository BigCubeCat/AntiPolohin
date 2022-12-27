#include "sort.h"

/*
 * Swap(int *array, int first, int second)
 * swap array elements
 */
void Swap(int *array, int first, int second) {
    int tmp = array[first];
    array[first] = array[second];
    array[second] = tmp;
}
/*
 * CreateHeap(int *array, int n, int i)
 * Create heap from array (swap array value)
 * @param array: array to create heap
 * @param n: size of array
 * @param i: index of curren value
 * Heap struct:
 *      i (element)
 *     /  \
 *  2i+1  2i + 2
 */
void CreateHeap(int *array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[i] < array[left]) {
        largest = left;
    }
    if (right < n && array[largest] < array[right]) {
        largest = right;
    }
    if (largest != i) {
        Swap(array, i, largest);
        CreateHeap(array, n, largest);
    }
}

/*
 * HeapSort(int *array, int n)
 * Sorts array elements by non-decreasing
 * @param array: array to sort
 * @param n: size of array
 */
void HeapSort(int *array, int n) {
    for (int i = n / 2; i >= 0; --i) {
        CreateHeap(array, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        Swap(array, i, 0);
        CreateHeap(array, i, 0);
    }
}
