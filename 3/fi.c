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
 * CopyByDigits(BigInt *copy, BigInt copyable, int start, int finish) {
 * Copy from copyable to copy digits from start to finish
 */
void CopyByDigits(BigInt *copy, BigInt copyable, int aBegin, int aEnd) {
    for (int i = 0; i <= aEnd - aBegin; ++i) {
        copy->data[i] = copyable.data[i + aBegin];
    }
    copy->size = aEnd - aBegin + 1;
}

/*
 * CompareBigInt(BigInt a, BigInt b)
 * retrun 0  if a == b
 * return 1  if a > b
 * return -1 if a < b
 */
int CompareBigInt(BigInt a, BigInt b) {
    if (a.size != b.size) {
        if (a.size > b.size) {
            return 1;
        }
        return -1;
    }
    for (int i = a.size - 1; i >= 0; --i) {
        if (a.data[i] != b.data[i]) {
            if (a.data[i] > b.data[i]) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}

/*
 * Divide
 * return a / b
 */
BigInt Divide(BigInt a, BigInt b) {
    // Осталось убрать один 0 справа
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
    for (int i = 0; i <= j; ++i) {
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
    FromString(&data[0], "0", 1);
    FromString(&data[1], "1", 1);

    // if (argc > 1) {
    //     test();
    //     return 0;
    // }

    // Найдем какое-то большое Fn+1
    for (int i = 2; i < 50000 + 1;
         ++i) { // 50000 - достаточно большое, но не выходит за границы. %3 == 2
        // => data[2] - наибольшее
        data[i % 3] = Plus(data[(i + 1) % 3], data[(i + 2) % 3]);
    }
    // PrintBigInt(data[2]);
    // printf("\n");
    // PrintBigInt(data[1]);

    // Умножим на 1000 data[2], чтобы не делать арифметику плавающей точки
    Shift(&data[2], 1000); // 10 ^ 1000 -сдвиг на 1000 десятичных разрядов

    // PrintBigInt(data[2]);
    // До этого шага все работает верно!
    BigInt value;
    InitBigInt(&value);
    value = Divide(data[2], data[1]);
    value.data[value.size - 1] = 0;
    value.size -= 1;
    printf("1.");
    PrintBigInt(value);

    return 0;
}

void test() {
    BigInt a, b;
    InitBigInt(&a);
    FromString(&a, "1234", 4);
    InitBigInt(&b);
    FromString(&b, "963", 3);
    BigInt value = Minus(a, b);
    PrintBigInt(value);

    InitBigInt(&a);
    FromString(&a, "1234567890", 10);
    InitBigInt(&b);
    FromString(&b, "321", 3);
    a = Divide(a, b);
    PrintBigInt(a);
    /*
    BigInt a;
    InitBigInt(&a);
    BigInt b;
    InitBigInt(&b);
    FromString(&a, "99", 2);
    FromString(&b, "301", 3);
    BigInt c;
    InitBigInt(&c);
    Plus(&c, a, b);
    printf("99 + 301 = ");
    PrintBigInt(c);

    printf("Compare 30 from 301 and 99 = ");
    printf("%d\n", CompareBigInt(b, a));

    BigInt hung;
    InitBigInt(&hung);
    FromString(&hung, "1110", 4);

    BigInt one;
    InitBigInt(&one);
    FromString(&one, "1", 1);

    BigInt someShit;
    InitBigInt(&someShit);
    Plus(&someShit, hung, one);

    printf("Minus operator; 301 - 99 = ");
    BigInt minusTest;
    InitBigInt(&minusTest);
    Minus(&minusTest, b, a);
    PrintBigInt(minusTest);

    BigInt three;
    InitBigInt(&three);
    FromString(&three, "3", 1);
    BigInt copy;
    CopyByDigits(&copy, b, 1, 2);
    printf("copy = ");
    PrintBigInt(copy);
    printf("30 / 3 = ");
    Divide(&copy, copy, three);
    PrintBigInt(copy);

    printf("Division: \n");
    Divide(&a, b, a);
    printf("\n301 / 99 = ");
    PrintBigInt(a);
    */
}
