#include <stdio.h>
#include <stdlib.h>

struct TCell {
    int Score;
    char Block;  
};

struct TPoint {
    int X;
    int Y;
};

struct TPoint SumPoints(struct TPoint a, struct TPoint b) {
    struct TPoint result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    return result;
}


enum Cmd {
    LEFT = 'l',
    BACK = 'b',
    RIGHT = 'r',
    FORWARD = 'f'
};

int GetNumber(char c) {
    if ('0' <= c && '9' >= c) {
        return c - '0';
    }
    return -1;
}

void main() {
    
    struct TPoint left = {0, -1};
    struct TPoint right = {0, 1};
    struct TPoint forward = {-1, 0};
    struct TPoint backward = {1, 0};
    struct TPoint zero = {0, 0};
    
    int totalScore = 0;
    int N; scanf("%d\n", &N);
    struct TCell **data = (struct TCell **) malloc(sizeof(struct TCell*) * N);
    int number; char block;
    struct TPoint player;
    for (int i = 0; i < N; ++i) {
        data[i] = (struct TCell *) malloc(sizeof(struct TCell) * N);
        for (int j = 0; j < N; ++j) {
            block = getchar();
            if (block == 'x') {
                player.X = i;
                player.Y = j;
            }
            number = GetNumber(block);
            data[i][j].Score = (number >= 0) ? number : 0;

            data[i][j].Block = (block == '#') ? 1 : 0;
        }
        getchar(); // get \n
    }
    int m; scanf("%d\n", &m);
    enum Cmd cmd;
    struct TPoint newPosition;
    for (int i = 0; i < m; ++i) {
        /*
        l - left
        r - right
        b - back
        f - forward
        */
        scanf("%c", &cmd);
        switch (cmd) {
            case LEFT:
                newPosition = SumPoints(player, left);
                break;
            case RIGHT:
                newPosition = SumPoints(player, right);
                break;
            case FORWARD:
                newPosition = SumPoints(player, forward);
                break;
            case BACK:
                newPosition = SumPoints(player, backward);
                break;
            default:
                newPosition = SumPoints(player, zero);
                break;
        }
        if (!data[newPosition.X][newPosition.Y].Block) {
            // Можем пройти, идем
            totalScore += data[newPosition.X][newPosition.Y].Score;
            data[newPosition.X][newPosition.Y].Score = 0;
            player = newPosition;
        }
    }
    printf("%d\n", totalScore);
}

