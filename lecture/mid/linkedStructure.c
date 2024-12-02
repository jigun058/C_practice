#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode
{
    element data;
    struct StackNode* next;
}StackNode;

typedef struct
{
    StackNode* top;
}StackType;

void init(StackType* S)
{
    S->top = NULL;
}

int isEmpty(StackType* S)
{
    return S->top == NULL;
}

void push(StackType *S, element e)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = e;
    node->next = S->top;
    S->top = node;
}

element pop(StackType* S)
{
    if(isEmpty(S))
        return -1;
    
    StackNode* p = S->top;
    element e = p->data;

    S->top = p->next;

    free(p);
    return e;
}

void print(StackType *S)
{
    for(StackNode* p = S->top; p != NULL; p = p->next)
        printf("[%d] => ", );
}

int main()
{
    StackType S;
    init(&S);
    
    push

    return 0;
}
