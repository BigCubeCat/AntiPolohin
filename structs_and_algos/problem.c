/*
 * Условие
 * N - количество слов
 * word1, word_2, word_3, word_4, ... word_N
 * Найти пятерки символв которые есть в каждм из слов
 */

#include <stdio.h>
#include <stdlib.h>

struct THashTable {
    struct TNode {
        char key[5];
        int value;
    };
    struct TNode *Array;
    int M;
};

void Add(THashTable *table, char *word, int n) {}

int main() {
    const int M = 10000;
    int n;
    scanf("%d", &n);
    char **words;
    struct THashTable table;
    table.Array = (struct TNode *)malloc(sizeof(struct TNode) * M);
    table.M = M;

    for (int i = 0; i < M; ++i) {
        char *word = words[i];
        while (word[5] != '\0') {
            Add(&table, word, 5);
            ++word;
        }
    }
    return 0;
}
