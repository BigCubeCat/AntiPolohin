#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"
#include "utils.h"

const int PATTERN_LENGTH = 16; // from README.md

int main(void) {
    unsigned char pattern[PATTERN_LENGTH];
    int size = 0;
    InputPattern(pattern, &size);
    Search(pattern, size);
    return EXIT_SUCCESS;
}

/*
Робин-карп
                   ,__
                   |  `'.
__           |`-._/_.:---`-.._
\='.       _/..--'`__         `'-._
 \- '-.--"`      ===        /   o  `',
  )= (                 .--_ |       _.'
 /_=.'-._             {=_-_ |   .--`-.
/_.'    `\`'-._        '-=   \    _.'
         )  _.-'`'-..       _..-'`
        /_.'        `/";';`|
                     \` .'/
                      '--'
 */
