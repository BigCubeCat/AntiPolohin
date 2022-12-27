#include <stdio.h>
#include <stdlib.h>

typedef struct THashF {
    int p;
    int a;
    int b;
} THashF;

typedef struct TBloomFilter {
    int *Array;
    THashF *Hashes;
    int k;
    int m;
} TBloomFilter;

int CalcHash(THashF func, int m, int x) {
    return ((func.a * x + func.b) % func.p) % m;
}

int Check(TBloomFilter *filter, int x) {
    for (int i = 0; i < filter->k; i++) {
        int hash = CalcHash(filter->Hashes[i], filter->m, x);
        if (filter->Array[hash] == 0) {
            return 0;
        }
    }
    return 1;
}

void Add(TBloomFilter *filter, int x) {
    for (int i = 0; i < filter->k; ++i) {
        int hash = CalcHash(filter->Hashes[i], filter->m, x);
        filter->Array[hash] = 1;
    }
}

int main() {
    TBloomFilter filter;
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    filter.Array = (int *)calloc(sizeof(int), m);
    int k = (n / m) * 0.69;
    filter.Hashes = (THashF *)malloc(k * sizeof(THashF));
    filter.k = k;
    filter.m = m;

    int p;
    for (int i = m + (m % 2 + 1);; i += 2) {
        int count = 0, sqrti = (int)sqrt(i);
        for (int j = 2; j < sqrti + 1; ++j) {
            if (sqrti % j == 0) {
                count = 1;
                break;
            }
        }
        if (count) {
            p = i;
            break;
        }
    }
    for (int i = 0; i < k; ++i) {
        filter.Hashes[i].p = p;
        filter.Hashes[i].a = (rand() + 1) % p;
        filter.Hashes[i].b = (rand()) % p;
    }
}
