#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "calc.h"

#define STRING_SIZE 4096

int main(void) {
    char string[STRING_SIZE];
    int size = InputString(string);
    if (size != -1) {
        Calc(string, size);
    }

    return EXIT_SUCCESS;
}
