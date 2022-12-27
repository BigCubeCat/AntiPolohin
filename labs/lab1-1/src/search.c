#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"

const int P = 3; // for pattern

/*
 * Hash(unsigned char *pattern, unsigned char *text, int size, 
 * int *patternHash, int *currentHash, int *powPointer)
 * Calculate hash for pattern and text start
 * Write results to *patternHash and *currentHash
 * Write n - 1 degree to *pow
 */
void Hash(
        unsigned char *pattern, unsigned char *text, int size, 
        int *patternHash, int *currentHash, int *powPointer) {
    int templateHash = 0;
    int textHash = 0;
    int pow = 1; 
    for (int i = 0; i < size; i ++) { 
        templateHash += (pattern[i] % P) * pow; 
        textHash += (text[i] % P) * pow; 
        pow *= P; 
    }
    *patternHash = templateHash;
    *currentHash = textHash;
    *powPointer = pow / P; // need n - 1 degree
}

/*
 * Search(unsigned char *pattern, int size)
 * Realisation of Rabin-Karp Algorithm.
 * Take pattern and read text from stdin
 */
void Search(unsigned char *pattern, int size) {
    int currentIndex = 0; // start of string in buffer
    unsigned char *text = (unsigned char *) malloc(sizeof( unsigned char ) * size);
    int badInput = 0;
    for (int i = 0; i < size; ++i) {
        // read first symbols
        text[i] = getc(stdin);
        if (text[i] == 255) { // EOF, like in test 2
            badInput = 1;
            break;
        }
    }
    int patternHash, currentHash, pow;
    Hash(pattern, text, size, &patternHash, &currentHash, &pow);
    printf("%d ", patternHash);
    if (badInput) {
        free(text);
        return;
    }

    // start search
    int symbolIndex = 1;
    int currentChar = 1;
    while (currentChar) {
        if (currentHash == patternHash) {
            // hash's are equal, compare strings
            if (StringsAreEqual(text, pattern, size, currentIndex, symbolIndex)) {
                // string compare, find substring
                // Nothing to do ;-)
            }
        }
        int lastChar = text[currentIndex];
        currentChar = getc(stdin);
        if (currentChar == EOF) {
            break;
        }
        text[currentIndex] = currentChar;
        /*
        printf("currentIndex = %d\n", currentIndex);
        printf("|%s|\n", text);
        printf("shit = %c\n", text[(currentIndex + 1) % size]);
        printf("last = %c\n", text[(currentIndex + size) % size]);
        */
        currentHash = (currentHash / P) + (text[(currentIndex + size) % size] % 3) * pow - (lastChar % P) / P;
        /*
        int h = hash(text, size, currentIndex + 1);
        printf("h = %d\n", h);
        printf("currentHash = %d\n\n", currentHash);
        */
        currentIndex = (currentIndex + 1) % size;
        symbolIndex++;
    }
    free(text);
}

