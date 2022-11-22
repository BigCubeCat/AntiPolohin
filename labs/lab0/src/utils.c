#include <string.h>
#include <math.h>
#include "utils.h"

char CHARS[17] = "0123456789abcdef"; // alphabet
const int MINIMUM_NUMBER = (int)'0'; // min number code
const int MAXIMUM_NUMBER = (int)'9';
const int MINIMUM_LETTER = (int)'a'; // min letter code


/*
 * CheckNumber(int digit, int base)
 * check, that digit exists in current number system
 */
int CheckNumber(int digit, int base) {
    return (digit < base && digit >= 0);
}

/*
 * getDecimalNumber(char symbol, int base)
 * gets char symbol - digit
 * and base - number base
 * returns decimal digit, if success
 * else returns -1 
 */
int GetDecimalNumber(char symbol, int base) {
    int charInt = (int)symbol;
    int value;
    if (charInt <= MAXIMUM_NUMBER) {
        value = charInt - MINIMUM_NUMBER;
    } else {
        value = 10 + charInt - MINIMUM_LETTER;
    }
    if (CheckNumber(value, base)) {
        return value;
     } 
    return -1;
}

void ToBaseBeforeDot(long long decimalNumber, int base, char *string) {
    int i = 0;
    while (decimalNumber > 0) {
        string[i] = CHARS[decimalNumber % base];
        decimalNumber /= base;
        ++i;
    }
}

/*
 * sizeBeforeDot(long long decimalNumber, int base)
 * returns length of decimalNumber in current number system
 */
int SizeBeforeDot(long long decimalNumber, int base) {
    int result = 0;
    while (decimalNumber > 0) {
        decimalNumber /= base;
        result++;
    }
    return result;
}

/*
 * GetChar(int digitNumber)
 * returns symbol of number
 */
char GetChar(int digitNumber) {
    return CHARS[digitNumber];
}

