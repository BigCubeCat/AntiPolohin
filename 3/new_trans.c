#include <stdio.h>
#include <stdlib.h>

const int maximum = 1000000;
int main() {
    int n;
    scanf("%d", &n);
    int **data = (int **)malloc(sizeof(int *) * n);
    int totalSize = 0;
    for (int t = 0; t < n; ++t) {
        int size;
        scanf("%d", &size);
        getchar();
        totalSize += size;
        data[t] = (int *)malloc(sizeof(int) * (size + 1));
        data[t][size] = maximum;
        for (int i = 0; i < size; ++i) {
            scanf("%d", &data[t][i]);
        }
        getchar();
    }
    int *ptrs = (int *)calloc(totalSize, sizeof(int));
    int *result = (int *)malloc(sizeof(int) * totalSize);

    for (int k = 0; k < totalSize; ++k) {
        int minimum = maximum;
        int index = -1;
        for (int i = 0; i < n; ++i) {
            if (minimum > data[i][ptrs[i]]) {
                minimum = data[i][ptrs[i]];
                index = i;
            }
        }
        ptrs[index]++;
        result[k] = minimum;
    }
    for (int i = 0; i < totalSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
