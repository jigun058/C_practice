#include <stdio.h>
#include <stdlib.h>

#define N 30

typedef int element;

typedef struct HeapType {
    element heap[N];
    int heapsize;
} HeapType;

void init(HeapType* H) {
    H->heapsize = 0;
}

void upHeap(HeapType* H) {
    int i = H->heapsize;

    element key = H->heap[i];

    while(i != 1 && (key > H->heap[i/2])) {
        H->heap[i] = H->heap[i/2];
        H->heap[i/2] = key;
        i /= 2;
    }
}

void insertItem(HeapType* H, element key) {
    H->heapsize += 1;
    H->heap[H->heapsize] = key;
    upHeap(H);
}

element heapPop(HeapType* H) {
    if(H->heapsize == 0) {
        printf("힙이 비어있습니다.\n");
        return -1;
    }

    H->heapsize -= 1;
    element temp = H->heap[1];
    H->heap[1] = H->heap[H->heapsize];

    int i = 1;
    int child;
    while(i*2 <= H->heapsize) {
        if(2*i < H->heapsize && H->heap[2*i] > H->heap[2*i+1])
            child = 2 * i;
        else
            child = 2 * i + 1;
        
        if(H->heap[i] > H->heap[child])
            break;
        else {
            element tmp = H->heap[i];
            H->heap[i] = H->heap[child];
            H->heap[child] = tmp;
            i = child;
        }
    }

    return temp;
}

void print(HeapType* H) {
    for(int i = 1; i <= H->heapsize; i++)
        printf("[%d] ", H->heap[i]);
    printf("\n");
}

int main(){
    HeapType H;
    init(&H);

    element keys[] = {9,7,6,5,4,3,2,2,1,3};
   
    for(int i=0; i<10; i++){
        insertItem(&H, keys[i]);
    }

    insertItem(&H, 8);
    print(&H);

    printf("%d \n", heapPop(&H));
    print(&H);
    printf("%d \n", heapPop(&H));
    print(&H);

    
    
    return 0;
} 