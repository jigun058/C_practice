#include <stdio.h>
#include <stdlib.h>

void heapify(int A[], int i, int n) {
    int max = i;
    int left = max*2;
    int right = max*2 + 1;

    if(left <= n && A[max] < A[left]) {
        max = left;
    }
    if(right <= n && A[max] < A[right]) {
        max = right;
    }

    if(max != i) {
        int tmp = A[i];
        A[i] = A[max];
        A[max] = tmp;

        heapify(A, max, n);
    }
}

void buildHeap(int A[], int n) {
    for(int i = n / 2; i >= 1; i--) {
        heapify(A, i, n);
    }
}

void printHeap(int A[], int n) {
    for(int i = 1; i <= n; i++) {
        printf("[%d] ", A[i]);
    }
    printf("\n");
}

void heapSort(int A[], int n) {
    buildHeap(A, n);

    for(int i = n; i > 1; i--) {
        int tmp = A[1];
        A[1] = A[i];
        A[i] = tmp;

        heapify(A, 1, i-1);
    }
}


int main() {
    int A[] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = 10;

    buildHeap(A, n);
    printf("최대 힙:\n");
    printHeap(A, n);

    heapSort(A, n);
    printf("힙 정렬 결과:\n");
    printHeap(A, n);

    return 0;
}