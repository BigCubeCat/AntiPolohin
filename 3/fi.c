#include <stdio.h>
#define INT_SIZE 32768

typedef struct BigInt BigInt;

int max(int a, int b) { return (a > b) ? a : b; }
void test();

struct BigInt {
    int data[INT_SIZE];
    int size;
};

/*
 * PrintBigInt
 * just print number
 */
void PrintBigInt(BigInt number) {
    for (int i = number.size - 1; i >= 0; --i) {
        printf("%d", number.data[i]);
    }
    printf("\n");
}

/*
 * Initialize zero
 */
void InitBigInt(BigInt *number) {
    number->size = 0;
    for (int i = 0; i < INT_SIZE; ++i) {
        number->data[i] = 0;
    }
}

void FromString(BigInt *number, char *string, int size) {
    number->size = size;
    for (int i = 0; i < size; ++i) {
        number->data[i] = (string[size - i - 1] - '0');
    }
}

/*
 * Shift
 * << operator. Change number
 */
void Shift(BigInt *number, int shift) {
    // << for BigInt
    for (int i = number->size - 1 + shift; i >= shift; --i) {
        number->data[i] = number->data[i - shift];
    }
    for (int i = shift - 1; i >= 0; --i) {
        number->data[i] = 0;
    }
    number->size += shift;
}

/*
 * Plus
 * return a + b
 */
BigInt Plus(BigInt a, BigInt b) {
    // TODO
    BigInt result;
    int maximum = max(a.size, b.size);
    int inBrain = 0;
    int digit;
    for (int i = 0; i < maximum; ++i) {
        digit = a.data[i] + b.data[i] + inBrain;
        result.data[i] = digit % 10;
        inBrain = (digit > 9) ? digit / 10 : 0;
    }
    result.size = maximum;
    if (inBrain) {
        result.data[maximum] = inBrain;
        ++result.size;
    }
    return result;
}

/*
 * Minus
 * return a - b
 * !important (a >= b)
 */
BigInt Minus(BigInt a, BigInt b) {
    int inBrain = 0;
    int digit;
    int lastIndex = 0;
    BigInt result;
    InitBigInt(&result);
    for (int i = 0; i < a.size; ++i) {
        digit = inBrain + a.data[i] - b.data[i];
        if (digit < 0) {
            result.data[i] = (10 + digit) % 10;
            inBrain = -1;
        } else {
            result.data[i] = digit;
            inBrain = 0;
        }
        if (result.data[i] > 0) {
            lastIndex = i;
        }
    }
    result.size = lastIndex + 1;
    return result;
}

/*
 * MultiplyTable
 * writes to table[10]
 * 0, 1 * number, 2 * number, ..... , 9 * number
 */
void MultiplyTable(BigInt *table, BigInt number) {
    BigInt value;
    InitBigInt(&value);
    for (int i = 0; i < 10; ++i) {
        table[i] = value;
        value = Plus(value, number);
    }
}
/*
 * CompareBigInt(BigInt a, BigInt b)
 * retrun 0  if a == b
 * return 1  if a > b
 * return -1 if a < b
 */
int CompareBigInt(BigInt a, BigInt b) {
    if (a.size != b.size) {
        return (a.size > b.size) ? 1 : -1;
    }
    for (int i = a.size - 1; i >= 0; --i) {
        if (a.data[i] != b.data[i]) {
            return (a.data[i] > b.data[i]) ? 1 : -1;
        }
    }
    return 0;
}

/*
 * Divide
 * return a / b
 */
BigInt Divide(BigInt a, BigInt b) {
    BigInt result;
    int res[INT_SIZE];
    int j = 0;

    if (a.size < b.size) {
        result.size = 0;
        result.data[0] = 0;
        return result;
    }

    BigInt multiplyTable[10];
    MultiplyTable(multiplyTable, b);

    int end;
    end = a.size - b.size;

    BigInt tmp;
    tmp.size = b.size;
    for (int i = a.size - 1; i >= a.size - b.size; --i) {
        tmp.data[b.size + i - a.size] = a.data[i];
    }
    int isStarted = 0;
    while (end >= 0) {
        // copy digits to temp number
        int k = CompareBigInt(tmp, b);
        if (k == -1) {
            res[j] = 0;
            j++;
            Shift(&tmp, 1);
            end--;
            tmp.data[0] = a.data[end];
        } else {
            int index = 0;
            for (int mult = 0; mult < 10; ++mult) {
                if (CompareBigInt(multiplyTable[mult], tmp) < 1) {
                    index = mult;
                } else {
                    break;
                }
            }
            res[j] = index;
            j++;
            tmp = Minus(tmp, multiplyTable[index]);
            Shift(&tmp, 1);
            end--;
            tmp.data[0] = a.data[end];
        }
    }
    for (int i = 0; i <= j; ++i) { // Небольшой костыль
        result.data[i] = res[j - i - 1];
    }
    result.size = j - 1;
    return result;
}

int main(int argc, char *argv[]) {
    BigInt data[3];
    BigInt oneThousand;
    InitBigInt(&data[0]);
    InitBigInt(&data[1]);
    InitBigInt(&data[2]);
    // Первые два числа фибоначи
    FromString(&data[0], "0", 1);
    FromString(&data[1], "1", 1);

    // Найдем какое-то большое Fn+1
    for (int i = 2; i < 50000 + 1; ++i) {
        // 50000 - достаточно большое, и не выходит за границы по времени.
        // 50000 % 3 = 2 => data[2] - наибольшее
        data[i % 3] = Plus(data[(i + 1) % 3], data[(i + 2) % 3]);
    }

    // Умножим на 1000 data[2], чтобы не делать арифметику плавающей точки :-)
    Shift(&data[2], 1000); // 10 ^ 1000 -сдвиг на 1000 десятичных разрядов

    BigInt value;
    InitBigInt(&value);
    value = Divide(data[2], data[1]);
    // По сути убираем 1 из нашего числа. Полученое число - цифры после запятой
    value.data[value.size - 1] = 0;
    value.size -= 1;
    printf("1.");
    PrintBigInt(value);

    return 0;
}
