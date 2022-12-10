#include <stdio.h>
#include <stdlib.h>

typedef struct Tring {
    struct Node {
        int value;
        struct Node *Prev;
        struct Node *Next;
    };
    struct Node *Head;
    struct Node *Tail;
    int size;
} Ring;

void Initring(Ring *ring) {
    ring->Head = NULL;
    ring->Tail = NULL;
    ring->size = 0;
}

void Push(Ring *ring, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    if (ring->Tail) {
        newNode->Prev = ring->Tail;
        ring->Tail->Next = newNode;
        ring->Tail = newNode;
        ring->Tail->Next = ring->Head;
    } else {
        ring->Head = ring->Tail = newNode;
    }
}

void DeleteNode(Ring *ring, struct Node *node) {
    if (ring->size == 1) {
        ring->size--;
        ring->Head = NULL;
        return;
    }
    node->Prev->Next = node->Next;
    node->Next->Prev = node->Prev;
    ring->size--;
}

typedef struct P {
    int Power;
    int HP;
} Character;

void Fight(Character *firstPlayer, Character *secondPlayer, struct Node *first,
           struct Node *second) {
    firstPlayer[first->value].HP -= secondPlayer[second->value].Power;
    secondPlayer[second->value].HP -= firstPlayer[first->value].Power;
}

int main() {
    Character firstPlayer[1000];
    Character secondPlayer[1000];
    int firstLen, secondLen; // Len for array, Count for count alive Characters
    scanf("%d", &firstLen);
    for (int i = 0; i < firstLen; ++i) {
        int a, b;
        getchar(); // space
        getchar(); // (
        scanf("%d", &a);
        getchar(); // ,
        getchar(); // space
        scanf("%d", &b);
        getchar();
        printf("c = %c\n", getchar());
        firstPlayer[i].HP = b;
        firstPlayer[i].Power = a;
    }
    scanf("%d", &secondLen);
    for (int i = 0; i < secondLen; ++i) {
        int a, b;
        getchar(); // space
        getchar(); // (
        scanf("%d", &a);
        getchar(); // ,
        getchar(); // space
        scanf("%d", &b);
        getchar();
        getchar();
        secondPlayer[i].HP = b;
        secondPlayer[i].Power = a;
    }
    Ring firstRing;
    Ring secondRing;
    Initring(&firstRing);
    Initring(&secondRing);
    for (int i = 0; i < firstLen; ++i) {
        Push(&firstRing, i);
    }
    for (int j = 0; j < secondLen; ++j) {
        Push(&secondRing, j);
    }
    struct Node *first = firstRing.Head;
    struct Node *second = secondRing.Head;

    while (firstRing.size > 0 && secondRing.size > 0) {
        Fight(firstPlayer, secondPlayer, first, second);
        if (firstPlayer[first->value].HP <= 0) {
            struct Node *cpy = first->Next;
            DeleteNode(&firstRing, first);
            first = cpy;
        } else {
            first = first->Next;
        }
        if (secondPlayer[second->value].HP <= 0) {
            struct Node *cpy = second->Next;
            DeleteNode(&secondRing, second);
            second = cpy;
        } else {
            second = second->Next;
        }
    }
    if (firstRing.size + secondRing.size == 0) {
        printf("0\n");
    } else if (firstRing.size == 0) {
        printf("-1\n");
    } else {
        printf("1\n");
    }
    return 0;
}
