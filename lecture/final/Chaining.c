#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 13

typedef struct HashType
{
	int key;
	struct HashType* next ;
}HashType;

void init(HashType* HT)
{
	for (int i = 0; i < M; i++)
	{
		HT[i].key = 0;
		HT[i].next = NULL;
	}
}

int hashFn(int key)
{
    return key % M;
} 

void insertItem(HashType* HT, int key)
{
    int b = hashFn(key);
    HashType* node = (HashType*)malloc(sizeof(HashType));
	node->key = key;
	node->next = HT[b].next;
	HT[b].next = node;
}

int findItem(HashType* HT, int key)
{
	int b = hashFn(key);
	int count = 0;
	HashType* p;
	for (p = HT[b].next; p != NULL; p = p->next)
		if (p->key == key)
			count++;
	return count;
}

int deleteItem(HashType* HT, int key)
{
	int b = hashFn(key);
	int count = 0;
	HashType* p = &HT[b];
	HashType* q;

	while (p->next)
	{
		if (p->next->key == key)
		{
			count++;
			q = p->next;
			p->next = q->next;
			free(q);
		}
		else
			p = p->next;
	}
	return count;
}

void printHash(HashType* HT)
{
	HashType* p;
	for (int i = 0; i < M; i++)
	{
		printf("HT[%02d] : ", i);
		for (p = HT[i].next; p != NULL; p = p->next)
			printf("[%d] ", p->key);
		printf("\n");
	}
}

int main()
{
	HashType HT[M];
	int key;
	init(HT);
	
	srand(time(NULL));
	
	for (int i = 0; i < 20; i++)
		insertItem(HT, rand() % 90 + 10);
	printHash(HT);
	
	printf("\nInput search key : ");
	scanf("%d", &key);
	printf("There are %d %d.\n", findItem(HT, key), key);
	
	printf("\nInput delete key : ");
	scanf("%d", &key);
	printf("%d %d deleted.\n\n", deleteItem(HT, key), key);
	printHash(HT);
}




