#include <stdio.h>
#include <stdlib.h>


int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int** data = (int**)malloc(n * sizeof(int*));
    int* len = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        data[i] = (int *) malloc(sizeof(int));
        //len[i] = 0;
    }
    getchar();
    char c;
    int index, value;
    for (int i = 0; i < m; ++i) {
        getchar();
        c = getchar();
        getchar();
        if (c == 'u') {
            getchar();
            scanf("%d%d",&index,&value);
            data[index][len[index]] = value;
            ++len[index];
            data[index] = (int*)realloc(data[index], sizeof(int) * len[index]);
        }
        else if (c == 'o') {
            scanf("%d", &index);
            --len[index];
            data[index] = (int*)realloc(data[index], len[index] * sizeof(int));
        }
        getchar();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
    return 0;
}

