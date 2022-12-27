#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char **cache;

int F(int value, int position, int seed) {
    int result = 0;
    for (size_t i = 1; i <= seed * seed; ++i) {
        result = (result + (i % 2 ? value + 1 : position + 1) * i * seed) % 10;
    }
    return result;
}
static int count = 0;

int Find(char *str, int seed, int len, int position, char *result) {
    if (position == len) {
        result[position] = '\0';
        printf("%s\n", result);
        count++;
        return count;
    }
    int t = 0;
    if (cache[position] == NULL) {
        cache[position] = (char *)malloc(sizeof(char) * 11);
        int ok = 0;
        for (int i = '9'; i >= '0'; --i) {
            if (F(i - '0', position, seed) == str[position] - '0') {
                result[position] = i;
                Find(str, seed, len, position + 1, result);
                cache[position][t++] = i;
                if (count == 5 || count == -1) {
                    return count;
                }
                ok = 1;
            }
        }
        if (!ok) {
            count = -1;
            return count;
        }
        cache[position][t] = -1;
    } else {
        t = 0;
        while (cache[position][t] != -1) {
            result[position] = cache[position][t];
            Find(str, seed, len, position + 1, result);
            if (count == 5) {
                return count;
            }
            ++t;
        }
    }
    return count;
}

int main() {
    int n, seed;
    scanf("%d %d", &n, &seed);
    getchar();
    cache = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; ++i) {
        cache[i] = NULL;
    }
    char *data = (char *)malloc(sizeof(char) * n);
    char *value = (char *)malloc(sizeof(char) * n);
    for (int i = 0; i < n; ++i) {
        data[i] = getchar();
    }

    Find(data, seed, n, 0, value);
    if (count == 0) {
        printf("No solutions\n");
    }

    free(data);
    free(value);
}
