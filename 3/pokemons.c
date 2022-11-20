#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int geom(int a, int b) {
    //printf("a, b, res = %d, %d, %d\n", a, b, (int)sqrt(a * b));
    return sqrt(a * b);
}

int step(int *data, int k, int size) {
    //printf("k = %d\n", k);
    for (int i = 0; i < size; i += k) {
        int nextIndex = i + (k / 2);
        if (nextIndex >= size) {
            break;
        }
        data[i] = geom(data[i], data[nextIndex]);
    }
    /*
    for (int i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    } printf("\n");
    */
    if (size / k < 1) {
        return data[0];
    }
    return step(data, k * 2, size);
}

int main() {
    int n;
    scanf("%d", &n); getchar();
    int *data = (int *) malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data[i]);
    }
    if (n % 2 == 1) {
        // Заглушка для нечетного сулчая
        data[n] = data[n - 1];
        n++;
    }
    printf("%d\n", step(data, 2, n));
}
