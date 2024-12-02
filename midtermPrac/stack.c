#include <stdio.h>
#include <stdlib.h>

#define maxSize 10

typedef struct Element{
    int num;
    char name[20];
}Element;

typedef struct Stack{
    Element data[maxSize];
    int top;
}Stack;

void init(Stack* S){
    S->top = -1;
}

int isEmpty(Stack* S){
    return S->top == -1;
};

int isFull(Stack* S){
    return S->top == maxSize-1;
};

void push(Stack* S, Element e){
    S->top += 1;
    S->data[S->top] = e;
}

Element pop(Stack* S){
    Element temp = S->data[S->top];
    S->top -= 1;
    return temp;
}

Element peek(Stack* S){
    return S->data[S->top];
}

void destroyStack(Stack* S){
    while((S->top) > -1)
        pop(S);
}

int main() {
    Stack stack;
    init(&stack);

    printf("%d\n", isEmpty(&stack));
    for(int i = 1; i<=maxSize; i++){
        Element e = {i, "번째"};
        push(&stack, e);
    }

    printf("%d\n", isFull(&stack));

    for(int i = 0; i<maxSize; i++){
        Element e = pop(&stack);
        printf("%d%s\n", e.num, e.name);
    }

    return 0;
}