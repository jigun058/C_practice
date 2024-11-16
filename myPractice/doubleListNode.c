#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct DNode{
    struct DNode* prev;
    struct DNode* next;
    Element data;
}DNode;

typedef struct List{
    DNode* head;
    DNode* tail;
    int size;
}List;

DNode* makeNode(Element e){
    DNode* node = (DNode*)malloc(sizeof(DNode));
    node->data = e;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void init(List* L){
    L->head = makeNode('\0');
    L->tail = makeNode('\0');

    L->head->next = L->tail;
    L->tail->prev = L->head;
    L->size = 0;
}

int isEmpty(List* L){
    return L->size == 0;
}

int insert(List* L, int pos, Element e){
    if(L->size < pos){
        printf("%d 이하의 pos를 입력하세요.\n", L->size);
        return -1;
    }

    DNode* node = makeNode(e);
    DNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
    }

    node->next = p->next;
    node->prev = p;
    p->next->prev = node;
    p->next = node;

    L->size += 1;
    return 0;
}

Element delete(List* L, int pos){
    if(isEmpty(L)){
        printf("Underflow\n");
        return -1;
    }

    if(L->size <= pos){
        printf("%d 미만의 pos를 입력하세요.\n", L->size);
        return -1;
    }
    
    DNode* p = L->head;
    for(int i=0; i<=pos; i++){
        p = p->next;
    }
    Element temp = p->data;

    p->next->prev = p->prev;
    p->prev->next = p->next;

    free(p);
    L->size -= 1;
    return temp;
}

Element getEntry(List* L, int pos){
    if(isEmpty(L)){
        printf("리스트가 비어있습니다.\n");
        return -1;
    }

    if(L->size <= pos){
        printf("%d 미만의 pos를 입력하세요.\n", L->size);
        return -1;
    }

    DNode* p = L->head;
    for(int i=0; i<=pos; i++){
        p = p->next;
    }

    return p->data;
}

void printList(List* L){
    DNode* p = L->head->next;

    while(p != L->tail){
        printf("[%c] => ", p->data);
        p = p->next;
    }
    printf("\b\b\b     \n");
}

int main() {
    List L;
    List L1;

    init(&L);
    init(&L1);

    insert(&L, 0, 'A');
    insert(&L, 1, 'B');
    insert(&L, 0, 'C');
    insert(&L, 3, 'D');
    insert(&L, 1, 'E');
    insert(&L, 0, 'F');
    insert(&L1, 0, 'X');

    printf("%c\n", delete(&L1, 0));

    printf("%c\n", delete(&L, 5));
    printf("%c\n", getEntry(&L, 0));
    printf("%c\n", getEntry(&L, 4));
    printf("%c\n", delete(&L, 3));
    printf("%c\n", delete(&L, 3)); 


    return 0;
}