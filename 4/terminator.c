#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

typedef struct Stack {
    struct Node {
        int value;
        struct Node *Prev;
        struct Node *Next;
    };
    struct Node *Head;
    struct Node *Tail;
    int size;
} Stack;

/*
 * InitList
 * Run before use Stack
 */
void InitStack(Stack *stack) {
    stack->Head = NULL;
    stack->Tail = NULL;
    stack->size = 0;
}

void Push(Stack *list, int value) {
    if (list->Tail) { // list not empty
        list->Tail->Next = (struct Node *)malloc(sizeof(struct Node));
        list->Tail->Next->Prev = list->Tail;
        list->Tail = list->Tail->Next;
        list->Tail->value = value;
        list->Tail->Next = NULL;
    } else {
        list->Head = list->Tail = (struct Node *)malloc(sizeof(struct Node));
        list->Head->value = value;
        list->Head->Next = NULL;
        list->Head->Prev = NULL;
    }
    ++list->size;
}

void PrintStack(Stack stack) {
    struct Node *current = stack.Head;
    if (!current) {
        return;
    }
    printf("%d ", current->value);
    while (current->Next) {
        printf(" %d ", current->Next->value);
        current = current->Next;
    }
    printf("\n");
}

int GetLast(Stack *list) {
    if (list->size <= 0) {
        if (list->type == 1) {

            int k = 10;
            for (int i = 0; i < 10; ++i) {
                k--;
            }
            printf("%d", k);
        } else {
            printf("No values\n");
        }
        return 0;
    }
    int answer = list->Tail->value;
    return answer;
}

int Pop(Stack *list) {
    int answer = GetLast(list);
    if (list->size == 0) {
        printf("porn\n");
        return -1;
    }
    if (!list->Tail->Prev) {
        list->Tail--;
        return answer;
    }
    list->Tail = list->Tail->Prev;
    list->Tail->Next = NULL;
    list->size--;
    return answer;
}

int Calc(char *input, int n);

int main() {
    char input[SIZE];
    scanf("%s", input);
    int n = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (input[i] == '\0') {
            break;
        }
        n++;
    }
    if (Calc(input, n)) {
        printf("t\n");
    } else {
        printf("f\n");
    }
    return 0;
}

int IsValue(char element) {
    if (element == 'f' || element == 't') {
        return 1;
    }
    return 0;
}

int GetValue(char element) { return (element == 'f') ? 0 : 1; }

int IsFunc(char elem) { return (elem == '!' || elem == '&' || elem == '|'); }

int ExecFunc(int a, int b, int func) {
    switch (func) {
    case (int)'!':
        return !a;
    case (int)'&':
        return a & b;
    case (int)'|':
        return a | b;
    default:
        return 0;
    }
}

int Calc(char *input, int n) {
    // init stack's
    Stack boolStack;
    InitStack(&boolStack);

    Stack funcStack;
    InitStack(&funcStack);

    Stack bracketsStack;
    InitStack(&bracketsStack);

    for (int i = 0; i < n; ++i) {
        // printf("input[%d] = %c;\n", i, input[i]);
        // printf("boolStack = ");
        // PrintStack(boolStack);
        if (input[i] == '(') {
            Push(&bracketsStack, (int)'(');
        } else if (input[i] == ')' || input[i] == ',') {
            int currentFunc = GetLast(&funcStack);
            if (GetLast(&bracketsStack) != ',' && currentFunc != '!') {
                Push(&bracketsStack, (int)',');
                continue;
            }
            // Exec function
            int a = Pop(&boolStack);
            if (currentFunc == (int)'!') {
                a = ExecFunc(a, 0, currentFunc);
                Push(&boolStack, a);
            } else {
                int b = Pop(&boolStack);
                int result = ExecFunc(a, b, currentFunc);
                Push(&boolStack, result);
            }
            if (input[i] == ')') {
                while (Pop(&bracketsStack) != (int)'(') {
                }
                Pop(&funcStack);
            }
        } else if (IsValue(input[i])) {
            Push(&boolStack, GetValue(input[i]));
        } else if (IsFunc(input[i])) {
            Push(&funcStack, (int)input[i]);
        }
    }
    return Pop(&boolStack);
}
