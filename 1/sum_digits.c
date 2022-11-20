#include <stdio.h>

int CountDigits(double number) {
    long long beforeDot = (long long)(number * 10000000);
    int sum = 0;
    while (beforeDot > 0) {
        sum += beforeDot % 10;
        beforeDot /= 10;
    }
    return sum;
}

int main() {
    double number = 0;
    scanf("%lf", &number);
    printf("%d", CountDigits(number));
    return 0;
}
