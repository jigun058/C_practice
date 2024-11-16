#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct SimpNode{
    struct SimpNode* next;
    Element data;
}SimpNode;

typedef struct List{
    SimpNode* head;
    int size;
}List;

SimpNode* makeNode(Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->next = NULL;
    return node;
}

void init(List* L){
    SimpNode* node = makeNode('\0');
    L->head = node;
    L->size = 0;
}

int isEmpty(List* L){
    return L->size == 0;
}

int insert(List* L, int pos, Element e){
    if(L->size < pos){
        printf("%d 이하의 pos를 입력해주세요.\n", L->size);
        return -1;
    }
    
    SimpNode* node = makeNode(e);
    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p=p->next;
    }
    node->next = p->next;
    p->next = node;

    L->size += 1;
    return 0;
}

Element delete(List* L, int pos){
    if(L->size <= pos){
        printf("%d 미만의 pos를 입력해주세요.\n", L->size);
        return -1;
    }

    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p=p->next;
    }

    Element temp = p->next->data;
    p->next = p->next->next;

    return temp;
}

Element getEntry(List* L, int pos){
    if(L->size <= pos){
        printf("%d 미만의 pos를 입력해주세요.\n", L->size);
        return -1;
    }

    SimpNode* p = L->head;
    for(int i=0; i<=pos; i++){
        p=p->next;
    }

    return p->data;
}

void printList(List* L){
    SimpNode* p = L->head->next;

    while(p != NULL){
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