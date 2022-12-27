#include <stdio.h>
#include <stdlib.h>

typedef struct THashNode {
    char *Key;
    char *Value;
    struct THashNode *Next;
} HashNode;

int main() {
    int N = 10;
    HashNode *hashTable = malloc(sizeof(HashNode) * N);
    for (int i = 0; i < N; ++i) {
        hashTable[i] = NULL;
    }

    return 0;
}
