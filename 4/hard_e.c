#include <stdio.h>
#define SIZE 50000

struct TList {
    struct TListNode {
        int value;
        struct TListNode *Next;
    };
    struct TListNode *Head;
    struct TListNode *Tail;
    size_t size;
};

/*
 * InitList(struct TList *list)
 * Run before use TList
 */
void InitList(struct TList *list) {
    list->Head = NULL;
    list->Tail = NULL;
    list->size = 0;
}

/*
 * AddValue(struct TList *list, int value)
 * Add <value> to end of <list>
 */
void AddValue(struct TList *list, int value) {
    if (list->Tail) { // list not empty
        list->Tail->Next = (struct TListNode *)malloc(sizeof(struct TListNode));
        list->Tail = list->Tail->Next;
        list->Tail->value = value;
        list->Tail->Next = NULL;
    } else {
        list->Head = list->Tail =
            (struct TListNode *)malloc(sizeof(struct TListNode));
        list->Head->value = value;
        list->Head->Next = NULL;
    }
    ++list->size;
}

/* RemoveValue(struct TList *list, int index)
 * Remove element from <list> by <index>
 * return 1 if success;
 */
int RemoveValue(struct TList *list, int index) {
    if (index >= list->size || index < 0) {
        return 0;
    }
    list->size--;
    if (index == 0) {
        struct TListNode *deletableElement = list->Head;
        if (list->Tail == list->Head) {
            list->Tail = list->Head->Next;
        }
        list->Head = list->Head->Next;
        free(deletableElement);
        return 1;
    }
    struct TListNode *current = list->Head;
    for (int i = 0; i < index - 1; ++i) {
        current = current->Next;
    }
    struct TListNode *deletableElement = current->Next;
    current->Next = current->Next->Next;
    free(deletableElement);
    if (index == list->size) {
        list->Tail = current->Next;
    }
    return 1;
}

/*
 * PrintList(struct TList *list)
 * Print list
 */
void PrintList(struct TList *list) {
    if (list->Head) { // list not empty
        struct TListNode *current = list->Head;
        printf("%d ", current->value);
        while (current->Next) {
            current = current->Next;
            printf("%d ", current->value);
        }
        printf("\n");
    } else {
        printf("No values\n");
    }
}

int GetListValue(struct TList *list, int index) {
    if (index >= list->size || index < 0) {
        printf("Invalid index\n");
        return -1;
    };
    if (index == 0) {
        return list->Head->value;
    }
    struct TListNode *current = list->Head;
    for (int i = 0; i < index - 1; ++i) {
        current = current->Next;
    }
    return current->Next->value;
}

int main() {
    int L, M;
    char C;
    char string[SIZE];
    scanf("%s", string);

    struct TList list;
    InitList(&list);

    for (int i; i < SIZE; ++i) {
        if (string[i] == '\0') {
            break;
        } else if (string[i] == C) {
            AddValue(&list, i);
        }
    }
    return 0;
}
