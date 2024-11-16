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
int isVisit[N];

typedef struct {
    int vSize;
    int adjMat[N][N];
}GraphType;

void initGraph(GraphType* G){
    G->vSize = 0;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N ; j++){
            G->adjMat[i][j] = 0;
        }
    }
}

void setVertexCount(GraphType* G, int n){
    G->vSize = n;
}

void insertEdge(GraphType* G, int u, int v){
    if(u < G->vSize && v < G->vSize){
        G->adjMat[u][v] = G->adjMat[v][u] = 1;
    }
}

int degree(GraphType* G, int v){
    int count = 0;
    for(int i = 0 ; i < G->vSize ; i++){
        if(G->adjMat[v][i] == 1){
            count++;
        }
    }

    return count;
}

// 현재 지점에서 탐색 가능한 인접 정점이 두 개 이상인 경우는 peek, 한 개 이하인 경우는 pop을 통해 다음 지점 반환
int peekOrPop(GraphType* G, Stack* S){
    int s = peek(S);

    int count = 0;
    for(int i=0; i<(G->vSize); i++){
        if(G->adjMat[s][i] == 1 && !isVisit[i])
            count += 1;
    }

    if(count >= 2)
        return peek(S);
    else
        return pop(S);
}

void print(GraphType* G){
    for(int i = 0 ; i < G->vSize ; i++){
        printf(" %c(%d) | ", vName[i], degree(G, i));
        for(int j = 0 ; j < G->vSize ; j++){
            printf(" %d", G->adjMat[i][j]);
        }

        printf("\n");
    }
}

// void rDFS(GraphType* G, int s){
//     isVisit[s] = TRUE;
//     printf("[%c] ", vName[s]);

//     for(int t = 0 ; t < G->vSize ; t++){
//         if(G->adjMat[s][t] == 1 && isVisit[t] == FALSE){
//             rDFS(G, t);
//         }
//     }
// }

void DFS(GraphType* G, int s){
    Stack S;
    initStack(&S);
    push(&S, s);

    while(!isStackEmpty(&S)){
        int here = peekOrPop(G, &S);

        if(isVisit[here] == FALSE){
            isVisit[here] = TRUE;
            printf("[%c] ", vName[here]);
        }

        for(int j = (G->vSize)-1; j >= 0; j--){   //stack은 LIFO방식이므로 우선순위가 낮은 지점부터 투입
            if(G->adjMat[here][j] == 1 && !isVisit[j])
                push(&S, j);
        }
    }
}

void BFS(GraphType* G, int s){
    isVisit[s] = TRUE;
    printf("[%c] ", vName[s]);
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


    printf("DFS : "); DFS(&G, 0);
    //printf("BFS : "); BFS(&G, 0);

    return 0;
}