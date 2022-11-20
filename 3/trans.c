#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Best practice
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

struct TListNode *InsertValue(struct TList *list, int value, int index) {
    struct TListNode *current = list->Head;
    for (int i = 1; i < index; ++i) {
        current = current->Next;
    }
    struct TListNode *newNext = current->Next;
    struct TListNode *newNode = (struct TListNode *)malloc(sizeof(struct TListNode));
    newNode->value = value;
    current->Next = newNode;
    newNode->Next = newNext;
    return newNext;
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
void PrintList(struct TList list) {
    if (list.Head) { //  list not empty
        struct TListNode *current = list.Head;
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
    }
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
    int n, k, value;
    scanf("%d", &n);
    getchar();
    // Empty list
    struct TList list;
    InitList(&list);
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &value);
        AddValue(&list, value);
    }
    getchar();
    for (int t = 0; t < n - 1; ++t) {
        scanf("%d", &k);
        struct TListNode *current = list.Head;
        scanf("%d", &value);
        int index = 0;
        while (current->value <= value) {
            index++;
            current = current->Next;
            if (current == NULL) {
                break;
            }
        }
        current = InsertValue(&list, value, index);
        for (int i = 0; i < k - 1; ++i) {
            scanf("%d", &value);
            while (current->value <= value) {
                index++;
                current = current->Next;
                if (current == NULL) {
                    break;
                }
            }
            InsertValue(&list, value, index);
        }
        getchar();
    }
    PrintList(list);
    return 0;
}
