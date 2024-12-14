#include <stdio.h>
#include <stdlib.h>

#define N 26
#define inf 100

int dist[N];
int vertices[N];

typedef struct Edge {
    char v1, v2;
    int weight;
    struct Edge* next;
} Edge;

typedef struct AdjVertex {
    char aName;
    Edge* e;
    struct AdjVertex* next;
} AdjVertex;

typedef struct Vertex {
    char vName;
    int isVisited;
    AdjVertex* aHead;
    struct Vertex* next;
} Vertex;

typedef struct GraphType {
    Vertex* vHead;
    Edge* eHead;
    int vCount, eCount;
} GraphType;

void initGraph(GraphType* G) {
    G->vHead = NULL;
    G->eHead = NULL;
    G->eCount = G->vCount = 0;
}

void initDist(int dist[]) {
    for (int i = 0; i < N; i++) {
        dist[i] = inf;
    }
}

void makeVertex(GraphType* G, char vName) {
    Vertex* node = (Vertex*)malloc(sizeof(Vertex));
    node->vName = vName;
    node->next = NULL;
    node->isVisited = 0;
    node->aHead = NULL;

    G->vCount += 1;
    
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

void makeAdjVertex(Vertex* v, char aName, Edge* e) {
    AdjVertex* node = (AdjVertex*)malloc(sizeof(AdjVertex));
    node->aName = aName;
    node->next = NULL;
    node->e = e;

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

void insertEdge(GraphType* G, char from, char to, int weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));

    e->next = NULL;
    e->v1 = from;
    e->v2 = to;
    e->weight = weight;

    G->eCount += 1;

    Edge* ep = G->eHead;

    if (ep == NULL) {
        G->eHead = e;
    }
    else {
        while (ep->next != NULL) {
            ep = ep->next;
        }
        ep->next = e;
    }

    Vertex* p = findVertex(G, from);
    makeAdjVertex(p, to, e);
    
    Vertex* rp = findVertex(G, to);
    makeAdjVertex(rp, from, e);
}

void print(GraphType* G) {
    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        printf("[%c] : ", p->vName);
        for (AdjVertex* a = p->aHead; a != NULL; a = a->next) {
            printf("[%c, %d]", a->aName, a->e->weight);
        }
        printf("\n");
    }
}

Vertex* findMin(GraphType* G) {
    Vertex* v = NULL;
    int min = inf;

    for (Vertex* p = G->vHead; p != NULL; p = p->next) {
        if (p->isVisited == 0 && dist[p->vName - 65] < min) {
            min = dist[p->vName - 65];
            v = p;
        }
    }

    return v;
}

void prim(GraphType* G, char start) {
    initDist(dist);

    Vertex* v = NULL;
    AdjVertex* a = NULL;
    dist[start-65] = 0;

    for (int i=0; i < G->vCount; i++) {
        v = findMin(G);
        v->isVisited = 1;

        for(int i=0; i < G->vCount; i++)
            printf("%3d ", dist[i]);
        printf("\n");

        for(a = v->aHead; a != NULL; a = a->next) {
            Vertex* w = findVertex(G, a->aName);
            if (w->isVisited == 0 && a->e->weight < dist[a->aName - 65]) {
                dist[a->aName - 65] = a->e->weight;
            }
        }
    }
}

void selectionSort(GraphType* G, Edge* edges[]) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e = G->eHead;

    for (int i = 0; i < G->eCount; i++) {
        edges[i] = e;
        e = e->next;
    }

    for (int i = 0; i < G->eCount-1; i++) {
        int min = i;

        for (int j = i+1 ; j < G->eCount; j++) {
            if (edges[j]->weight < edges[min]->weight) {
                min = j;
            }
        }

        e = edges[i];
        edges[i] = edges[min];
        edges[min] = e;
    }

    for(int i = 0; i < G->eCount; i++)
        printf("[%c%c%d] ", edges[i]->v1, edges[i]->v2, edges[i]->weight);
    printf("\n\n");
}

int Find(int vNum) {
    if (vertices[vNum] == -1) {
        return vNum;
    }

    while (vertices[vNum] != -1) {
        vNum = vertices[vNum];
    }
    return vNum;
}

void Union(int vNum1, int vNum2) {
    vertices[vNum2] = vNum1;
}

void kruskal(GraphType* G, Edge* edges[]) {
    for (int i = 0; i < N; i++) {
        vertices[i] = -1;
    }

    Edge* e;
    int eCnt = 0;
    int i = 1;

    while (eCnt < G->vCount-1) {
        e = edges[i-1];
        
        int vNum1 = Find(e->v1 - 'A');
        int vNum2 = Find(e->v2 - 'A');

        if(vNum1 != vNum2) {
            printf("%d. [%c%c]\n", i, e->v1, e->v2);
            eCnt++;
            Union(vNum1, vNum2);
        }
        i++;
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

    //prim(&G, 'A');

    Edge* edges[N];
    selectionSort(&G, edges);
    kruskal(&G, edges);
    
    return 0;
}