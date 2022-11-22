#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Snake {
    struct SnakeNode {
        int Index;
        int X, Y;
        struct SnakeNode *Next;
        struct SnakeNode *Prev;
    };
    struct SnakeNode *Head;
    struct SnakeNode *Tail;
    int Size;
};

int InBox(int x, int y, int N, int M) {
    return (x >= 0 && x < N) && (y >= 0 && y < M);
}

void InitNode(struct SnakeNode *node, int index, int x, int y) {
    node->Index = index;
    node->X = x;
    node->Y = y;
}

void AddNode(struct Snake *snake, int x, int y) {
    struct SnakeNode *headCopy = snake->Head;
    snake->Head = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));
    snake->Head->Next = headCopy;
    headCopy->Prev = snake->Head;
    InitNode(snake->Head, snake->Size, x, y);
    snake->Size += 1;
}

void InitSnake(struct Snake *snake, int hX, int hY, int sX, int sY) {
    snake->Head = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));
    InitNode(snake->Head, 1, sX, sY);
    snake->Tail = snake->Head;
    snake->Size = 1;
    AddNode(snake, hX, hY);
}

int InSnake(struct Snake *snake, int x, int y) {
    if (snake->Head) {
        struct SnakeNode *current = snake->Head;
        while (current) {
            if (current->X == x && current->Y == y) {
                return 1;
            }
            current = current->Next;
        }
    }
    return 0;
}

void UpdateBerry(int *berryX, int *berryY, int N, int M, struct Snake *snake) {
    *berryX = (*berryX + 16127) % N;
    *berryY = (*berryY + 16843) % M;
    if (InSnake(snake, *berryY, *berryX)) {
        UpdateBerry(berryX, berryY, N, M, snake);
    }
}

void SwapHead(struct Snake *snake, int x, int y) {
    struct SnakeNode *oldTail = snake->Tail;
    struct SnakeNode *oldHead = snake->Head;
    snake->Head = snake->Tail;
    snake->Tail = oldTail->Prev;
    oldHead->Prev = snake->Head;
    snake->Head->X = x;
    snake->Head->Y = y;
}

void GetVector(int *x, int *y, int cmd, int prev) {
    if ((cmd + 2) % 2 == prev % 2) {
        cmd = prev;
    }
    switch (cmd) {
    case 0:
        *x -= 1;
        break;
    case 2:
        *x += 1;
        break;
    case 1:
        *y += 1;
        break;
    case 3:
        *y -= 1;
        break;
    default:
        break;
    }
}

void PrintGame(int N, int M, struct Snake *snake, int bX, int bY) {
    for (int j = 0; j < M; ++j) {
        for (int i = 0; i < N; ++i) {
            if (i == bX && j == bY) {
                printf("@");
            } else if (InSnake(snake, i, j)) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int N, M, hX, hY, sX, sY, bX, bY, l, cmd;
    scanf("%d%d", &N, &M);
    getchar();
    scanf("%d%d", &hX, &hY);
    getchar();
    scanf("%d%d", &sX, &sY);
    getchar();
    scanf("%d%d", &bX, &bY);
    getchar();
    scanf("%d", &l);
    getchar();
    // Передвижение - хвост становится головой,
    // хвостом становится предыдущий элемент
    struct Snake snake;
    InitSnake(&snake, hX, hY, sX, sY);
    int prev = -1;
    for (int t = 0; t < l; ++t) {
        scanf("%d", &cmd);
        getchar();
        int x = snake.Head->X;
        int y = snake.Head->Y;
        GetVector(&x, &y, cmd, prev);
        prev = cmd;
        if (!InBox(x, y, N, M)) {
            printf("Met wall\n");
            break;
        }
        if (InSnake(&snake, x, y)) {
            // snake move to place, where tail
            printf("Met self\n");
            break;
        }
        if (x == bX && y == bY) {
            AddNode(&snake, x, y);
            UpdateBerry(&bX, &bY, N, M, &snake);
        }
        SwapHead(&snake, x, y);
    }
    printf("%d\n", snake.Size);
    return 0;
}
