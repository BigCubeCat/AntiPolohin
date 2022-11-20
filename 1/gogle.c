#include <stdio.h>

int main() {
    // Место для чудесного кода чудесного человека
    int n;
    scanf("%d", &n);
    // Наивный алгоритм
    int counter = 1;
    int salary = 0;
    while (n > 0) {
        salary++;
        n -= counter;
        counter++;
    }
    printf("%d\n", salary);
    return 0;
}
