#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//////////////////////스택과 큐//////////////////////
typedef struct SimpNode{
    struct SimpNode* next;
    int data;
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

int pop(Stack* S){
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

int dequeue(Queue* Q){
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

int peek(Stack* S){
    if(isStackEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    return S->top->data;
}

int peekFront(Queue* Q){
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
    int isVisited;
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
    v->isVisited = FALSE;
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

void print(GraphType* G){
    for(Vertex* p = G->vHead; p != NULL; p = p->next){
        printf("[%c] : ", p->vName);
        for(AdjVertex* q = p->aHead; q != NULL; q = q->next)
            printf("[%c]", q->aName);
        printf("\n");
    }
}

void DFS(GraphType* G, char vName){
    Vertex* v = findVertex(G, vName);
    AdjVertex* a = NULL;
    if(v->isVisited == FALSE){
        v->isVisited = TRUE;
        printf("[%c] ", v->vName);
    }

    for(a = v->aHead; a != NULL; a = a->next){
        v = findVertex(G, a->aName);
        if(v->isVisited == FALSE)
            rDFS(G, v->vName);
    }
}

void BFS(GraphType* G, char vName){
    Vertex* v = findVertex(G, vName);
    AdjVertex* a = NULL;
    if(v->isVisited == FALSE){
        v->isVisited = TRUE;
        printf("[%c] ", v->vName);
    }

    for(a = v->aHead; a != NULL; a = a->next){
        v = findVertex(G, a->aName);
        if(v->isVisited == FALSE)
            rDFS(G, v->vName);
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

    DFS(&G, 'B'); printf("\n");
    BFS(&G, 'B'); printf("\n");

    return 0;
}