#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//////////////////////스택과 큐//////////////////////
typedef struct SimpNode{
    struct SimpNode* next;
    char data;
}SimpNode;

typedef struct Stack{
    SimpNode* top;
}Stack;

typedef struct Queue{
    SimpNode* rear;
}Queue;

void initStack(Stack* S){
    S->top = NULL;
}

void initQueue(Queue* Q){
    Q->rear = NULL;
}

int isStackEmpty(Stack* S){
    return S->top == NULL;
}

int isQueueEmpty(Queue* Q){
    return Q->rear == NULL;
}

void push(Stack* S, int e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    node->next = S->top;
    S->top = node;
}

void enqueue(Queue* Q, int e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;

    if(isQueueEmpty(Q)){
        node->next = node;
        Q->rear = node;
    }

    else{

        node->next = Q->rear->next;
        Q->rear->next = node;
        Q->rear = node;
    }
}

char pop(Stack* S){
    if(isStackEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = S->top;
    int temp = node->data;

    S->top = node->next;

    free(node);

    return temp;
}

char dequeue(Queue* Q){
    if(isQueueEmpty(Q)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = Q->rear->next;
    int temp = node->data;

    if(Q->rear == node){
        Q->rear = NULL;
    }
    else{
        Q->rear->next = node->next;
    }

    free(node);
    return temp;
}

char peek(Stack* S){
    if(isStackEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    return S->top->data;
}

char peekFront(Queue* Q){
    if(isQueueEmpty(Q)){
            printf("Underflow\n");
            return -1;
        }

    return Q->rear->next->data;
}
///////////////////////////////////////////////////////

typedef struct AdjVertex{
    char aName;
    struct AdjVertex* next;
}AdjVertex;

typedef struct Vertex{
    char vName;
    int isVisit;
    AdjVertex* aHead;
    struct Vertex* next;
}Vertex;

typedef struct{
    Vertex* vHead;
}GraphType;

void initGraph(GraphType* G){
    G->vHead = NULL;
}

void makeVertex(GraphType* G, char vName){
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisit = FALSE;
    v->aHead = NULL;
    v->next = NULL;

    Vertex* p = G->vHead;

    if(p == NULL)
        G->vHead = v;
    else{
        while(p->next != NULL)
            p = p->next;
        p->next = v;
    }
}

Vertex* findVertex(GraphType* G, char vName){
    Vertex* p = G->vHead;

    while(p->vName != vName)
        p = p->next;
    
    return p;
}

void makeAdjVertex(Vertex* v, char aName){
    AdjVertex* a = (AdjVertex*)malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->next = NULL;

    AdjVertex* p = v->aHead;

    if(p == NULL)
        v->aHead = a;
    else{
        while(p->next != NULL)
            p = p->next;
        p->next = a;
    }
}

void insertEdge(GraphType* G, char v1, char v2){
    Vertex* v = findVertex(G, v1);
    makeAdjVertex(v, v2);

    v = findVertex(G, v2);
    makeAdjVertex(v, v1);
}

// 현재 지점에서 탐색 가능한 인접 정점이 두 개 이상인 경우는 peek, 한 개 이하인 경우는 pop을 통해 다음 지점 반환
char peekOrPop(GraphType* G, Stack* S){
    char s = peek(S);
    Vertex* p = findVertex(G, s);

    int count = 0;
    for(AdjVertex* a = p->aHead; a != NULL; a = a->next){
        Vertex* b = findVertex(G, a->aName);
        if(!(b->isVisit))
            count += 1;
    }

    if(count >= 2)
        return peek(S);
    else
        return pop(S);
}

void print(GraphType* G){
    for(Vertex* p = G->vHead; p != NULL; p = p->next){
        printf("[%c] : ", p->vName);
        for(AdjVertex* q = p->aHead; q != NULL; q = q->next)
            printf("[%c]", q->aName);
        printf("\n");
    }
}

void DFS(GraphType* G, char s){
    Stack S;
    initStack(&S);
    push(&S, s);

    // 임시 스택
    Stack Temp;
    initStack(&Temp);

    while(!isStackEmpty(&S)){
        char here = peekOrPop(G, &S);

        Vertex* p = findVertex(G, here);

        if(p->isVisit == FALSE){
            p->isVisit = TRUE;
            printf("[%c] ", p->vName);
        }

        // stack은 LIFO방식이므로 우선순위가 낮은 지점부터 투입해야 하는데, AdjVertex는 우선순위가 높은 지점부터 저장되는 단순연결(단방향)형태이므로 Temp 스택을 사용해 S 스택에 저장
        for(AdjVertex* a = p->aHead; a != NULL; a = a->next){
            Vertex* b = findVertex(G, a->aName);
            if(!(b->isVisit))
                push(&Temp, a->aName);
        }
        while(!isStackEmpty(&Temp))
            push(&S, pop(&Temp));
    }
}

void BFS(GraphType* G, char s){
    // BFS는 DFS를 실행한 후 바로 실행할 것이므로 isVisit 초기화
    for(Vertex* p = G->vHead; p != NULL; p = p->next)
        p->isVisit = 0;

    Queue Q;
    initQueue(&Q);
    enqueue(&Q, s);

    while(!isQueueEmpty(&Q)){
        char here = dequeue(&Q);

        Vertex* p = findVertex(G, here);

        if(p->isVisit == FALSE){
            p->isVisit = TRUE;
            printf("[%c] ", p->vName);
        }

        for(AdjVertex* a = p->aHead; a != NULL; a = a->next){
            Vertex* b = findVertex(G, a->aName);
            if(!(b->isVisit))
                enqueue(&Q, a->aName);
        }
    }
}

int main(){
    
    GraphType G;
    initGraph(&G);

    makeVertex(&G, 'A'); makeVertex(&G, 'B');
    makeVertex(&G, 'C'); makeVertex(&G, 'D');
    makeVertex(&G, 'E'); makeVertex(&G, 'F');
    makeVertex(&G, 'G'); makeVertex(&G, 'H');

    insertEdge(&G, 'A', 'B'); insertEdge(&G, 'A', 'C');
    insertEdge(&G, 'B', 'D'); insertEdge(&G, 'C', 'D');
    insertEdge(&G, 'C', 'E'); insertEdge(&G, 'D', 'F');
    insertEdge(&G, 'E', 'G'); insertEdge(&G, 'E', 'H');
    insertEdge(&G, 'G', 'H');

    print(&G); printf("\n");

    DFS(&G, 'A'); printf("\n");
    BFS(&G, 'A'); printf("\n");

    return 0;
}