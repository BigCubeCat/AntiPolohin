#include <stdlib.h>
#include <stdio.h>
#include "next_permutation.h"

const int ZERO_CODE = (int)'0';

/*
 * checkSymbol(char symbol)
 * return 1, if symbol is decimal digit, else 0
 */
int checkSymbol(char symbol) {
    return (int)'0' <= symbol && symbol <= (int)'9';
}

int main(void) {
    char value;
    char *inputString = (char*) malloc(sizeof(char));
    int length = 0;
    int count = 0;
    int digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    void *tmp;
    while (1) { 
        if (!scanf("%c", &value)) {
            printf("bad input\n");
            free(inputString);
            return EXIT_SUCCESS;
        };
        if (!checkSymbol(value)) {
            if (value == '\n') {
                break;
            } else {
                printf("bad input\n");
                free(inputString);
                return EXIT_SUCCESS;
            }
        }
        int currentDigit = (int)value - ZERO_CODE;
        digits[currentDigit]++;
        if (digits[currentDigit] > 1) { // symbol not unique now
            printf("bad input\n");
            free(inputString);
            return EXIT_SUCCESS;
        }
        length++;
        tmp = (char*) realloc(inputString, length * sizeof(char));
        if (tmp == NULL) {
            return EXIT_SUCCESS;
        } else {
            inputString = tmp;
            inputString[length - 1] = value;
        }
    }
    if (!scanf("%d", &count)) {
        printf("bad input\n");
        free(inputString);
        return EXIT_SUCCESS;
    }
    for (int i = 0; i < count; ++i) {
        NextPermutation(inputString, length);
    }
    free(inputString);
    return EXIT_SUCCESS;
}
