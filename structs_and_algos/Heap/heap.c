#include <stdio.h>

void swap(int *a, int *b) {
    int *c = b;
    b = a;
    a = c;
}

void SiftDown(int k, int *heap, int n) {
    int left = 2 * k + 1;
    int right = 2 * k + 2;
    int mink = k;
    if (left < n && heap[left] < heap[mink]) {
        mink = left;
    }
    if (right < n && heap[right] < heap[mink]) {
        mink = right;
    }
    if (mink != k) {
        swap(&heap[k], &heap[mink]);
        SiftDown(mink, heap, n);
    }
}

/*
 * Обработка добавления элемента
 */
void SiftUp(int k, int *heap, int n) {
    int root = (k - 1) / 2;
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    int mink = root;
    if (left < n && heap[left] < heap[mink]) {
        mink = left;
    }
    if (right < n && heap[right] < heap[mink]) {
        mink = right;
    }
    if (mink != k) {
        swap(&heap[k], &heap[mink]);
        SiftUp(mink, heap, n);
    }
}

void AddValue(int *heap, int *n, int value) {
    *n += 1;
    heap[*n - 1] = value;
    SiftUp(*n - 1, heap, *n);
}

int EtractMain(int *heap, int *n) {
    int min = heap[0];
    swap(&heap[0], &heap[n - 1]);
    *n -= 1;
    SiftDown(0, heap, *n);
    return min;
}

int main() {}
