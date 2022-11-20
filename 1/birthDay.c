#include <stdio.h>


int main() {
    // Место для чудесного кода чудесного человека
    int yearDigits[] = {0, 0, 0, 0};
    int mouthDigits[] = {0, 0};
    int dayDigits[] = {0, 0};
    char currentChar;
    for (int i = 0; i < 4; ++i) {
        scanf("%c", &currentChar);
        yearDigits[i] = (int)currentChar - (int)'0';
    }
    getchar();
    for (int i = 0; i < 2; ++i) {
        scanf("%c", &currentChar);
        mouthDigits[i] = (int)currentChar - (int)'0';
    }
    getchar();
    for (int i = 0; i < 2; ++i) {
        scanf("%c", &currentChar);
        dayDigits[i] = (int)currentChar - (int)'0';
    }
    int year = 1000 * yearDigits[0] + 100 * yearDigits[1] + 10 * yearDigits[2] + yearDigits[3];
    int mouth = 10 * mouthDigits[0] + mouthDigits[1];
    int day = 10 * dayDigits[0] + dayDigits[1];

    int daysCount[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Количество дней в каждом месяце года
    if (year % 400 == 0) {
        daysCount[1]++;
    } else if (year % 100 > 0 && year % 4 == 0) {
        daysCount[1]++;
    }
    int answer = 0;
    for (int i = 0; i < mouth - 1; ++i) {
        answer += daysCount[i];
    }
    answer += day;
    printf("%d", answer);
    return 0;
}
