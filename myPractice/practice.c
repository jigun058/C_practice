#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Element;

typedef struct SimpNode{
    struct SimpNode* next;
    Element data;
}SimpNode;

typedef struct List{
    SimpNode* head;
}List;

SimpNode* makeNode(Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->next = NULL;
    return node;
}

void init(List* L){
    L->head = makeNode(0);
}

int isEmpty(List* L){
    return L->head->next == NULL;
}

int insert(List* L, int pos, Element e){
    SimpNode* node = makeNode(e);
    
    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
        if(p == NULL){
            printf("pos 범위 오류\n");
            return -1;
        }
    }

    node->next = p->next;
    p->next = node;
    return 0;
}

Element delete(List* L, int pos){
    if(isEmpty(L)){
        printf("underflow\n");
        return -1;
    }

    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
        if(p->next == NULL){
            printf("pos 범위 오류\n");
            return -1;
        }
    }

    Element temp = p->next->data;
    SimpNode* nodeToDel = p->next;
    p->next = p->next->next;
    
    free(nodeToDel);
    return temp;
}

Element getEntry(List* L, int pos){
    if(isEmpty(L)){
        printf("리스트가 비어있습니다.\n");
        return -1;
    }

    SimpNode* p = L->head;
    for(int i=0; i<pos; i++){
        p = p->next;
        if(p->next == NULL){
            printf("pos 범위 오류\n");
            return -1;
        }
    }

    return p->next->data;
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
    init(&L);

    int count = 0;
    srand(time(NULL));
    while(count < 10){
        int num = rand() % 100;

        int hasSame = 0;

        for(int j=0; j<count; j++){
            if(getEntry(&L, j) == num){
                hasSame = 1;
                break;
            }
        }
        if(!hasSame){
            insert(&L, count, num);
            count += 1;
        }
    }

    List Sorted;
    init(&Sorted);

    insert(&Sorted, 0, delete(&L, 0));

    count = 1;
    while(count < 10){
        int temp = delete(&L, 0);
        for(int i=0; i<=count; i++){
            if(i==count){
                insert(&Sorted, i, temp);
                count += 1;
                break;
            }
            if(temp < getEntry(&Sorted, i)){
                insert(&Sorted, i, temp);
                count += 1;
                break;
            }
        }
    }

    for(int i=0; i<10; i++)
        printf("%d\n", delete(&Sorted, 0));


    return 0;
}