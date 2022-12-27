#include <stdio.h>
#include <stdlib.h>

typedef struct Man {
    int HP, Attack;
} Character;

void InputCharacters(Character *ch) {
    getchar();
    getchar();
    scanf("%d", &ch->Attack);
    getchar();
    getchar();
    scanf("%d", &ch->HP);
    getchar();
}

struct TList {
    struct Node {
        Character character;
        struct Node *Next;
        struct Node *Prev;
    };
    struct Node *Head;
    struct Node *Tail;
    int size;
};

void Init(struct TList *list) {
    list->size = 0;
    list->Head = NULL;
    list->Tail = NULL;
}

void Push(struct TList *list, Character value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->character = value;
    newNode->Next = NULL;
    if (list->Tail) {
        list->Tail->Next = newNode;
        newNode->Prev = list->Tail;
        list->Tail = newNode;
    } else {
        list->Head = list->Tail = newNode;
    }
    list->size += 1;
}

Character Pop(struct TList *list) {
    if (!list->Tail) {
        Character ch;
        ch.HP = -1;
        return ch;
    }
    Character answer = list->Tail->character;
    list->Tail = list->Tail->Prev;
    list->size -= 1;
    return answer;
}

struct Node *GetNext(struct TList *list, struct Node *current) {
    if (list->size == 1) {
        return current;
    } else if (list->size == 0) {
        return NULL;
    } else if (current->Next) {
        return current->Next;
    }
    return list->Head;
}

void Fight(Character *a, Character *b) {
    a->HP -= b->Attack;
    b->HP -= a->Attack;
}

void DeleteNode(struct TList *list, struct Node *deletable) {
    if (deletable == list->Head) {
        if (deletable == list->Tail) {
            list->Head = list->Tail = NULL;
        } else {
            list->Head = list->Head->Next;
            list->Head->Prev = NULL;
        }
    } else if (deletable == list->Tail) {
        list->Tail = list->Tail->Prev;
        list->Tail->Next = NULL;
    } else {
        deletable->Prev->Next = deletable->Next;
        deletable->Next->Prev = deletable->Prev;
    }
    free(deletable);
    list->size -= 1;
}

/*
 * PrintList(struct TList *list)
 * Print list
 */
void PrintList(struct TList *list) {
    if (list->Head) { // list not empty
        struct Node *current = list->Head;
        while (current) {
            printf("(%d, %d) ", current->character.Attack,
                   current->character.HP);
            current = current->Next;
        }
        printf("\n");
    } else {
        printf("No values\n");
    }
}

void test() {
    struct TList list;
    Init(&list);
    for (int i = 0; i < 10; ++i) {
        Character ch;
        ch.HP = i;
        Push(&list, ch);
    }
    printf("size = %d\n", list.size);
    PrintList(&list);
    DeleteNode(&list, list.Head->Next);
    PrintList(&list);
    DeleteNode(&list, list.Head);
    PrintList(&list);
    DeleteNode(&list, list.Tail);
    PrintList(&list);
}

int main() {
    // test();
    int sizeA, sizeB;

    scanf("%d", &sizeA);
    struct TList listA;
    Init(&listA);
    for (int i = 0; i < sizeA; ++i) {
        Character ch;
        InputCharacters(&ch);
        Push(&listA, ch);
    }

    scanf("%d", &sizeB);
    struct TList listB;
    Init(&listB);
    for (int i = 0; i < sizeB; ++i) {
        Character ch;
        InputCharacters(&ch);
        Push(&listB, ch);
    }
    struct Node *currentA = listA.Head;
    struct Node *currentB = listB.Head;

    struct Node *nextA;
    struct Node *nextB;

    int i = 0;
    while (listA.size > 0 && listB.size > 0) {
        // printf("ListA: \n");
        // PrintList(&listA);
        // printf("ListB: \n");
        // PrintList(&listB);

        Fight(&currentA->character, &currentB->character);

        nextA = GetNext(&listA, currentA);
        nextB = GetNext(&listB, currentB);

        if (currentA->character.HP <= 0) {
            DeleteNode(&listA, currentA);
        }
        if (currentB->character.HP <= 0) {
            DeleteNode(&listB, currentB);
        }
        currentA = nextA;
        currentB = nextB;
    }
    // printf("A: %d B: %d\n", listA.size, listB.size);
    if (listA.size == listB.size) {
        printf("0\n");
    } else if (listA.size > listB.size) {
        printf("-1\n");
    } else {
        printf("1\n");
    }

    return 0;
}
