#include "next_permutation.h"
#include <stdio.h>

void SwapByIndex(char *array, int first, int second) {
    char tmp = array[first];
    array[first] = array[second];
    array[second] = tmp;
}

/*
 * NextPermutation(char *string, int length)
 * string: string for change
 * length: string length
 * print next Dejkstra permutation
 */
void NextPermutation(char *string, int length) {
    for (int i = length - 1; i > 0; --i) {
        if ((int)string[i - 1] < (int)string[i]) {
            int pivot = i;
            for (int j = pivot; j < length; ++j) {
                if (string[j] <= string[pivot] && string[i - 1] < string[j]) {
                    pivot = j;
                }
            }
            SwapByIndex(string, i - 1, pivot);

            for (int j = length - 1; i < j; ++i, --j) {
                SwapByIndex(string, i, j);
            }
            printf("%s\n", string);
            return;
        }
    }
}

