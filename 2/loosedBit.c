#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */

union Shit {
    float f;
    int i;
};

void Resolve(float* database, size_t n) {
    // Место для очень простого кода
    int *shit = (int *) malloc(sizeof(int) * n);
    union Shit s;
    for (int i = 0; i < n; ++i) {
        s.f = database[i];
        shit[i] = s.i;
    }
    int res = shit[0];
    for (int i = 1; i < n; ++i) {
        res |= shit[i];
    }
    for(int i = 0; i < 32; ++i) {
        int c = (res >> i) & 1;
        if (!c) {
            printf("%d ", i);
        }
    }
}

int main() {
    float database[] = {
            3.39992 ,
            -1.05518,
            2.82901 ,
            2.9844  ,
            4.11257 ,
            -3.02449,
            -1.6468 ,
            2.68031 ,
            -2.2203 ,
            0.539204,
        };
    Resolve(database, 10);
    return 0;
}
