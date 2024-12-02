#include <stdio.h>
#include <stdlib.h>

#define maxSize 100

typedef char Element;

typedef struct Queue{
    Element data[maxSize];
    int front;
    int rear;
}Queue;

void init(Queue *Q){
    Q->front = 0;
    Q->rear = 0;
}

int isEmpty(Queue* Q){
    return (Q->front) == (Q->rear);
}

int isFull(Queue* Q){
    return (Q->front) == (((Q->rear)+1)%maxSize);
}

void enqueue(Queue* Q, Element e){
    if(isFull(Q)) printf("Overflow\n");
    Q->rear = ((Q->rear) + 1)%100;
    Q->data[Q->rear] = e;
}

Element dequeue(Queue* Q){
    Q->front = ((Q->front) + 1)%100;
    return Q->data[Q->front];
}

int main() {
    Queue Q1;
    Queue Q2;

    init(&Q1);
    init(&Q2);

    enqueue(&Q1, 'A');
    enqueue(&Q1, 'B');
    enqueue(&Q1, 'C');
    enqueue(&Q1, 'D');
    enqueue(&Q1, 'E');

    while(isEmpty(&Q1) != 1){
        printf("%c\n", dequeue(&Q1));
    }

    return 0;
}