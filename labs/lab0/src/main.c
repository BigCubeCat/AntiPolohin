#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include <ctype.h>

const int INPUT_LENGTH = 13;

int main(void) {
    int b1, b2;
    if (!scanf("%d", &b1)) {
        printf("bad input\n");
        return EXIT_SUCCESS;
    };
    if (!scanf("%d", &b2)) {
        printf("bad input\n");
        return EXIT_SUCCESS;
    }
    if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16) {
        printf("bad input\n");
        return EXIT_SUCCESS;
    }
    getchar();

    char currentChar;
    int i = 0;
    long long array[INPUT_LENGTH];
    int dotExists = 0;
    int beforeDotSize = 0;
    int afterDotSize = 0;
    while ((currentChar=tolower(getchar()))!=' ') {
        if (currentChar == '\n') {
            if (dotExists && afterDotSize == 0) {
                printf("bad input\n"); // Bad symbol, exit program
                return EXIT_SUCCESS;
            }
            break;
        }
        if (currentChar == '.') {
            if (dotExists) {
                printf("bad input\n"); // second dot. exit program
                return EXIT_SUCCESS;
            }
            dotExists = 1;
            if (beforeDotSize == 0) {
                printf("bad input\n"); // Bad symbol, exit program
                return EXIT_SUCCESS;
            }
            continue;
        } 
        array[i] = GetDecimalNumber(currentChar, b1);
        if (array[i] == -1) {
            printf("bad input\n"); // Bad symbol, exit program
            return EXIT_SUCCESS;
        }
        (dotExists) ? afterDotSize++ : beforeDotSize++ ;
        i = beforeDotSize + afterDotSize;
    }
    long long beforeDotDecimal = 0; // number befor dot in decimal number system
    long long k = 1;
    for (int i = beforeDotSize - 1; i >= 0; --i) {
        beforeDotDecimal += array[i] * k;
        k *= b1;
    }
    double afterDotDecimal = 0;
    double m = (double)b1;
    for (int i = beforeDotSize; i < beforeDotSize + afterDotSize; ++i) {
        afterDotDecimal += (double)array[i] / m;
        m *= b1;
    }
    int size = SizeBeforeDot(beforeDotDecimal, b2);
    char *beforeDotString = (char*)malloc(sizeof(char) * size);
    ToBaseBeforeDot(beforeDotDecimal, b2, beforeDotString);
    if (size == 0) {
        printf("0");
    } else {
        for (int j = size - 1; j >= 0; --j) {
            printf("%c", beforeDotString[j]);
        }
    }
    if (afterDotSize > 0) {
        // If input number not integer
        printf(".");
        for (int i = 0; i < 16; ++i) {
            afterDotDecimal *= b2;
            printf("%c", GetChar((int)afterDotDecimal % b2));
            afterDotDecimal -= (double)(int)afterDotDecimal;
        }
    }
    printf("\n");
    free(beforeDotString);
    return EXIT_SUCCESS;
}
