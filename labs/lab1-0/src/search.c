#include <stdio.h>
#include <stdlib.h>
#include "search.h"

const int ALPHABET_SIZE = 1024;
const int PATTERN_LENGTH = 16; // from README.md

void CalculateTable(int *table, char *texting, int size) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        table[i] = size;
    }
    for (int i = 0; i <= size - 2; ++i) {
        table[(int)texting[i]] = size - 1 - i;
    }
}

/*
 * Search()
 * Realisation of Boyer-Moore Algorithm.
 * Reads pattern (first string) and text (all after pattern) from stdin
 */
void Search() {
    int currentChar;
    // input pattern
    char pattern[PATTERN_LENGTH];
    int size = 0;

    currentChar = getchar();
    while (currentChar != EOF && currentChar != 10) {
        pattern[size] = (char)currentChar;
        currentChar = getchar();
        size += 1;
    }
 
    // Create tabel for Boyer-Moore algo
    int table[ALPHABET_SIZE];
    CalculateTable(table, pattern, size);

    char text[PATTERN_LENGTH];
    int pastLength = size;
    int currentIndex = 0;
    int matches = 0;
    int gap = 0;
    while (1) {
        int count = 0;
        if (currentIndex > 0) {
            gap = size - currentIndex;
            for (int i = 0; i < size; ++i) {
                text[i] = text[i + gap];
            }
        }
        for (int i = currentIndex; i < size; ++i) {
            currentChar = getc(stdin);
            if (currentChar == EOF) {
                return;
            }
            text[i] = (char)currentChar;
        }
        for (int j = size - 1; j >= 0; --j) {
            printf("%d ", j + pastLength - size + 1);
            matches = pattern[j] == text[j];
            if (matches) {
                count += 1;
                continue;
            }
            if (count == 0) {
                currentIndex = size - table[(int)text[j]];
                pastLength += table[(int)text[j]];
            } else if (count == size - 1) {
                currentIndex = 0;
                pastLength += size;
            } else {
                currentIndex = 1;
                pastLength += table[(int)pattern[0]];
            }
            break;
        }
        if (matches) {
            pastLength += size;
        }
    }
}
