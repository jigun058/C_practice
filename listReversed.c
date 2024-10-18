#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct ListNode
{
    Element data;
    struct ListNode* next;
}ListNode;

typedef struct
{
    ListNode* tail;
    int size;
}ListType;

void init(ListType* L)
{
    L->tail = NULL;
    L->size = 0;
}

int isEmpty(ListType* L)
{
    return L->size == 0;
}

ListNode* makeNode(Element e)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = e;
    node->next = NULL;
    return node;
}

void insertLast(ListType* L, Element e)
{
    ListNode* node = makeNode(e);

    if(isEmpty(L))
    {
        L->tail = node;
        node->next = node;
    }
    else
    {
        node->next = L->tail->next;
        L->tail->next = node;
        L->tail = node;
    }
    L->size++;
}

void insertFirst(ListType* L, Element e)
{
    ListNode* node = makeNode(e);

    if(isEmpty(L))
    {
        L->tail = node;
        node->next = node;
    }
    else
    {
        node->next = L->tail->next;
        L->tail->next = node;
    }
    L->size++;
}

Element deleteFirst(ListType* L)
{
    if(isEmpty(L)) return -1;

    ListNode* p = L->tail;
    ListNode* q = p->next;

    Element e = q->data;
    p->next = q->next;

    if(p == q)
        L->tail = NULL;

    L->size--;
    free(q);
    return e;
}

int nodeCount(ListType* L)
{
    return L->size;
}

Element deleteLast(ListType* L)
{
    if(isEmpty(L)) return -1;

    ListNode* p = L->tail;
    ListNode* q = p->next;
    Element e = p->data;

    if(nodeCount(L) == 1)
        L->tail = NULL;
    else
    {
        while(q->next != p)
            q = q->next;
        q->next = p->next;
        L->tail = q;
    }

    L->size--;
    free(p);
    return e;
}

void print(ListType* L)
{
    ListNode* p = L->tail;

    // if(!isEmpty(L))
    // {
    //     do{
    //         printf("[%c] => ", p->next->data);
    //         p = p->next;
    //     }while(p != L->tail);
    //     printf("\b\b\b  \n");
    // }
    
    for(ListNode* p = L->tail; p != NULL; p = p->next)
        printf("[%c] => ", p->data);
    printf("\b\b\b  \n");
}

int main()
{
    ListType L;
    init(&L);

    insertLast(&L, 'A'); print(&L);
    insertLast(&L, 'B'); print(&L);
    insertFirst(&L, 'C'); print(&L); getchar();

    printf("[%c] Deleted : ", deleteFirst(&L)); print(&L);
    printf("[%c] Deleted : ", deleteLast(&L)); print(&L);

    return 0;
}