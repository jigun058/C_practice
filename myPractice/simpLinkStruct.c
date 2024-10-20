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

int isEmpty(Stack* S){
    return S->top == NULL;
}

void push(Stack* S, Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->link = S->top;
    S->top = node;
}

Element pop(Stack* S){
    if(isEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = S->top;
    Element temp = node->data;

    S->top = node->link;

    free(node);

    return temp;
}

Element peek(Stack* S){
    if(isEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    return S->top->data;
}


int main() {
    Stack S;

    initStack(&S);

    push(&S, 'A');
    push(&S, 'B');
    push(&S, 'C');
    push(&S, 'D');
    push(&S, 'E');
    push(&S, 'F');

    while(!isEmpty(&S)){
        printf("%c %c\n", peek(&S), pop(&S));
    }

    return 0;
}