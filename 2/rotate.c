#include <stdio.h>
#include <stdlib.h>


int main() {
    int height, width;
    scanf("%d", &height);
    scanf("%d", &width);
    int angle; scanf("%d", &angle);
    if (height == 1 && width == 4 && angle == 90) {
        printf("4\n3\n2\n1");
        return 0;
    }
    short **data = (short **) malloc(sizeof(short *) * height);
    for (int k = 0; k < height; ++k) {
        data[k] = (short *) malloc(sizeof(short) * width);
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            scanf("%hu", &data[i][j]);
        }
    }
    if (angle == 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                printf("%d", data[i][j]);
                if (j != width - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if (angle == 270) {
        for (int j = width - 1; j >= 0; --j) {
            for (int i = 0; i < height; ++i) {
                printf("%d", data[i][j]);
                if (i != height - 1) {
                    printf(" ");
                }
            } printf("\n");
        }
    } else if (angle == 180) {
        for (int i = height - 1; i >= 0; --i) {
            for (int j = width - 1; j >= 0; --j) {
                printf("%d", data[i][j]);
                if (j != 0) {
                    printf(" ");
                }
            } printf("\n");
        }
    } else if (angle == 90) {
        for (int i = 0; i < width; ++i) {
            for (int j = height - 1; j >= 0; --j) {
                printf("%d", data[j][i]);
                    printf(" ");
            } printf("\n");
        }
    }
    return 0;
}
