#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct simpNode{
    Element data;
    struct simpNode* next;
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

void initList(List* L){
    L->size = 0;
    L->head = (SimpNode*)malloc(sizeof(SimpNode));
    L->head->next = NULL;
}

int isEmpty(List* L){
    return L->head->next == NULL;
}

int insert(List* L, int pos, Element e){
    if(L->size < pos){
        printf("%d이하의 pos를 입력하세요.\n", L->size);
        return -1;
    }
    
    SimpNode* node = makeNode(e);

    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
    }

    node->next = p->next;
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
        printf("%d미만의 pos를 입력하세요.\n", L->size);
        return -1;
    }

    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
    }

    SimpNode* nodeToDel = p->next;
    Element temp = p->next->data;

    p->next = p->next->next;

    free(nodeToDel);
    L->size -= 1;
    return temp;
}

Element getEntry(List* L, int pos){
    if(isEmpty(L)){
        printf("리스트가 비어있습니다.\n");
        return -1;
    }

    if(L->size <= pos){
        printf("%d미만의 pos를 입력하세요.\n", L->size);
        return -1;
    }

    SimpNode* p = L->head;

    for(int i=0; i<pos; i++){
        p = p->next;
    }

    return p->next->data;
}

int main() {
    List L;
    List L1;

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