#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

int main(void) {
    int size;
    if (scanf("%d\n", &size) != 1) {
        printf("Error\n");
        return EXIT_FAILURE;
    }
    int *data = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", &data[i]) != 1) {
            printf("Error\n");
            return EXIT_FAILURE;
        }
    }
    QuickSort(data, size, 0, size - 1);
    for (int i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    free(data);
    return EXIT_SUCCESS;
}
