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
    ListNode* head;
    int size;
}ListType;

void init(ListType* L)
{
    L->head = NULL;
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

void insertFirst(ListType* L, Element e)
{
    ListNode* node = makeNode(e);
    node->next = L->head;
    L->head = node;
    L->size++;
}

void insert(ListType* L, Element e, int pos)
{
    ListNode* node = makeNode(e);
    ListNode* p = L->head;

    //Invalid pos. check needed.
    if(pos == 1)
        insertFirst(L, e);
    else
    {
        for(int i = 2; i < pos; i++)
            p = p->next;
        
        node->next = p->next;
        p->next = node;
        L->size++;
    }
}

Element deleteFirst(ListType* L)
{
    if(isEmpty(L)) return -1;

    ListNode* p = L->head;
    Element e = p->data;

    L->head = p->next;
    L->size--;

    free(p);
    return e;
}

Element delete(ListType* L, int pos)
{
    if(isEmpty(L)) return -1;

    ListNode* p = L->head;
    ListNode* q;

    if(pos == 1)
        return deleteFirst(L);
    else
    {
        for(int i = 2; i <= pos; i++)
        {
            q = p;
            p = p->next;
        }
        Element e = p->data;
        q->next = p->next;
        L->size--;

        free(p);
        return e;
    }
}

void print(ListType* L)
{
    for(ListNode* p = L->head; p != NULL; p = p->next)
        printf("[%c] => ", p->data);
    printf("\b\b\b  \n");
}

int main()
{
    ListType L;
    init(&L);

    insertFirst(&L, 'A'); print(&L);
    insertFirst(&L, 'B'); print(&L); getchar();

    insert(&L, 'C', 1); print(&L);
    insert(&L, 'D', 4); print(&L);

    return 0;
}