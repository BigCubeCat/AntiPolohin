#include <stdio.h>
#include <stdlib.h>

void Resolve(long long val) {
    if (val < 100000) {
        printf("%lld\n", val);
        return;
    }
    printf("0x%llx\n", val);
    long long *pointer = (long long*)val;
    Resolve(*pointer);
    // Место для выстраданного кода
}

int main() {
    printf("0x%X\n", 100);
    return 0;
}
