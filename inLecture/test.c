#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode{
    struct ListNode* next;
    element data;
}ListNode;

typedef struct{
    ListNode* head;
}ListType;

ListNode* makeNode(element e){
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));

    node->data = e;
    node->next = NULL;

    return node;
}

void init(ListType* L){
    L->head = makeNode(' '); // head node

    L->head->next = NULL;
}

int isEmpty(ListType* L){
    return L->head->next == NULL;
}

void insert(ListType* L, int pos, element e){
    ListNode* node = makeNode(e);
    ListNode* before = L->head;

    for (int i = 1 ; i < pos ; i++){
        before = before->next; //before 위치까지 노드를 옮김
    }

    node->next = before->next;
    before->next = node;
}

element delete(ListType* L, int pos){
    ListNode* before = L->head;

    for (int i = 1 ; i < pos ; i ++){
        before = before->next;
    }

    ListNode* p = before->next;
    element e = p->data;
    before->next = p->next;
    free(p);
    return e;
}

void printList(ListType* L){
    ListNode* p = L->head->next;

    while (p != NULL){
        printf("[%d] => ", p->data);
        p = p->next;
    }
    printf("\b\b\b      \n");
}

int SearchPoint(ListType* L, int num){
    ListNode* p = L->head->next;
    int i = 1;

    while (p != NULL){
        if(p->data > num){
            break;
        }
        else if(p->data == num){
            i = -1;
            break;
        }else{
            p = p->next;
            i += 1;
        }
    }
    return i;
}

void makeSet(ListType* L){
    for(int i = 1; i < 10 ; i ++){
        int random = rand()%30+1;

        if(i == 1){
            insert(L, 1, random);
        }else{
            int point = SearchPoint(L, random);
            if(point != -1){
                insert(L, point , random);
            }
        }
    }
}

void intersetcion(ListType* L, ListType* A, ListType* B){
    ListNode* aPoint = A->head->next;
    ListNode* bPoint = B->head->next;

    int i = 1;

    while (aPoint != NULL && bPoint != NULL){
        if(aPoint->data == bPoint->data){
            insert(L, i, aPoint->data);
            i++;
            aPoint = aPoint->next;
            bPoint = bPoint->next;
        }
        else if(aPoint->data > bPoint->data){
            bPoint = bPoint->next;
        }else{
            aPoint = aPoint->next;
        }
    }
}

void uni(ListType* L, ListType* A, ListType* B){
    ListNode* aPoint = A->head->next;
    ListNode* bPoint = B->head->next;

    int i = 1;

    while (aPoint != NULL && bPoint != NULL){
        if(aPoint->data == bPoint->data){
            insert(L, i, aPoint->data);
            i++;
            aPoint = aPoint->next;
            bPoint = bPoint->next;
        }
        else if(aPoint->data > bPoint->data){
            insert(L, i, bPoint->data);
            bPoint = bPoint->next;
            i++;
        }else{
            insert(L, i, aPoint->data);
            aPoint = aPoint->next;
            i++;
        }
    }
    // 리스트 A에 남은 데이터가 있으면 추가
    while (aPoint != NULL){
        insert(L, i, aPoint->data);
        i++;
        aPoint = aPoint->next;
    }

    // 리스트 B에 남은 데이터가 있으면 추가
    while (bPoint != NULL){
        insert(L, i, bPoint->data);
        i++;
        bPoint = bPoint->next;
    }
}

void minus(ListType* L, ListType* A, ListType* B){
    ListNode* aPoint = A->head->next;
    ListType inter;
    init(&inter);
    intersetcion(&inter, A, B);
    ListNode* minusPoint = inter.head->next;

    int i = 1;

    while (aPoint != NULL){
        if(minusPoint != NULL && aPoint->data == minusPoint->data){
            aPoint = aPoint->next;
            minusPoint = minusPoint->next;
        }
        else if(minusPoint != NULL && aPoint->data > minusPoint->data){
            minusPoint = minusPoint->next;
        }
        else{
            insert(L, i, aPoint->data);
            aPoint = aPoint->next;
            i++;
        }
    }
}

int main(){

    ListType listA;
    ListType listB;

    init(&listA);
    init(&listB);

    makeSet(&listA);
    printf("List A : ");    printList(&listA);
    makeSet(&listB);
    printf("List B : ");    printList(&listB);

    ListType inter;
    init(&inter);
    intersetcion(&inter, &listA, &listB);
    printf("교집합 : ");    printList(&inter);

    ListType unio;
    init(&unio);
    uni(&unio, &listA, &listB);
    printf("힙집합 : ");    printList(&unio);

    ListType AminusB;
    init(&AminusB);
    minus(&AminusB, &listA, &listB);
    printf("A-B : ");    printList(&AminusB);

    ListType BminusA;
    init(&BminusA);
    minus(&BminusA, &listB, &listA);
    printf("B-A : ");    printList(&BminusA);

    return 0;
}