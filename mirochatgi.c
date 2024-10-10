#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#include <unistd.h>

#define N 100
#define M 6

// char map[M][M] = {
//     {'1','1','1','1','1','1'},
//     {'0','0','1','0','0','1'},
//     {'1','0','0','0','1','1'},
//     {'1','0','1','0','1','1'},
//     {'1','0','1','0','0','x'},
//     {'1','1','1','1','1','1'}
// };

char map[M][M] = {
    {'1','1','1','1','1','1'},
    {'0','0','0','0','0','1'},
    {'1','0','1','0','1','1'},
    {'1','1','1','0','0','x'},
    {'1','1','1','0','1','1'},
    {'1','1','1','1','1','1'}
};

typedef struct
{
    int r, c;
}Coor;

typedef Coor element;

typedef struct Deque
{
    int front;
    int rear;

    element data[N];
}Deque;

void init(Deque *S)
{
	S -> front = 0;
    S -> rear = 0;
}	

int isEmpty(Deque *S)
{
    return (S -> rear) == (S -> front);
}

int isFull(Deque *S)
{
    return (((S -> rear) + 1)%N) == ((S -> front)%N);
}

void addFront(Deque *S, element e)
{
    if (isFull(S))
    {
		printf("오버플로우\n");
        exit(EXIT_FAILURE);
    }
    else if (isEmpty(S))
    {
        S -> data[S -> front] = e;
    }
    else
    {
        S -> front = (S->front - 1 + N) % N;
        S -> data[S -> front] = e;
    }
}

void addRear(Deque *S, element e)
{
    if (isFull(S))
    {
		printf("오버플로우\n");
        exit(EXIT_FAILURE);
    }
    else if (isEmpty(S))
    {
        S -> data[S -> rear] = e;
    }
    else
    {
        S -> rear = (S->rear + 1) % N;
        S -> data[S -> rear] = e;
    }
}

element deleteFront(Deque *S)
{
    if (isEmpty(S))
    {
		printf("언더플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int foll = S -> front;
        S -> front = (S->front + 1) % N;
        return S -> data[foll];
    }
}

element deleteRear(Deque *S)
{
    if (isEmpty(S))
    {
		printf("언더플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int prev = S -> rear;
        S -> rear = (S->rear - 1 + N) % N;
        return S -> data[prev];
    }
}

