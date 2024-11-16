#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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

void rDFS(GraphType* G, char vName){
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

    rDFS(&G, 'B'); printf("\n");

    return 0;
}