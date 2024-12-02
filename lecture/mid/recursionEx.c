#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rSum(int n) {
    printf("%d + ", n);
    if(n == 1)
        return 1;
    else
        return n + rSum(n-1);
}

void rPrintDigit1(int n) {
    if(n < 10)
        printf("%5d - %d\n", n, n);
    else {
        rPrintDigit1(n / 10);
        printf("%5d - %d\n", n, n % 10);
    }
}

void rPrintDigit2(int n) {
    if(n < 10)
        printf("%5d - %d\n", n, n);
    else {
        printf("%5d - %d\n", n, n % 10);
        rPrintDigit2(n / 10);
    }
}

int getMax(int* arr, int i, int max) {
    if(i >= 0 && arr[i] > max){
        return getMax(arr, i-1, arr[i]);
    }
    else if(i >= 0){
        return getMax(arr, i-1, max);
    }
    else
        return max;
}

int rCountChar(char str[], char c, int i) {
    int cnt = (str[i] == c) ? 1 : 0;

    if(i == 0){
        return cnt;
    }
    else{
        return cnt + rCountChar(str, c, i-1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    srand(time(NULL));

    for(int i=0; i<n; i++){
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    printf("\n%d\n", getMax(arr, n-1, 0));

    /*
    rPrintDigit1(n);
    printf("----------------------------\n");
    rPrintDigit2(n);
    //printf("\b\b\b = %d\n", rsum(n));
    */

    return 0;
}