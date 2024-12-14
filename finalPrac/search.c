#include <stdio.h>
#include <stdlib.h>

#define N 9
#define M 13

void sequentialSearch(int A[], int num) {
    for (int i = 0; i < N; i++) {
        if (A[i] == num) {
            printf("%d found\n", num);
            return;
        }
        else if (i == N-1) {
            printf("%d not found\n", num);
            return;
        }
    }
}

void binarySearch(int A[], int num, int left, int right) {
    int mid = (left + right) / 2;

    if (left > right) {
        printf("%d not found\n", num);
        return;
    }
    if (A[mid] == num) {
        printf("%d found\n", num);
        return;
    }
    else if(A[mid] > num) {
        binarySearch(A, num, left, mid-1);
    }
    else {
        binarySearch(A, num, mid+1, right);
    }
}

typedef struct Bucket {
    int key;
    int probeCount;
} Bucket;

typedef struct HashTable {
    Bucket B[M];
} HashTable;

void init(HashTable* HT) {
    for (int i = 0; i < M; i++) {
        HT->B[i].key = 0;
        HT->B[i].probeCount = 0;
    }
}

int isEmpty(HashTable* HT, int b) {
    return HT->B[b].key == 0;
}

int hashFn1(int key) {
    return key % M;
}

int hashFn2(int key) {
    return 11 - (key % 11);
}

void insertItem(HashTable* HT, int key) {
    int hashVal = hashFn1(key);
    int count = 0;

    for (int i = 0; i < M; i++) {
        count++;
        int b = (hashVal + i) % M;      //선형 조사법
        //int b = (hashVal + i*i) % M;  //이차 조사법
        //int b = (hashVal + i * hashFn2(key)) % M;   //이중 해싱법

        if (isEmpty(HT, b)) {
            HT->B[b].key = key;
            HT->B[b].probeCount = count;
            return;
        }
    }
}

int findItem(HashTable* HT, int key) {
    int hashVal = hashFn1(key);

    for (int i = 0; i < M; i++) {
        int b = (hashVal + i) % M;

        if (isEmpty(HT, b)) {
            return -1;
        }
        if (HT->B[b].key == key) {
            return b;
        }
    }

    return -1;
}

int deleteItem(HashTable* HT, int key) {
    int hashVal = hashFn1(key);

    for (int i = 0; i < M; i++) {
        int b = (hashVal + i) % M;

        if (isEmpty(HT, b)) {
            return -1;
        }
        if (HT->B[b].key == key) {
            HT->B[b].key = -1;
            HT->B[b].probeCount = 0;
            return key;
        }
    }

    return -1;
}

void print(HashTable* HT) {
    for(int i = 0; i < M; i++)
        printf(" %2d", HT->B[i].key);
    printf("\n");
}

void printHash(HashTable* HT) {
    printf("Bucket   key  Probe\n");
    printf("===================\n");

    for(int i = 0; i < M; i++)
        printf("HT[%02d] :  %2d   %4d\n", i, HT->B[i].key, HT->B[i].probeCount);
    printf("\n");
}

int main() {

    HashTable HT;
    init(&HT);

    int data[] = {25, 13, 16, 15, 7, 28, 31, 20, 1, 38};

    printf(" h(key)     0  1  2  3  4  5  6  7  8  9 10 11 12\n");
    printf("========   ======================================\n");

    for(int i = 0; i < 10; i++) {
        printf("h(%2d):%2d  ", data[i], hashFn1(data[i]));
        insertItem(&HT, data[i]);
        print(&HT);
    }

    printf("\n");
    printHash(&HT);

    int key;

    printf("\nInput Search Key : ");
    scanf("%d", &key);
    if(findItem(&HT, key) != -1)
        printf("%d exists.\n", key);
    else
        printf("%d not exists.\n", key);

    printf("\nInput Delete Key : ");
    scanf("%d", &key);
    if(deleteItem(&HT, key) != -1)
        printf("%d is deleted.\n", key);
    else
        printf("%d not exists.\n", key);

    printHash(&HT);

    printf("\nInput Search Key : ");
    scanf("%d", &key);
    if(findItem(&HT, key) != -1)
        printf("%d exists.\n", key);
    else
        printf("%d not exists.\n", key);

    return 0;
}