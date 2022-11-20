#include <stdio.h>

int main() {
    int n; scanf("%d", &n);
    int v;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v);
        if (v & 4) {// c++ chad
            printf("1");
            continue;
        }
        if (v & 225) { // has green
            if ((v & 24) == 24) {
                // 2 red
                printf("0");
            }
            else {
                printf("1");
            }
            continue;
        }
        printf("0");
    }
    return 0;
}
