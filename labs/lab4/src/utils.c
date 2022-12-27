#include "utils.h"

int IsBracket(char symbol) {
    return (symbol == ')' || symbol == '(');
}

int IsNumber(char symbol) {
    return ('0' <= symbol && symbol <= '9');
}

int IsOperator(char symbol) {
    return (symbol == '*' || symbol == '/' 
            || symbol == '+' || symbol == '-');
}


