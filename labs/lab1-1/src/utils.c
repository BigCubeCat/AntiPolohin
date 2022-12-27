#include <stdio.h>

/*
 * StringsAreEqual(char *text, char *pattern, int size, int gap, int symbolIndex)
 * Check that pattern compares with text part
 * Print index of checked symbol
 */
int StringsAreEqual(unsigned char *text, unsigned char *pattern, int size, int gap, int symbolIndex) {
    for (int k = 0; k < size; ++k) {
        printf("%d ", symbolIndex + k);
        if (text[(gap + k) % size] != pattern[k]) {
            return 0;
        }
    }
    return 1;
}

/*
 * InputPattern(unsigned char *pattern, int *size)
 * Read pattern from stdin and write to pattern
 * Also writes pattern length to *size
 */
void InputPattern(unsigned char *pattern, int *size) {
    int currentChar;
    currentChar = getchar();
    while (currentChar != EOF && currentChar != (int)'\n') {
        pattern[*size] = (unsigned char)currentChar;
        currentChar = getchar();
        *size += 1;
    }
}


