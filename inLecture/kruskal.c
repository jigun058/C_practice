#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1
#define FALSE 0
#define INF 1410065407

int dist[N];
int vertices[N];

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
    int isVisit;
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

void initDist(GraphType* G) {
    for (int i = 0; i < 26; i++){
        dist[i] = INF;
        vertices[i] = -1;
    }
}

void makeVertex(GraphType* G, char vName){
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->vName = vName;
    v->isVisit = FALSE;
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

Vertex* findMin(GraphType* G){
    Vertex* v = NULL;
    int min = INF;

    for(Vertex* p = G->vHead; p != NULL; p = p->next){
        if(dist[p->vName - 65] < min && p->isVisit == FALSE){
            min = dist[p->vName - 65];
            v = p;
        }
    }
    
    return v;
}

void selectionSort(GraphType* G, Edge* edges[]){
    Edge* e = G->eHead;

    for(int i = 0; i < G->eCount; i++){
        edges[i] = e;
        e = e->next;
    }

    for(int i = 0; i < G->eCount - 1; i++){
        int min = i;

        for(int j = i + 1; j < G->eCount; j++)
            if(edges[j]->weight < edges[min]->weight)
                min = j;

        e = edges[min];
        edges[min] = edges[i];
        edges[i] = e;
    }

    for(int i = 0; i < G->eCount; i++)
        printf("[%c%c%d] ", edges[i]->v1, edges[i]->v2, edges[i]->weight);
    printf("\n\n");
}

void prim(GraphType* G, char vName){
    Vertex* v = NULL;
    AdjVertex* a = NULL;

    dist[vName - 65] = 0;

    for(int i=0; i < G->vCount; i++){
        for(int i=0; i < G->vCount; i++)
            printf("%3d ", dist[i]);
        printf("\n");

        v = findMin(G);
        v->isVisit = TRUE;
        //printf("[%c(%d)] ", v->vName, dist[v->vName - 65]);

        for(a = v->aHead; a != NULL; a = a->next){
            Vertex* w = findVertex(G, a->aName);
            if(w->isVisit == FALSE && a->e->weight < dist[a->aName - 65])
                dist[a->aName - 65] = a->e->weight;
        }
    }
}

int Find(int vNum){
    if(vertices[vNum] == -1)
        return vNum;

    while(vertices[vNum] != -1)
        vNum = vertices[vNum];

    return vNum;
}

void Union(int vNum1, int vNum2){
    vertices[vNum2] = vNum1;
}

void kruskal(GraphType* G, Edge* edges[]){
    int eCnt = 0, i = 1;

    int vNum1, vNum2;
    Edge* e;

    while(eCnt < G->vCount - 1){
        e = edges[i];

        vNum1 = Find(e->v1 - 65);
        vNum2 = Find(e->v1 - 65);

        if(vNum1 != vNum2){
            printf("%d. [%c%c%d]", eCnt + 1, e->v1, e->v2, e->weight);
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

    Edge* edges[N];
    selectionSort(&G, edges);

    kruskal(&G, edges);

    //print(&G); printf("\n");

    //prim(&G, 'A');
    
    return 0;
}