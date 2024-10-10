#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
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

// 원형 덱을 사용
// front가 가리키는 곳 : 맨 앞의 요소의 위치
// rear가 가리키는 곳 : 맨 뒤의 요소의 한 칸 더 뒤 
void init(Deque *S)
{
	S->front = 0;
    S->rear = 0;
}	

// 비어있는지 확인하는 함수
// 비어있는 상태에서는 front와 rear의 위치가 같음
int isEmpty(Deque *S)
{
    return (S->rear) == (S->front);
}

// 100칸 중 99칸 차있는지 확인하는 함수(100칸 중 값이 100칸을 다 차지하게되면 Empty인 경우와 구별이 안 돼 99칸으로 제한)
int isFull(Deque *S)
{
    return (((S->rear) + 1)%N) == (S->front);
}

// front쪽으로 값을 넣는 함수
void addFront(Deque *S, element e)
{
    if (isFull(S))
    {
		printf("오버플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        S->front = (S->front - 1 + N) % N;
        S->data[S->front] = e;
    }
}

// rear쪽으로 값을 넣는 함수
void addRear(Deque *S, element e)
{
    if (isFull(S))
    {
		printf("오버플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
    S->data[S->rear] = e;
    S->rear = (S->rear + 1) % N;
    }
}

// front의 요소를 반환하고 (논리적)삭제하는 함수
element deleteFront(Deque *S)
{
    if (isEmpty(S))
    {
		printf("언더플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        element temp = S->data[S->front];
        S->front = (S->front + 1) % N;
        return temp;
    }
}

// rear의 요소를 반환하고 (논리적)삭제하는 함수
element deleteRear(Deque *S)
{
    if (isEmpty(S))
    {
		printf("언더플로우\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        S->rear = (S->rear - 1 + N) % N;
        return S->data[S->rear];
    }
}



int main()
{
    Deque D;
    init(&D);

    


    return 0;
}