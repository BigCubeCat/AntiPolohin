#include <stdio.h>

int main() {
    unsigned int a; scanf("%d", &a);
    unsigned int b; scanf("%d", &b);
    unsigned int result = 0;
    char flag = 0;
    for (int i = 31; i >= 0; --i) {
        if ((b >> i) & 1) {
            if ((a >> i) & 1) {
                result |= 1 << i;
            } else {
                break;
            }
        }
    }
    printf("%d\n", result);
    return 0;
}
