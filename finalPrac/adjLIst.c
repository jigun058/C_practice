#include <stdio.h>
#include <stdlib.h>

typedef struct AdjVertex {
    char aName;
    struct AdjVertex* next;
}AdjVertex;

typedef struct Vertex {
    char vName;
    int isVisited;
    AdjVertex* aHead;
    struct Vertex* next;
}Vertex;

typedef struct GraphType {
    Vertex* vHead;
} GraphType;

void initGraph(GraphType* G) {
    G->vHead = NULL;
}

void makeVertex(GraphType* G, char vName) {
    Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    node->vName = vName;
    node->next = NULL;
    node->isVisited = 0;
    node->aHead = NULL;
    
    Vertex* p = G->vHead;

    if (p == NULL) {
        G->vHead = node;
    }
    else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = node;
    }
}

Vertex* findVertex(GraphType* G, char vName) {
    Vertex* p = G->vHead;

    while (p->vName != vName && p != NULL) {
        p = p->next;
    }

    if (p == NULL) {
        printf("해당 노드가 없습니다.\n");
        return p;
    } else {
        return p;
    }
}

void makeAdjVertex(Vertex* v, char aName) {
    AdjVertex* node = (AdjVertex*)malloc(sizeof(AdjVertex));
    node->aName = aName;
    node->next = NULL;

    AdjVertex* p = v->aHead;

    if (p == NULL) {
        v->aHead = node;
        return;
    }
    else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = node;
    }
}

void insertEdge(GraphType* G, char from, char to) {
    Vertex* p = findVertex(G, from);
    makeAdjVertex(p, to);
    
    Vertex* rp = findㅊVertex(G, to);
    makeAdjVertex(rp, from);
}

void print(GraphType* G) {
    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        printf("[%c] : ", p->vName);
        for (AdjVertex* a = p->aHead; a != NULL; a = a->next) {
            printf("[%c]", a->aName);
        }
        printf("\n");
    }
}

void rDFS(GraphType* G, char start) {
    Vertex* p = findVertex(G, start);

    if (p->isVisited == 1) {
        return;
    }

    p->isVisited = 1;
    printf("[%c] ", p->vName);

    for (AdjVertex* a = p->aHead; a != NULL; a = a->next) {
        Vertex* pNext = findVertex(G, a->aName);
        if (pNext != NULL && pNext->isVisited == 0) {
            rDFS(G, a->aName);
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

    rDFS(&G, 'B'); printf("\n");

    return 0;
}