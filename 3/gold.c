#include <stdio.h>
#define INT_SIZE 32768

typedef struct BigInt BigInt;

int max(int a, int b) { return (a > b) ? a : b; }

struct BigInt {
    int data[INT_SIZE];
    int size;
};

/*
 * Initialize zero
 */
void InitBigInt(BigInt *number) {
    number->size = 0;
    for (int i = 0; i < INT_SIZE; ++i) {
        number->data[i] = 0;
    }
}

void PrintDecimal(BigInt number) {
    int num[INT_SIZE];
    int binDeg[INT_SIZE];
    int pow = 1;
    int j = 0;
    for (int i = 0; i < number.size; ++i) {
        if (number.data[i]) {
            binDeg[j] = pow;
            j++;
        }
        pow *= 2;
    }
    int inBrain = 0;
    int index = 0;
    while (binDeg[j - 1] > 0) {
        int newDigit = 0;
        int k = 0;
        for (int i = j - 1; i >= 0; --i) {
            if (!binDeg[i]) {
                break;
            }
            k += binDeg[i] % 10;
            binDeg[i] /= 10;
        }
        num[index] = (k + inBrain) % 10;
        inBrain = (k + inBrain) / 10;
        index++;
    }
    num[index] = inBrain;
    for (int i = index; i >= 0; --i) {
        printf("%d", num[i]);
    }
    printf("\n");
}

void FromString(BigInt *number, char *string, int size) {
    number->size = size;
    for (int i = 0; i < size; ++i) {
        number->data[i] = (string[size - i - 1] == '1') ? 1 : 0;
    }
}

/*
 * LowerOrEqual
 * return 1, if a <= b, else 0
 */
int LowerOrEqual(BigInt a, BigInt b) {
    if (a.size != b.size) {
        return a.size < b.size;
    }
    for (int i = b.size; i >= 0; --i) {
        if (a.data[i] > b.data[i]) {
            return 0;
        }
    }
    return 1;
}

/*
 * Equal
 * return 1 if a == b else 0
 */
int Equal(BigInt a, BigInt b) {
    if (a.size != b.size) {
        return 0;
    }
    for (int i = 0; i < b.size; ++i) {
        if (a.data[i] != b.data[i]) {
            return 0;
        }
    }
    return 1;
}

/*
 * PrintBigIntBinary
 * just print binary of number
 */
