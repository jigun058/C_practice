#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct DListNode
{
    element data;
    struct DListNode* prev;
    struct DListNode* next;
}DListNode;

// typedef struct
// {
//     DListNode* H;
//     DListNode* T;
//     int size;
// }DListType;

void init(DListNode* H, DListNode* T)
{
    H->next = T;
    H->prev = H;
}

// void init(DListType* DL)
// {
//     DL->H = makeNode(0);
//     DL->T = makeNode(0);

//     DL->H->next = DL->T;
//     DL->T->prev = DL->H;

//     DL->size = 0;
// }

DListNode* makeNode(element e)
{
    DListNode* node = (DListNode*)malloc(sizeof(DListNode));
    node->data = e;
    node->prev = node->next = NULL;
    return node;
}

void insert(DListNode* H, int pos, element e)
{
    DListNode* node = makeNode(e);
    //********************************************범위를 벗어난거 테스트**********************************************
    DListNode* p = H;   // = DL->H;
    for(int i = 1; i < pos; i++)
        p = p->next;
    
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node;
}

element delete(DListNode* H, int pos)
{
    DListNode* p = H;
    for(int i = 1; i <= pos; i++)
        p = p->next;
    
    element e = p->data;

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);
    return e;
}

void print(DListNode* H, DListNode* T)
{
    for(DListNode* p = H->next; p != T; p = p->next)
        printf("[%c] <=> ", p->data);
    printf("\b\b\b\b    \n");
}

int main()
{
    //DListType* 
    DListNode* H = makeNode(0);
    DListNode* T = makeNode(0);

    init(H, T);

    insert(H, 1, 'A'); print(H, T);
    insert(H, 1, 'B'); print(H, T);
    insert(H, 3, 'C'); print(H, T);
    insert(H, 2, 'D'); print(H, T);

    printf("Delete [%c] : ", delete(H, 3)); print(H, T);

    return 0;
}