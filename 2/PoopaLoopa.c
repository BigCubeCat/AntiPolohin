#include <stdio.h>


int main() {
    unsigned long long int a;
    unsigned long long int b = 0;
    scanf("%llu",&a);
    for( int i = 0; i < 64; ++i) {
        int c = (a >> i) & 1;
        b |= c;
        if (i != 63) {
            b <<= 1;
        }
    }
    printf("%llu", b);
    return 0;
}

