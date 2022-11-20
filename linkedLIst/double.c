#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Best practice
struct TDoubleLinkedList {
    struct TListNode {
        void* Value;
        int ValueSize;
        struct TListNode *Next;
        struct TListNode *Previous;
    };
    struct TListNode *Head;
    struct TListNode *Tail;
    size_t size;
};

/*
 * InitList(struct TDoubleLinkedList *list)
 * Run before use TList
 */
void InitList(struct TDoubleLinkedList *list) {
    list->Head = NULL;
    list->Tail = NULL;
    list->size = 0;
}

/*
 * AddValue(struct TDoubleLinkedList *list, int value)
 * Add <Value> to end of <list>
 */
void AddValue(struct TDoubleLinkedList *list, int value) {
    if (list->Tail) { // list not empty
        list->Tail->Next = (struct TListNode *) malloc(sizeof(struct TListNode));
        list->Tail = list->Tail->Next;
        list->Tail->Value = value;
        list->Tail->Next = NULL;
    } else {
        list->Head = list->Tail = (struct TListNode *) malloc(sizeof(struct TListNode));
        list->Head->Value = value;
        list->Head->Next = NULL;
    }
    ++list->size;
}

/* RemoveValue(struct TDoubleLinkedList *list, int index)
 * Remove element from <list> by <index>
 * return 1 if success;
 */
int RemoveValue(struct TDoubleLinkedList *list, int index) {
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
    for (int i = 0 ; i < index - 1; ++i)  {
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
 * PrintList(struct TDoubleLinkedList *list)
 * Print list
 */
void PrintList(struct TDoubleLinkedList *list) {
    if (list->Head) { // list not empty
        struct TListNode* current = list->Head;
        printf("%d ", current->Value);
        while (current->Next) {
            current = current->Next;
            printf("%d ", current->Value);
        }
        printf("\n");
    } else {
        printf("No Values\n");
    }
}

int GetListValue(struct TDoubleLinkedList *list, int index) {
    if (index >= list->size || index < 0) {
        printf("Invalid index\n");
        return -1;
    };
    if (index == 0) {
        return list->Head->Value;
    }
    struct TListNode* current = list->Head;
    for (int i = 0; i < index - 1; ++i) {
        current = current->Next;
    }
    return current->Next->Value;
    
}

int main() {
    // Empty list
    struct TDoubleLinkedList list;
    InitList(&list);
    PrintList(&list);

    AddValue(&list, 5);
    PrintList(&list); // 5
    RemoveValue(&list, 0); PrintList(&list); // 6
    AddValue(&list, 6);
    AddValue(&list, 8);
    AddValue(&list, 7);
    PrintList(&list); // 5 6

    RemoveValue(&list, 0); PrintList(&list); // 6

    return 0;
}
