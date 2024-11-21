#include <stdio.h>
#include <stdlib.h>

#define N 10

void print(int A[]){
    for(int i=0; i<N; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void selectionSort(int A[]){
    for(int i = 0; i < N - 1; i++){
        print(A);
        int min = i;
        
        for(int j = i+1; j < N; j++){
            if(A[j] < A[min])
                min = j;
        }
        int tmp = A[min];
        A[min] = A[i];
        A[i] = tmp;
    }
}

int main(){
    int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    selectionSort(A);

    return 0;
}