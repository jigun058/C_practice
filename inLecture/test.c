#include <stdio.h>

#define N 10

typedef struct Pair {
    int key;
    int value[N];
    struct Pair* next;
} Pair;

typedef struct Dictionary {
    Pair* head;
    int size;
} Dictionary;


int main(void)
{

    return 0;
}