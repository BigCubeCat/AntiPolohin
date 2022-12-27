#include "stack.h"
#include <stdio.h>

/*
 * StackInit(int *stack) 
 * Set head index
 */
void StackInit(int *stack) {
    stack[0] = 0;
}

/*
 * StackPush(int *stack, int value)
 * Push value into stack head
 */
void StackPush(int *stack, int value) {
    int head = stack[0];
    stack[head + 1] = value;
    stack[0]++;
}

/*
 * StackPop(int *stack)
 * Delete last value and return it
 */
int StackPop(int *stack) {
    int head = stack[0];
    int x = stack[head];
    stack[0]--;
    return x;
}

/*
 * StackBack(int *stack)
 * Returns last value in stack
 */
int StackBack(int *stack) {
    return stack[stack[0]];
}

/*
 * StackIsEmpty(int *stack)
 * Returns 0 if stack is empty
 */
int StackIsEmpty(int *stack) {
    return stack[0] == 0;
}
