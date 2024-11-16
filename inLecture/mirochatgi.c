#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //macos에서 windows.h 대신 사용하는 헤더

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

// 덱 초기화(원형덱으로 구현)
// 데이터의 맨 앞의 값이 front 위치(큐의 나가는부분)
// 데이터의 맨 뒤의 값보다 한 칸 뒤가 rear 위치(스택의 나가는 부분, 데이터가 들어오는 부분)
void init(Deque *S)
{
    S->front = 0;
    S->rear = 0;
}   

// 덱이 비어있는지 확인하는 함수
int isEmpty(Deque *S)
{
    return (S->rear) == (S->front);
}

// 덱이 꽉 차있는지 확인하는 함수
// 값이 99개 들어가있는 상태가 꽉 차있는 상태(100개가 들어가있으면 특별한 처리 없이는 Empty인 상태와 구별할 수 없음)
int isFull(Deque *S)
{
    return (((S->rear) + 1)%N) == (S->front);
}

// rear에 요소 추가(값은 항상 Rear로 넣도록 함)
void addRear(Deque *S, element e)
{
    if (isFull(S))
    {
        printf("오버플로우\n");
    }
    S->data[S->rear] = e;
    S->rear = (S->rear + 1) % N;
}

// front에서 요소 제거 및 반환(dequeue)
element deleteFront(Deque *S)
{
    if (isEmpty(S))
    {
        printf("언더플로우\n");
    }
    element temp = S->data[S->front];
    S->front = (S->front + 1) % N;
    return temp;
}

// rear에서 요소 제거 및 반환(pop)
element deleteRear(Deque *S)
{
    if (isEmpty(S))
    {
        printf("언더플로우\n");
    }
    S->rear = (S->rear - 1 + N) % N;
    return S->data[S->rear];
}

// front의 요소를 확인하는 함수(큐의 peek)
element peekFront(Deque *S)
{
    return S->data[S->front];
}

// rear의 요소를 확인하는 함수(스택의 peek)
element peekRear(Deque *S)
{
    return S->data[S->rear];
}

// 맵을 출력하는 함수
void printMap(char map[M][M], element here) {
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == here.r && j == here.c)
                printf("@ ");  // 쥐의 위치는 @로 표시
            else
                printf("%c ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    usleep(500000);  // 0.5초 지연
}

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 상, 하, 좌, 우 순서 -> DFS에서는 스택에 집어넣는 순서이므로, pop을 통한 실제 이동은 반대 순서가 됨.

// 스택을 이용한 DFS(덱의 Rear을 top으로 간주)
void DFS(Deque *S, int startRow, int startCol)
{
    // 인자로 받은 startRow, startCol 값을 element 요소로 변환해 저장, 스택에 push
    element start = {startRow, startCol};
    addRear(S, start);

    // 연결된 모든 경로를 탐색하기 전까지 동작
    while (!isEmpty(S))
    {
        element here = deleteRear(S);   // 스택의 맨 위 요소를 pop해 현재 위치를 담는 element형 변수에 저장(이동하는 로직)

        // 현재 위치에 x가 있을 경우 성공, 함수를 끝냄
        if (map[here.r][here.c] == 'x')
        {
            printf("찍찍(치즈 맛있다!)\n");
            return;
        }

        map[here.r][here.c] = '.';  // 방문한 곳은 "."으로 바꿈

        printMap(map, here);    // 맵 출력

        for (int i = 0; i < 4; i++)
        {
            // 한 칸 이동한 새로운 좌표를 저장
            int newRow = here.r + directions[i][0];
            int newCol = here.c + directions[i][1];

            // 맵 안에 있어야 하고, 0 위에 있거나 x 위에 있어야 함. -> next 요소로 저장한 뒤 스택에 push
            if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < M && (map[newRow][newCol] == '0' || map[newRow][newCol] == 'x'))
            {
                element next = {newRow, newCol};
                addRear(S, next);   // 스택에 추가만 할 뿐이지 이동은 아직 하지 않음. 상하좌우를 모두 살핀 뒤 갈 수 있는 곳은 상 하 좌 우 순서대로 스택에 저장
            }
        }
    }

    printf("길을 찾을 수 없습니다\n");  // isEmpty가 True가 되어서 x를 찾기 전에 반복문을 빠져나오게 되면 연결된 길이 없는 것
    return;
}

// 큐를 이용한 BFS(덱의 rear은 rear, front는 front 그대로 사용)
void BFS(Deque *S, int startRow, int startCol)
{
    // 인자로 받은 startRow, startCol 값을 element 요소로 변환해 저장, 큐에 enqueue
    element start = {startRow, startCol};
    addRear(S, start);

    // 연결된 모든 경로를 탐색하기 전까지 동작
    while (!isEmpty(S))
    {
        element here = deleteFront(S);   // 큐의 맨 앞 요소를 dequeue해 현재 위치를 담는 element형 변수에 저장(이동하는 로직)

        // 현재 위치에 x가 있을 경우 성공, 함수를 끝냄
        if (map[here.r][here.c] == 'x')
        {
            printf("찍찍(치즈 맛있다!)\n");
            return;
        }

        map[here.r][here.c] = '.';  // 방문한 곳은 "."으로 바꿈

        printMap(map, here);    // 맵 출력

        for (int i = 0; i < 4; i++)
        {
            // 한 칸 이동한 새로운 좌표를 저장
            int newRow = here.r + directions[i][0];
            int newCol = here.c + directions[i][1];

            // 맵 안에 있어야 하고, 0 위에 있거나 x 위에 있어야 함. -> next 요소로 저장한 뒤 큐에 enqueue
            if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < M && (map[newRow][newCol] == '0' || map[newRow][newCol] == 'x'))
            {
                element next = {newRow, newCol};
                addRear(S, next);   // 큐에 추가만 할 뿐이지 이동은 아직 하지 않음. 상하좌우를 모두 살핀 뒤 갈 수 있는 곳은 상 하 좌 우 순서대로 큐에 저장
            }
        }
    }

    printf("길을 찾을 수 없습니다\n");  // isEmpty가 True가 되어서 x를 찾기 전에 반복문을 빠져나오게 되면 연결된 길이 없는 것
    return;
}

int main()
{
    // 덱 D를 선언하고 초기화
    Deque D;
    init(&D);

    // 시작 좌표 설정
    int startRow = 1;
    int startCol = 0;

    //둘 중 하나 선택
    //DFS(&D, startRow, startCol);
    BFS(&D, startRow, startCol);

    usleep(5000000);  // 5초 지연 후 종료
    return 0;
}