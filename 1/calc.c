#include <stdio.h>
#include <stdlib.h>

int isNumber(char c) {
    int a = (int)c - (int)'0';
    return (a >= 0 && a < 10);
}

int GCD(int a, int b) {
     return (b!=0) ? GCD(b, a%b) : a;
}

int IsGoodChar(char c) {
    return (c =='-' || c=='+' || c=='=' || c=='x' || isNumber(c));
}

int main() {
    // Место для чудесного кода чудесного человека
    char currentChar;
    int totalX = 0;
    int totalDigits = 0;
    int currentDigits = 0;

    int leftExists = 0;
    int rightExists = 0;
    int xExists = 0;

    int k;
    int isEq = 0;
    int sign = 1;
    int digitExist = 0; // Введено ли число перед x

    char prev;
    int zeroSign = 0;
    while ((currentChar = getc(stdin)) != EOF) {
        if (currentChar == '\n') {
            break;
        }
        if (!IsGoodChar(currentChar)) {
            continue;
        }
        if (isNumber(prev) && !isNumber(currentChar)) {
            zeroSign = 1;
        }
        prev = currentChar;
        switch (currentChar) {
            case '-':
                if (isEq) {
                    totalDigits -= currentDigits * sign;
                } else {
                    totalDigits += currentDigits * sign;
                }
                if (zeroSign) {sign = 1; zeroSign = 0;}
                currentDigits = 0;
                sign *= -1;
                digitExist = 0;
                break;
            case '+':
                if (isEq) {
                    totalDigits -= currentDigits * sign;
                } else {
                    totalDigits += currentDigits * sign;
                }
                if (zeroSign) {sign = 1; zeroSign = 0;}
                currentDigits = 0;
                digitExist = 0;
                break;
            case '=':
                totalDigits += currentDigits * sign;
                if (zeroSign) {sign = 1; zeroSign = 0;}
                isEq = 1;
                sign = 1;
                currentDigits = 0;
                digitExist = 0;
                break;
            case 'x':
                if (digitExist) {
                    k = currentDigits * sign;
                } else {
                    k = sign;
                }
                if (isEq) {
                    totalX += k;
                } else {
                    totalX -= k;
                }
                xExists = 1;
                currentDigits = 0;
                sign = 1;
                if (isEq) {
                    rightExists = 1;
                } else {
                    leftExists = 1;
                }
                break;
            default:
                if (isNumber(currentChar)) {
                    currentDigits *= 10;
                    currentDigits += ((int)currentChar - (int)'0');
                    if (isEq) {
                        rightExists = 1;
                    } else {
                        leftExists = 1;
                    }
                    digitExist = 1;
                }
                break;
        }
    }
    totalDigits -= currentDigits * sign;

    if (!xExists || !leftExists || !rightExists) {
        printf("Not an equation");
    } else if (totalDigits != 0 && totalX == 0) {
        // 0x = n (n != 0)
        printf("NaN");
    } else if (totalX == 0) {
        // 0x = 0
        printf("Any");
    } else {
        if (totalX * totalDigits < 0) {
            printf("-");
        }
        int gcd = GCD(abs(totalX), abs(totalDigits));
        int numerator = abs(totalDigits) / gcd;
        int denumerator = abs(totalX) / gcd;
        if (denumerator == 1) {
            // not a fraction
            printf("%d", numerator);
        } else {
            printf("%d/%d", numerator, denumerator);
        }
    }
    return 0;
}
