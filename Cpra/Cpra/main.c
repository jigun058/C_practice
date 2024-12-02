#include <stdio.h>
#include <stdlib.h>

#define M 13

typedef struct {
    int key;
    int probeCount;
} Bucket;

typedef struct {
    Bucket B[M];
} HashTable;

void init(HashTable* HT) {
    for(int i = 0; i < M; i++) {
        HT->B[i].key = 0;
        HT->B[i].probeCount = 0;
    }
}

int isEmpty(HashTable* HT, int b) {
    return HT->B[b].key == 0;
}

int hashFn(int key) {
    return key % M;
}

int hashFn2(int key) {
    return 11 - (key % 11);  //M보다 작은 최대의 소수(11)가 가장 적합하다고 알려짐.
}

void insertItem(HashTable* HT, int key) {
    int hashVal = hashFn(key);
    int count = 0;

    for(int i = 0; i < M; i++) {
        count++;
        int b = (hashVal + i) % M;    //선형 조사법
        //int b = (hashVal + i*i) % M;  //이차 조사법
        //int b = (hashVal + i * hashFn2(key)) % M;   //이중 해싱법 (최적!!)

        if(isEmpty(HT, b)) {
            HT->B[b].key = key;
            HT->B[b].probeCount = count;
            return;
        }
    }
}

int findItem(HashTable* HT, int key) {
    int hashVal = hashFn(key);

    for(int i = 0; i < M; i++) {
        int b = (hashVal + i) % M;                      //** insert와 같은 방식 선택해야 함 **
        //int b = (hashVal + i*i) % M;
        //int b = (hashVal + i * hashFn2(key)) % M;

        if(isEmpty(HT, b))
            return -1;
        else if(HT->B[b].key == key)
            return b;
    }
    return -1;
}

int deleteItem(HashTable* HT, int key) {
    int hashVal = hashFn(key);

    for(int i = 0; i < M; i++) {
        int b = (hashVal + i) % M;                      //선형 조사법 ** insert와 같은 방식 선택해야 함 **
        //int b = (hashVal + i*i) % M;                  //이차 조사법
        //int b = (hashVal + i * hashFn2(key)) % M;     //이중 해싱법 (최적!!)

        if(isEmpty(HT, b))
            return -1;
        else if(HT->B[b].key == key) {
            HT->B[b].key = -1;  //selete 후 search 하기 위해서는 처음부터 비어있던 곳과 구분해야함
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

int main(void) {

    HashTable HT;
    init(&HT);

    int data[] = {25, 13, 16, 15, 7, 28, 31, 20, 1, 38};

    printf(" h(key)     0  1  2  3  4  5  6  7  8  9 10 11 12\n");
    printf("========   ======================================\n");

    for(int i = 0; i < 10; i++) {
        printf("h(%2d):%2d  ", data[i], hashFn(data[i]));
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
