#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int land[10000];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &land[i]);
    }
    int leftMax = 0;
    int rightMax = 0;
    int left = 0;
    int right = n - 1;
    int countWater = 0;

    while (left < right) {
        if (land[left] > leftMax) {
            leftMax = land[left];
        }
        if (land[right] > rightMax) {
            rightMax = land[right];
        }
        if (leftMax >= rightMax) {
            countWater += rightMax - land[right];
            right--;
        } else {
            countWater += leftMax - land[left];
            left++;
        }
    }
    printf("%d\n", countWater);
    return 0;
}
