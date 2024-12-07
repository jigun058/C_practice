#include <stdio.h>
#include <stdlib.h>

#define N 10

int vName[N];
int isVisited[N];

typedef struct {
    int vSize;
    int adjMat[N][N];
}GraphType;

void initGraph(GraphType* G) {
    G->vSize = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            G->adjMat[i][j] = 0;
        }
    }
}

void setVertexCount(GraphType* G, int n) {
    G->vSize = n;
}

void insertEdge(GraphType* G, int from, int to) {
    if(from < G->vSize && to < G->vSize) {
        G->adjMat[from][to] = 1;
        G->adjMat[to][from] = 1;    //무방향 그래프
    }
}

int degree(GraphType* G, int n) {
    int count = 0;
    for(int i = 0; i < G->vSize; i++) {
        if(G->adjMat[n][i] == 1) {
            count += 1;
        }
    }

    return count;
}

void print(GraphType* G) {
    for(int i = 0; i < G->vSize; i++) {
        for(int j = 0; j < G->vSize; j++) {
            printf("%d ", G->adjMat[i][j]);
        }
        printf("\n");
    }
}

void rDFS(GraphType* G, int start) {
    if (isVisited[start] == 1) {
        printf("출발지점이 잘못되었습니다.\n");
        return;
    }

    isVisited[start] = 1;
    printf("%d ", start);
    for(int i = 0; i < G->vSize; i++) {
        if(G->adjMat[start][i] == 1 && isVisited[i] == 0)
            rDFS(G, i);
    }
    
}

int main(){
    
    GraphType G;
    initGraph(&G);

    int n;
    printf("정점의 수 : ");
    scanf("%d", &n);
    printf("\n");

    setVertexCount(&G, n);

    insertEdge(&G, 0, 1);
    insertEdge(&G, 0, 2);
    insertEdge(&G, 1, 3);
    insertEdge(&G, 2, 3);
    insertEdge(&G, 2, 4);
    insertEdge(&G, 3, 5);
    insertEdge(&G, 4, 6);
    insertEdge(&G, 4, 7);
    insertEdge(&G, 6, 7);
    print(&G);
    printf("\n");


    printf("DFS : "); rDFS(&G, 0);

    return 0;
}