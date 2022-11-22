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
 * Partion(int *array, int left, int right)
 * Swap array elements from left to right
 * returns border of two new partions
 */
int Partion(int *array, int left, int right) {
    int value = array[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (array[i] < value) {
            i++;
        }
        while (array[j] > value) {
            j--;
        }
        if (i >= j) {
            break;
        }
        Swap(array, i++, j--);
    }
    return j;
}

/*
 * QuickSort(int *array, int n, int left, int right)
 * Sorts array elements by non-decreasing
 * @param array: array to sort
 * @param n: size of array
 * @param left: left border of sorting part (default 0)
 * @param right: right border of sorting part (default n - 1)
 */
void QuickSort(int *array, int n, int left, int right) {
    if (left < right) {
        int q = Partion(array, left, right);
        QuickSort(array, n, left, q);
        QuickSort(array, n, q + 1, right);
    }
}
