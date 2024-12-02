#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUCKETS 10
#define DIGITS 4

typedef struct
{
    int data[BUCKETS];
    int front, rear;
}QueueType;

void init(QueueType* Q)
{
    Q->front = Q->rear = 0;
}

int isEmpty(QueueType* Q)
{
	return Q->front == Q->rear;
}

int isFull(QueueType* Q)
{
	return ((Q->rear + 1) % BUCKETS == Q->front);
}

void enqueue(QueueType* Q, int item)
{
	if (isFull(Q))
		printf("Full\n");
	else
	{
	    Q->rear = (Q->rear + 1) % BUCKETS;
	    Q->data[Q->rear] = item;
	}
}

int dequeue(QueueType* Q)
{
	if (isEmpty(Q))
	{
		printf("Empty\n");
		return -1;
	}
	
	Q->front = (Q->front + 1) % BUCKETS;
	return Q->data[Q->front];
}

void radixSort(int A[], int n)
{
    int factor = 1;
	QueueType Q[BUCKETS];

	for (int b = 0; b < BUCKETS; b++) 
	    init(&Q[b]);  

	for (int d = 0; d < DIGITS; d++) 
	{
		for (int i = 0; i < n; i++)			
			enqueue(&Q[(A[i] / factor) % 10], A[i]);

		for (int b = 0, i = 0; b < BUCKETS; b++)  
			while (!isEmpty(&Q[b]))
				A[i++] = dequeue(&Q[b]);

        printf("%4d의 자리 정렬 : ", factor);
        for (int i = 0; i < 15; i++)
		    printf("%d ", A[i]);
	    printf("\n");        
		factor *= 10;					
	}
}

int main()
{
    int A[15];
    srand(time(NULL));
    for(int i = 0; i < 15; i++)
        A[i] = rand() % 9999 + 1;
    
    for (int i = 0; i < 15; i++)
		printf("%d ", A[i]);
	printf("\n\n");

    radixSort(A, 15);


}