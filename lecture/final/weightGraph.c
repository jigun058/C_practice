#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Edge{
    char v1, v2;
    int weight;
    struct Edge* next;
}Edge;

typedef struct AdjVertex{
    char aName;
    Edge* e;
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
    Edge* eHead;
    int vCount, eCount;
}GraphType;

void initGraph(GraphType* G){
    G->vHead = NULL;
    G->eHead = NULL;
    G->vCount = G->eCount = 0;
}

void makeVertex(GraphType* G, char vName){
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisited = FALSE;
    v->aHead = NULL;
    v->next = NULL;

    G->vCount++;    // 정점의 개수 증가

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

void makeAdjVertex(Vertex* v, char aName, Edge* e){
    AdjVertex* a = (AdjVertex*)malloc(sizeof(AdjVertex));
    a->aName = aName;
    a->e = e;
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

void insertEdge(GraphType* G, char v1, char v2, int weight){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->weight = weight;
    e->next = NULL;

    G->eCount++;

    Edge* p = G->eHead;
    
    if(p == NULL)
        G->eHead = e;
    else{
        while(p->next != NULL)
            p = p->next;
        
        p->next = e;
    }
    
    Vertex* v = findVertex(G, v1);
    makeAdjVertex(v, v2, e);

    v = findVertex(G, v2);
    makeAdjVertex(v, v1, e);
}

void print(GraphType* G){
    for(Vertex* p = G->vHead; p != NULL; p = p->next){
        printf("[%c] : ", p->vName);
        for(AdjVertex* q = p->aHead; q != NULL; q = q->next)
            printf("[%c, %d]", q->aName, q->e->weight);
        printf("\n");
    }
}

int main(){
    GraphType G;
    initGraph(&G);

    makeVertex(&G, 'A'); makeVertex(&G, 'B');
    makeVertex(&G, 'C'); makeVertex(&G, 'D');
    makeVertex(&G, 'E'); makeVertex(&G, 'F');
    makeVertex(&G, 'G');

    insertEdge(&G, 'A', 'B', 25); insertEdge(&G, 'A', 'D', 12);
    insertEdge(&G, 'B', 'C', 10); insertEdge(&G, 'B', 'E', 15);
    insertEdge(&G, 'C', 'G', 16); insertEdge(&G, 'D', 'E', 17);
    insertEdge(&G, 'D', 'F', 37); insertEdge(&G, 'E', 'F', 19);
    insertEdge(&G, 'E', 'G', 14); insertEdge(&G, 'F', 'G', 42);

    print(&G); printf("\n");
    
    return 0;
}// 다른 더 좋은 방식이 있을 것