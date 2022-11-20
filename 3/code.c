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
                     int *count) {
    // printf("index = %d\n", index);
    // printf("size = %d\n", size);
    if (index >= size) {
        /*
        int *answer = (int *)malloc(sizeof(int) * size);
        for (int i = 0; i < size; ++i) {
            answer[i] = F(value[i], i, seed);
        }
        for (int i = 0; i < size; ++i) {
            if (answer[i] != data[i]) {
                free(answer);
                return 0;
            }
        }
        */
        // Cool, we find this!
        *count += 1;
        for (int i = 0; i < size; ++i) {
            printf("%d", value[i]);
        }
        printf("\n");
        return 1;
    }
    int answer = 0;
    for (int i = 9; i >= 0; --i) {
        value[index] = i;
        if (F(value[index], index, seed) == data[index] && *count < 5) {
            //      printf("F -> %d\n", i);
            //    printf("data[index] -> %d\n", data[index]);
            answer |=
                TyanochkuHocheca(data, value, index + 1, size, seed, count);
        }
    }
    return answer;
}

int main() {
    int n, seed;
    char *B = (char *)malloc(sizeof(char) * n);
    scanf("%d %d", &n, &seed);
    getchar();
    int *data = (int *)malloc(sizeof(int) * n);
    int *value = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        data[i] = (int)((int)getchar() - (int)'0');
    }

    int count = 0;
    if (!TyanochkuHocheca(data, value, 0, n, seed, &count)) {
        printf("No solutions\n");
    }

    free(B);
    free(data);
    free(value);
}
