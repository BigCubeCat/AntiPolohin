#include <stdio.h>
#include <stdlib.h>

int F(int value, int position, int seed) {
    int result = 0;
    for (size_t i = 1; i <= seed * seed; ++i) {
        result = (result + (i % 2 ? value + 1 : position + 1) * i * seed) % 10;
    }
    return result;
}

int TyanochkuHocheca(int *data, int *value, int index, int size, int seed,
                     int **d, int *count) {
    // printf("index = %d\n");
    if (*count >= 5) {
        return 0;
    }
    if (index >= size) {
        *count += 1;
        for (int i = 0; i < size; ++i) {
            printf("%d", value[i]);
        }
        printf("\n");
        return 1;
    }
    int answer = 0;
    int k = 0;
    for (int i = 9; i >= 0; --i) {
        value[index] = i;
        if (d[index][i] == data[index]) {
            k = TyanochkuHocheca(data, value, index + 1, size, seed, d, count);
            answer |= k;
        }
    }
    return answer;
}

int main() {
    int n, seed;
    char *B = (char *)malloc(sizeof(char) * n);
    scanf("%d %d", &n, &seed);
    getchar();
    int **d = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i) {
        d[i] = (int *)malloc(sizeof(int) * 10);
        for (int j = 10; j >= 0; --j) {
            d[i][j] = F(j, i, seed);
            // printf("%d ", d[i][j]);
        }
        // printf("\n");
    }
    int *data = (int *)malloc(sizeof(int) * n);
    int *value = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        data[i] = (int)((int)getchar() - (int)'0');
    }

    int count = 0;
    int index = 0;
    if (!TyanochkuHocheca(data, value, index, n, seed, d, &count)) {
        printf("No solutions\n");
    }

    free(B);
    free(data);
    free(value);
}
