#include <stdio.h>

int main(){
    int n, answer;
    int p;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p);
        if (p & (1 << 2)) {
            answer = 1;
        }
        else if ((p & (1 << 4)) && (p & (1 << 3))) {
            answer = 0;
        }
        else if ((p & (1 << 7)) || (p & (1 << 6)) || (p & (1 << 5)) || (p & 1) ) {
            answer = 1;
        }
        else {
            answer = 0;
        }
        printf("%d", answer);
    }
    return 0;
}
