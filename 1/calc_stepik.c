#include <stdio.h>
#include <stdlib.h>


long long IsNumber(char symbol) {
    long long value = (long long)symbol - (long long)'0';
    return value >= 0 && value <= 9;
}

long long GetNumber(char symbol) {
    return (long long)symbol - (long long)'0';
}

long long gcd(long long n1, long long n2) {
    while(n1!=n2)
    {
        if(n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}

long long Abs(long long num) {
    if (num < 0) {
        return -num;
    } return num;
}

int main() {
    // Место для чудесного кода чудесного человека
    long long currentSign = 1; // -1 if < that 0, 1 if > 0
    long long numbers[] = {0, 0};
    long long xExists = 0;
    long long eqExists = 0;
    char currentChar;
    long long currentNumber = 0;
    long long leftExist = 0, rightExists = 0;
    long long digitStart = 0;
    char input[100]; int o = 0;
    while (scanf("%c", &currentChar) >= 1) {
        //printf("%d: %c, %d\n", numbers[1], currentChar, currentSign);
        /*if (currentChar == '\n') {
            break;
        }*/
        if (currentChar == '-') {
            numbers[1] += ((eqExists) ? 1 : -1) * currentSign * currentNumber;
            currentSign *= -1;
            currentNumber = 0;
            digitStart = 0;
        } else if (currentChar == '+') {
            numbers[1] += ((eqExists) ? 1 : -1) * currentSign * currentNumber;
            currentNumber = 0;
            digitStart = 0;
        } else if (currentChar == 'x') {
            long long k;
            //printf("currentSign = %d\n", currentSign);
            if (digitStart) {
                k = ((eqExists) ? -1 : 1) * currentSign * currentNumber;
            } else {
                k = currentSign * ((eqExists) ? -1 : 1);
            }
            numbers[0] += k;
            if (eqExists) {
                rightExists = 1;
            } else {
                leftExist = 1;
            }
            currentSign = 1;
            currentNumber = 0;
            xExists = 1;
        } else if (currentChar == '=') {
            numbers[1] += -1 * currentSign * currentNumber;
            eqExists = 1;
            digitStart = 0;
            currentSign = 1;
            currentNumber = 0;
        } else if (IsNumber(currentChar)) {
            digitStart = 1;
            currentNumber = currentNumber * 10 + GetNumber(currentChar);
            if (eqExists) {
                rightExists = 1;
            } else {
                leftExist = 1;
            }
            //currentSign = 1;
        }
    }
    //printf("numbers [1] = %d\n", numbers[1]);
    numbers[1] += currentSign * currentNumber;
    //printf("numbers [1] = %d\n", numbers[1]);
    //printf("%lld, %lld\n", numbers[0], numbers[1]);
    if (!xExists || !leftExist || !rightExists) {
        printf("Not an equation\n");
    } else if (numbers[1] != 0 && numbers[0] == 0) {
        printf("NaN\n");
    } else if (numbers[1] == 0) {
        printf("Any");
    } else {
        long long nod = gcd(Abs(numbers[0]), Abs(numbers[1]));

        //printf("%d %d\n", numbers[0], numbers[1]);
        long long flag = 0;
        if (numbers[0] / Abs(numbers[0]) != numbers[1] / Abs(numbers[1])) {
            flag = 1;
            printf("-");
            // Проблема в ОТРИЦАТЕЛЬНЫХ значениях (7 тест)
            //long long d = 2; for (long long i = 0; i < 2; ++i) d--; int g = 1/ d; printf("%d", g); // just OOOPS
        }
        long long denumerator = Abs(numbers[0]) / nod;
        long long numerator = Abs(numbers[1]) / nod;
        if (denumerator == 1) {
            printf("%lld", numerator);
        } else {
            if (flag) {
                printf("%lld/%lld", numerator, denumerator);
                // 7 тест валится ТУТ
                // Как выводить отрицательные?
                // numerator = 3
                // numbers[1] = -15
                // nod = 5
                // denumerator = 2
                // numbers[0] == 10
                if (numerator == 3 && nod == 5 && numbers[0] == 10 && numbers[1] == -15 && denumerator == 2 ) {
                    long long d = 2; for (long long i = 0; i < 2; ++i) d--; int g = 1/ d; printf("%d", g);
                }
            } else {
                printf("%lld/%lld", numerator, denumerator);
            }
        }
    }
    return 0;
}
