#include <stdio.h>
#include <ctype.h>


int main() {
    // Место для чудесного кода чудесного человека
    int n; scanf("%d", &n);
    int currentLength = 0;
    int maximumLength = 0;
    char currentChar;
    getchar();
    for (int i = 0; i < n; i++) {
         do {
            currentChar = tolower(getchar());
            if (currentChar == 'a') {
                currentLength++;
            } else {
                maximumLength = (currentLength > maximumLength) ? currentLength : maximumLength;
                currentLength = 0;
            }
        } while (currentChar != '\n' && currentChar != EOF);
    }
    printf("%d\n", maximumLength);
    return 0;
}
