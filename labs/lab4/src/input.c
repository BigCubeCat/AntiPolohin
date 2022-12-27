#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * CheckSymbol(char symbol)
 * return 1 if symbol is valid
 * else return 0
 */
int CheckSymbol(char symbol) {
    return IsOperator(symbol) || IsBracket(symbol) || IsNumber(symbol);
}

/*
 * CheckBrackets(char *string, int size)
 * return 0, if brackets invalid
 */
int CheckBrackets(char *string, int size) {
    int buf = 0;
    char previous = '\0';
    for (int i = 0; i < size; ++i) {
        if (string[i] == '(') {
            buf++;
        } else if (string[i] == ')') {
            buf--;
            if (buf < 0) {
                return 0;
            } else if (previous == '(') {
                return 0;
            }
        }
        previous = string[i];
    }
    return (buf == 0);
}
/*
 * CheckOperators(char *string, int size);
 * Checks that string not contain two signs nearby
 */
int CheckOperators(char *string, int size) {
    for (int i = 1; i < size; ++i) {
        if (IsOperator(string[i - 1]) && IsOperator(string[i])) {
            return 0;
        }
    }
    return 1;
}

/*
 * inputString(char *string)
 * Reads valid (numbers, brackets and math operators) symbols 
 * and writes to *string
 * return size of string
 */
int InputString(char *string) {
    int size = 0;
    char currentChar;
    if (!scanf("%c", &currentChar)) {
        printf("bad input\n");
        return -1;
    }
    int numbersExists = 0;
    while (currentChar != EOF && currentChar != '\n') {
        if (IsNumber(currentChar)) {
            numbersExists = 1;
        }
        string[size] = currentChar;
        size++;
        if (!scanf("%c", &currentChar)) {
            printf("bad input\n");
            return -1;
        }
        if (!CheckSymbol(currentChar)) {
            if (currentChar == EOF || currentChar == '\n') {
                break;
            }
            printf("syntax error\n");
            return -1;
        }
    }
    if (size == 0) {
        printf("syntax error\n");
        return -1;
    }
    if (IsOperator(string[0]) || IsOperator(string[size - 1])) {
        printf("syntax error\n");
        return -1;
    }
    if (!CheckBrackets(string, size) || !numbersExists || !CheckOperators(string, size)) {
        printf("syntax error\n");
        return -1;
    }
    return size;
}
