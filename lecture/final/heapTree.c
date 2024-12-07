


#include<stdio.h>
#include<stdlib.h>

#define N 20

typedef int element;

typedef struct
{
    element heap[N];
    int heapSize;
}HeapType;

void init(HeapType* H)
{
    H->heapSize=0;
}

void upHeap(HeapType* H)
{
    int i=H->heapSize;
    element key = H->heap[i];
    
    while((i!=1)&&(key>H->heap[i/2]))
    {
        H->heap[i]=H->heap[i/2];
        i/=2;
    }
    H->heap[i]=key;
}


void insertItem(HeapType* H, element key){
    H->heapSize++;
    H->heap[H->heapSize]=key;
    upHeap(H);
}


int main(){
    HeapType H;
    init(&H);

   element keys[] = {9,7,6,5,4,3,2,2,1,3};
   
   for(int i=0; i<10;i++){
       insertItem(&H,keys[i]);
   }
   
   //print함수 만들고 insertItem에 8을 넣어서 upheap이 되었는지 확인 
   
   
   return 0;
} 