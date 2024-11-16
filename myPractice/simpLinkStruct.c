#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct SimpNode{
    struct SimpNode* link;
    Element data;
}SimpNode;

typedef struct Stack{
    SimpNode* top;
}Stack;

typedef struct Queue{
    SimpNode* rear;
}Queue;

void initStack(Stack* S){
    S->top = NULL;
}

void initQueue(Queue* Q){
    Q->rear = NULL;
}

int isStackEmpty(Stack* S){
    return S->top == NULL;
}

int isQueueEmpty(Queue* Q){
    return Q->rear == NULL;
}

void push(Stack* S, Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->link = S->top;
    S->top = node;
}

void enqueue(Queue* Q, Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;

    if(isQueueEmpty(Q)){
        node->link = node;
        Q->rear = node;
    }

    else{

        node->link = Q->rear->link;
        Q->rear->link = node;
        Q->rear = node;
    }
}

Element pop(Stack* S){
    if(isStackEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = S->top;
    Element temp = node->data;

    S->top = node->link;

    free(node);

    return temp;
}

Element dequeue(Queue* Q){
    if(isQueueEmpty(Q)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = Q->rear->link;
    Element temp = node->data;

    if(Q->rear == node){
        Q->rear = NULL;
    }
    else{
        Q->rear->link = node->link;
    }

    free(node);
    return temp;
}

Element peek(Stack* S){
    if(isStackEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    return S->top->data;
}

Element peekFront(Queue* Q){
    if(isQueueEmpty(Q)){
            printf("Underflow\n");
            return -1;
        }

    return Q->rear->link->data;
}

int main() {
    // Stack S;

    // initStack(&S);

    // push(&S, 'A');
    // push(&S, 'B');
    // push(&S, 'C');
    // push(&S, 'D');
    // push(&S, 'E');
    // push(&S, 'F');

    // while(!isStackEmpty(&S)){
    //     printf("%c %c\n", peek(&S), pop(&S));
    // }

    Queue Q;
    initQueue(&Q);

    enqueue(&Q, 'A');
    enqueue(&Q, 'B');
    enqueue(&Q, 'C');
    enqueue(&Q, 'D');
    enqueue(&Q, 'E');

    while(!isQueueEmpty(&Q)){
        printf("%c %c\n", peekFront(&Q), dequeue(&Q));
    }

    return 0;
}