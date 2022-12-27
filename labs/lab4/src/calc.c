#include "calc.h"
#include "stack.h"
#include "utils.h"
#include <stdio.h>

const int STACK_SIZE = 4096;

/*
 * Priority(int sign)
 * returns priority of sign. 
 * operations with hight priority doing first
 */
int Priority(int sign) {
    if (sign == (int)'-' || sign == (int)'+') {
        return 0;
    }
    return 1;
}

/*
 * ExecOperation(int *stack, int operation)
 * Takes two elements from stack, calculates operation 
 * and push result into stack
 * returns 1, if gets division by zero else 0
 */
int ExecOperation(int *stack, int operation) {
    int right = StackPop(stack);
    int left = StackPop(stack);
    switch (operation) {
        case (int)'+':
            StackPush(stack, left + right);
            break;
        case (int)'-':
            StackPush(stack, left - right);
            break;
        case (int)'*':
            StackPush(stack, left * right);
            break;
        case (int)'/':
            if (right == 0) {
                return 1;
            }
            StackPush(stack, left / right);
            break;
        default:
            break;
    }
    return 0;
}

void Calc(char *inputString, int size) {
    // init stack's
    int numberStack[STACK_SIZE];
    StackInit(numberStack);

    int operatorStack[STACK_SIZE];
    StackInit(operatorStack);

    for (int i = 0; i < size; ++i) {
        if (inputString[i] == '(') {
            StackPush(operatorStack, (int)'(');
        } else if(inputString[i] == ')') {
            while (StackBack(operatorStack) != (int)'(') {
                if (ExecOperation(numberStack, StackPop(operatorStack))) {
                    printf("division by zero\n");
                    return;
                }
            }
            StackPop(operatorStack);
        } else if (IsOperator(inputString[i])) {
            char currentOperation = inputString[i];
            int currentPriority = Priority((int)currentOperation);
            while (!StackIsEmpty(operatorStack) && IsOperator((char)StackBack(operatorStack))
                    && (Priority(StackBack(operatorStack)) >= currentPriority)) {
                if (ExecOperation(numberStack, StackPop(operatorStack))) {
                    printf("division by zero\n");
                    return;
                }
            }
            StackPush(operatorStack, currentOperation);
        } else {
            // number. Parse it all
            int number = 0;
            do {
                number = number * 10 + (int)(inputString[i] - '0');
                ++i;
            } while (i < size && IsNumber(inputString[i]));
            i--;
            StackPush(numberStack, number);
        }
    }
    while (!StackIsEmpty(operatorStack)) {
        if (ExecOperation(numberStack, StackPop(operatorStack))) {
            printf("division by zero\n");
            return;
        }
    }
    printf("%d\n", StackBack(numberStack));
}
