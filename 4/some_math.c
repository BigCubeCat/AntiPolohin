#include <stdio.h>

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int data[1000];
    int right = n - 1;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < n; ++i) {
        while (right > i) {
            int sum = data[i] + data[right];
            if (sum == m) {
                printf("%d %d\n", data[i], data[right]);
                return 0;
            } else if (sum > m) {
                right--;
                if (right <= i) {
                    printf("No solutions\n");
                    return 0;
                }
            } else {
                break;
            }
        }
    }
    printf("No solutions\n");
    return 0;
}
