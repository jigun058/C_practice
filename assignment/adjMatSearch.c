#include <stdio.h>
#include <stdlib.h>

#define N 10
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

// void rDFS(GrapeType* G, int s){
//     visited[s] = TRUE;
//     printf("[%c] ", vName[s]);

//     for(int t = 0 ; t < G->vSize ; t++){
//         if(G->adjMat[s][t] == 1 && visited[t] == FALSE){
//             rDFS(G, t);
//         }
//     }
// }

void DFS(GrapeType* G, int s){
    visited[s] = TRUE;
    printf("[%c] ", vName[s]);

}

void BFS(GrapeType* G, int s){
    visited[s] = TRUE;
    printf("[%c] ", vName[s]);
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


    printf("DFS : "); DFS(&G, 0);
    printf("BFS : "); BFS(&G, 0);

    return 0;
}