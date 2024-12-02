#include <stdio.h>
#include <stdlib.h>

#define N 10
#define TRUE 1
#define FALSE 0

char vName[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' , 'J'};
int visited[N];

typedef struct {
    int vSize;

    int adjMat[N][N];
}GrapeType;

void initGraph(GrapeType* G){
    G->vSize = 0;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N ; j++){
            G->adjMat[i][j] = 0;
        }
    }
}

void setVertexCount(GrapeType* G, int n){
    G->vSize = n;
}

void insertEdge(GrapeType* G, int u, int v){
    if(u < G->vSize && v < G->vSize){
        G->adjMat[u][v] = G->adjMat[v][u] = 1;
    }
}

int degree(GrapeType* G, int v){
    int count = 0;
    for(int i = 0 ; i < G->vSize ; i++){
        if(G->adjMat[v][i] == 1){
            count++;
        }
    }

    return count;
}

void print(GrapeType* G){
    for(int i = 0 ; i < G->vSize ; i++){
        printf(" %c(%d) | ", vName[i], degree(G, i));
        for(int j = 0 ; j < G->vSize ; j++){
            printf(" %d", G->adjMat[i][j]);
        }

        printf("\n");
    }
}

void rDFS(GrapeType* G, int s){
    visited[s] = TRUE;
    printf("[%c] ", vName[s]);

    for(int t = 0 ; t < G->vSize ; t++){
        if(G->adjMat[s][t] == 1 && visited[t] == FALSE){
            rDFS(G, t);
        }
    }
}

int main(){
    
    GrapeType G;
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