#include <stdio.h>
#include <stdlib.h>

#define maxSize 100

typedef char Element;

typedef struct Dequeue{
    Element data[maxSize];
    int front;
    int rear;
}Dequeue;

void init(Dequeue* D){
    D->front = 0;
    D->rear = 0;
}

int isEmpty(Dequeue* D){
    return D->front == D->rear;
}

int isFull(Dequeue* D){
    return (((D->rear) + 1) % maxSize) == D->front;
}

void addFront(Dequeue* D, Element e){
    if(!isFull(D)){
        D->data[D->front] = e;
        D->front = (D->front + maxSize - 1) % maxSize;
    }
    else printf("Overflow\n");
}

void addRear(Dequeue* D, Element e){
    if(!isFull(D)){
        D->rear = (D->rear + 1) % maxSize;
        D->data[D->rear] = e;
    }
    else printf("Overflow\n");
}

Element deleteFront(Dequeue* D){
    if(isEmpty(D))
        printf("Underflow\n");

    D->front = (D->front + 1) % maxSize;
    return D->data[D->front];
}

Element deleteRear(Dequeue* D){
    if(isEmpty(D))
        printf("Underflow\n");
    
    Element temp = D->data[D->rear];
    D->rear = (D->rear + maxSize - 1) % maxSize;
    return temp;
}

Element peekFront(Dequeue *D){
    if(isEmpty(D))
        printf("Null\n");

    D->front = (D->front + 1) % maxSize;
    Element temp = D->data[D->front];
    D->front = (D->front + maxSize - 1) % maxSize;
    return temp;
}

Element peekRear(Dequeue *D){
    if(isEmpty(D))
        printf("Null\n");
    
    return D->data[D->rear];
}

int main() {
    Dequeue D1;

    init(&D1);

    addFront(&D1, 'A');
    addFront(&D1, 'B');
    addFront(&D1, 'C');
    addRear(&D1, 'D');
    addRear(&D1, 'E');

    while(!isEmpty(&D1)){
        printf("%c\n", peekRear(&D1));
        printf("%c\n", deleteFront(&D1));
    }

    return 0;
}