#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct SimpNode{
    struct SimpNode* next;
    Element data;
}SimpNode;

typedef struct CircList{
    SimpNode* tail;
    int size;
}CircList;

SimpNode* makeNode(Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->next = NULL;
    return node;
}

void initList(CircList* C){
    SimpNode* node = makeNode('\0');
    C->tail = node;
    C->size = 0;
}

int isEmpty(CircList* C){
    return C->tail == NULL;
}

int insert(CircList* C, int pos, Element e){
    if(C->size < pos){
        printf("%d 이하의 pos를 입력해주세요.\n", C->size);
        return -1;
    }

    SimpNode* node = makeNode(e);

    if(C->size == 0){
        node->next = node;
        C->tail->next = node;
    }

    else{
        SimpNode* p = C->tail;
        for(int i=0; i<=pos; i++){
            p = p->next;
        }
        if(pos == C->size){
            node->next = p->next;
            p->next = node;
            C->tail->next = node;
        }
        else{
            node->next = p->next;
            p->next = node;
        }
    }

    C->size += 1;
    return 0;
}

Element delete(CircList* C, int pos){
    if(isEmpty(C)){
        printf("Underflow\n");
        return -1;
    }

    if(C->size <= pos){
        printf("%d 미만의 pos를 입력해주세요.\n", C->size);
        return -1;
    }

    SimpNode* p = C->tail;

    for(int i=0; i<=pos; i++){
        p = p->next;
    }
    Element temp = p->next->data;

    if(pos == C->size - 1){
        p->next = p->next->next;
        C->tail->next = p;
    }
    else{
        p->next = p->next->next;
    }

    C->size -= 1;
    return temp;
}

Element getEntry(CircList* C, int pos){
    if(isEmpty(C)){
        printf("Underflow\n");
        return -1;
    }

    if(C->size <= pos){
        printf("%d 미만의 pos를 입력해주세요.\n", C->size);
        return -1;
    }

    SimpNode* p = C->tail;

    for(int i=0; i<=pos; i++){
        p = p->next;
    }

    return p->next->data;
}

int main() {
    CircList L;
    CircList L1;

    initList(&L);
    initList(&L1);

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