#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct SimpNode{
    Element data;
    struct SimpNode* next;
}SimpNode;

typedef struct List{
    SimpNode* head;
    int size;
}List;

void initList(List* L){
    L->size = 0;
    L->head = NULL;
}

int isListEmpty(List* L){
    return L->head == NULL;
}

SimpNode* makeNode(Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->next = NULL;
    return node;
}

int insert(List* L, int pos, Element e){
    if(L->size < pos){
        printf("%d 이하의 pos값을 입력해주세요\n", L->size);
        return -1;
    }

    else{
        SimpNode* node = makeNode(e);
        
        if(isListEmpty(L)){
            node->next = NULL;
            L->head = node;
            L->size += 1;
        }

        else{
            if(pos == 0){
                node->next = L->head;
                L->head = node;
                L->size += 1;
            }

            else{
                SimpNode* p = L->head;
                for(int i=1; i<pos; i++){
                    p = p->next;
                }

                node->next = p->next;
                p->next = node;
                L->size += 1;
            }
        }

        return 0;
    }
}

Element delete(List* L, int pos){
    if(isListEmpty(L)){
        printf("Underflow\n");
        return -1;
    }

    if(L->size <= pos){
        printf("%d 미만의 pos값을 입력해주세요\n", L->size);
        return -1;
    }

    Element temp;

    if(pos == 0){
        SimpNode* node = L->head;
        temp = node->data;
        L->head = node->next;
        L->size -= 1;
        free(node);
    }

    else{
        SimpNode* p = L->head;
        for(int i=1; i<pos; i++){
            p = p->next;
        }
        SimpNode* nodeToDel = p->next;

        temp = p->next->data;
        p->next = p->next->next;
        L->size -= 1;
        free(nodeToDel);
    }

    return temp;
}

Element getEntry(List* L, int pos){
    if(isListEmpty(L)){
        printf("리스트가 비어있습니다.\n");
        return -1;
    }

    if(L->size <= pos){
        printf("%d 미만의 pos값을 입력해주세요\n", L->size);
        return -1;
    }

    SimpNode* node = L->head;

    for(int i=0; i<pos; i++){
        node = node->next;
    }

    return node->data;
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