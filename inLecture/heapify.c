#include <stdio.h>
#include <stdlib.h>

void heapify(){
    
}

void buildHeap(int A[], int i, int n){
    int max;

    if((2 * i < n) && (A[2 * i] > A[i]))
        max = 2 * i;
    else
        max = i;

    if((2 * i + 1 < n) && (A[2 * i + i] > A[max]))
        max = 2 * i + 1;
    
    if(max != i){
        int tmp = A[i];
        A[i] = A[max];
        A[max] = tmp;

        heapify(A, max, n);
    }
}

void pringHeap(int A[], int n){
    for(int i = 1; i < n; i++)
        printf("[%d] ", A[i]);
    printf("\n");
}

void heapSort(int A[], int n){
    buildHeap(A, n);
    printHeap(A, n);
    printf("--------------------------------------------------\n");

    for(int i = n-1; i > 1; i--){
        int tmp = A[i];
        A[i] = A[1];
        A[1] = tmp;

        heapify(A, 1 ,i);
    }
}

int main(){
    int A[] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    buildHeap(A, 11);
    printHeap(A, 11);

    return 0;
}