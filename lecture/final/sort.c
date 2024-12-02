#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int partition(int A[], int left, int right) {
    int pivot = A[left];
    int low = left + 1;
    int high = right;
    int tmp;

    while(low <= high) {
        while(low <= high && A[low] <= pivot)
            low++;

        while(low <= high && A[high] > pivot)
            high--;

        for(int i = 0; i < N; i++)
            printf("%d ", A[i]);
        printf("\nlow = %d, high = %d\n", low, high);

        if(low < high)
            SWAP(A[low], A[high], tmp);
    }

    SWAP(A[left], A[high], tmp);
    return high;
}

int sorted[N];

void selectionSort(int A[]) {
    for(int i = 0; i < N - 1; i++) {
        //print(A);
        int min = i;
        
        for(int j = i+1; j < N; j++) {
            if(A[j] < A[min])
                min = j;
        }
        int tmp = A[min];
        A[min] = A[i];
        A[i] = tmp;
    }
}

void insertionSort(int A[]) {
    printf("Before Sort : ");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    printf("\n<<<<<<<<<<<<<<< insertion sorting... >>>>>>>>>>>>>>>>\n");

    for(int i = 1; i <= N-1; i++) {
        int key = A[i];

        int j = i-1;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }

        A[j+1] = key;

        printf(" %d Pass >> ", i);
        for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
        printf("\n");
    }
}

void bubbleSort(int A[]) {
    printf("Before Sort : ");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    printf("\n<<<<<<<<<<<<<<< bubble sorting... >>>>>>>>>>>>>>>>\n");

    for(int i = 1; i <= N-1; i++) {
        for(int j = 1; j <= N - i; j++) {
            if(A[j-1] > A[j]) {
                int tmp = A[j-1];
                A[j-1] = A[j];
                A[j] = tmp;
            }
        }

        printf(" %d Pass >> ", i);
        for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
        printf("\n");
    }
}

void merge(int A[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while(i <= mid && j <= right) {
        if(A[i] <= A[j])
            sorted[k++] = A[i++];
        else
            sorted[k++] = A[j++];
    }

    if(i > mid)
        for(int l = j; l <= right; l++)
            sorted[k++] = A[l];
    else
        for(int l = i; l <= mid; l++)
            sorted[k++] = A[l];

    for(int l = left; l <= right; l++)
        A[l] = sorted[l];
}

void mergeSort(int A[], int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

void quickSort(int A[], int left, int right) {
    if(left < right) {
        int q = partition(A, left, right);
        quickSort(A, left, q-1);
        quickSort(A, q+1, right);
    }
}

int main() {
    int A[N] = {5, 3, 8, 4, 9, 1, 6, 2 ,7};
    // srand(time(NULL));
    // for(int i = 0; i < N; i++)
    //     A[i] = rand() % 100;

    // insertionSort(A);
    // bubbleSort(A);

    printf("Before Sort : ");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    // mergeSort(A, 0, N-1);       //잘 기억하기

    // printf("\n<<<<<<<<<<<<<<<< Merge Sorting... >>>>>>>>>>>>>>>\n");

    // printf("merge Sort : ");", A[i]);
    
    quickSort(A, 0, N-1);
    
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    return 0;
}