void PrintBigIntBinary(BigInt number) {
    for (int i = number.size - 1; i >= 0; --i) {
        printf("%d", number.data[i]);
    }
    printf("\n");
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
 * writes a + b to result
 */
void Plus(BigInt *result, BigInt a, BigInt b) {
    int maximum = max(a.size, b.size);
    int inBrain = 0;
    int digit;
    for (int i = 0; i < maximum; ++i) {
        digit = a.data[i] + b.data[i] + inBrain;
        result->data[i] = digit % 2;
        inBrain = (digit > 1) ? digit / 2 : 0;
    }
    result->size = maximum;
    if (inBrain) {
        result->data[maximum] = inBrain;
        ++result->size;
    }
}

/*
 * Minus
 * writes a - b to result
 * !important (a >= b)
 */
void Minus(BigInt *result, BigInt a, BigInt b) {
    int maximum = max(a.size, b.size);
    int inBrain = 0;
    int digit;
    int lastIndex = 0;
    for (int i = 0; i < maximum; ++i) {
        digit = a.data[i] - b.data[i] - inBrain;
        if (digit < 0) {
            inBrain = 1;
            result->data[i] = -digit % 2;
            continue;
        }
        result->data[i] = digit;
        inBrain = 0;
        if (result->data[i] > 0) {
            lastIndex = i;
        }
    }
    result->size = lastIndex + 1;
}

/*
 * Prod
 * writes a * b to result
 * WARNING! result must be zero
 */
void Prod(BigInt *result, BigInt a, BigInt b) {
    BigInt num;
    InitBigInt(&num);
    // num - just copy a
    Plus(&num, num, a);
    for (int i = 0; i < b.size; ++i) {
        if (b.data[i]) {
            Plus(result, *result, num);
        }
        Shift(&num, 1);
    }
}

/*
 * Divide
 * Writes a / b to result
 */
void Devide(BigInt *result, BigInt n, BigInt d) {
    BigInt quotient;
    InitBigInt(&quotient);
    BigInt r;
    InitBigInt(&r);

    for (int i = n.size - 1; i >= 0; --i) {
        Shift(&r, 1); // left shift r by 1
        r.data[0] = n.data[i];
        if (LowerOrEqual(d, r)) {
            Minus(&r, r, d);
            quotient.data[i] = 1;
            quotient.size = i + 1;
        }
    }
    *result = quotient;
}

/*
 * Общая идея
 * Ф - число фидия
 * Ф = lim Fn+1/Fn, n -> беск. Где Fn - число фибоначи
 * Значит после какого-то большого n все числа будут попадать в окресность числа
 * Ф равную 1 \ 10^3 Найдя такую мы найдем число Ф с нужной точностью
 */
int main() {
    BigInt data[3];
    BigInt oneThousand;
    BigInt test;

    InitBigInt(&oneThousand);
    FromString(&oneThousand, "11000", 5);

    InitBigInt(&test);
    FromString(&test, "101", 3); // 5

    InitBigInt(&data[0]);
    InitBigInt(&data[1]);
    InitBigInt(&data[2]);

    FromString(&data[1], "1", 1); // 5
    FromString(
        &oneThousand,
        "1111001110001101101100011111100111011101001111011010110000000101011110"
        "0011010010100101101001010100111001101111001011011011010010101011111010"
        "0001111100101010110010101011100011001011000111101000111110100011101100"
        "1111001101100100010100111011010110011010101000100001010001101011001011"
        "1100010001001000011101010111101111110101111111000101011100110100110111"
        "0111010101001000111010101111011000100000001101000001000001001000111101"
        "0110011010011100100010111100010010101010000100100010101111101101000100"
        "0011101011101000110000011000111111000110111001100010101111110110000101"
        "1100101001010101010101000100001010110111111011100001001110011010111010"
        "1010000101100110101000000101011010000110010000011011100111101000011010"
        "0101001001111110011000010111011010011111010010010100110011101111100000"
        "1001101101100111101000001110010101000010110000111011010110010101010000"
        "0000100010100011011001100011101100010011100011110110011101011100010000"
        "1110111000001111111001110111011100101001110101111110010001101001100011"
        "1100001100000010000001011000101000000010100010100000101110010100111011"
        "0011010011100101011000001010000000010110010111010101010101010010001010"
        "1011101010011110000111110110100000101111000011111010110101101011111111"
        "0111110101001001000010010011110010111000100000111110111101010011110011"
        "0100111001110010000010101100111001011011111001010111001010110110101000"
        "1000110000101111101101110010110111001100101100100100001111010011011001"
        "1110001011100001011100011000100001000111101100110010000110011110100000"
        "0000000011010111011110011100001000100101100110011001110011001101110100"
        "0001101111110000011010100000101001100010111111011111110110111001010001"
        "0011101101001001000110011000000110101011000110000101110101001010111110"
        "0011111101000001111011010100010100101010010011101011011001010110110110"
        "0111000011011011110101110111010011101100011010000110010010100010001011"
        "0000111000011101011001000110110011101111000111100111010001011011010100"
        "1100110001110110101000011011110010101001101010010100101101111010110100"
        "0100000101100001001010010010000111011101000111100001100001001011011101"
        "1011011010011000000001011110011111000011001011000101001001111001000011"
        "0100111001101111001011000110010100100001001011010100111000111010000000"
        "0010000111110100010101011011010000100110111001011101010110001111100110"
        "1011000010100101111010011101011111010001100011110011100111011011100010"
        "0110011000010000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000",
        3322); // 1000

    // Найдем какое-то большое Fn+1
    for (int i = 2; i < 10000;
         ++i) { // 50000 - достаточно большое, но не выходит за границы. %3 == 2
        // => data[2] - наибольшее
        Plus(&data[i % 3], data[(i + 1) % 3], data[(i + 2) % 3]);
    }

    // Умножим на 1000 data[2], чтобы не делать арифметику плавающей точки
    // PrintBigIntBinary(data[2]);
    BigInt zero;
    InitBigInt(&zero);

    PrintDecimal(data[2]);
    PrintDecimal(data[1]);
    Prod(&zero, data[2], oneThousand);
    // PrintDecimal(zero);
    //  Делим

    BigInt result;
    InitBigInt(&result);
    Devide(&result, zero, data[1]);
    // PrintDecimal(data[1]);
    PrintDecimal(result);
    // PrintDecimal(result);

    return 0;
}
