#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int sorted[N];

void selectionSort(int A[]) {
    printf("\n<<<<<<<<<<<<<<< selection sorting... >>>>>>>>>>>>>>>\n");

    for (int i = 0; i < N-1; i++) {
        int min = i;
        
        for (int j = i+1; j < N; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }

        int tmp = A[min];
        A[min] = A[i];
        A[i] = tmp;
    }
}

void insertionSort(int A[]) {
    printf("\n<<<<<<<<<<<<<<< insertion sorting... >>>>>>>>>>>>>>>>\n");

    for (int i = 1; i < N; i++) {
        int tmp = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > tmp) {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = tmp;
    }
}

void bubbleSort(int A[]) {
    printf("\n<<<<<<<<<<<<<<< bubble sorting... >>>>>>>>>>>>>>>>\n");

    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1-i; j++) {
            if (A[j] > A[j+1]) {
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}

void merge(int A[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    int Sorted[N];

    while (i <= mid && j <= right) {
        if (A[i] < A[j]) {
            Sorted[k] = A[i];
            i++;
        }
        else {
            Sorted[k] = A[j];
            j++;
        }
        k++;
    }

    if (i <= mid) {
        for (; i <= mid; i++) {
            Sorted[k] = A[i];
            k++;
        }
    }

    if (j <= right) {
        for (; j <= right; j++) {
            Sorted[k] = A[j];
            k++;
        }
    }

    for (int l = left; l <= right; l++) {
        A[l] = Sorted[l];
    }
}

void mergeSort(int A[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(A, left, mid);
        mergeSort(A, mid+1, right);

        merge(A, left, mid, right);
    }
}

int partition(int A[], int left, int right) {
    int pivot = A[left];
    int low = left + 1;
    int high = right;
    int tmp;

    while (low <= high) {   //check
        while (low <= high && A[low] < pivot) {
            low++;
        }
        while (low <= high && A[high] > pivot) {
            high--;
        }

        if (low < high) {
            SWAP(A[low], A[high], tmp);
        }
    }

    SWAP(A[left], A[high], tmp);
    return high;
}

void quickSort(int A[], int left, int right) {
    if (left < right) {
        int q = partition(A, left, right);

        quickSort(A, left, q-1);
        quickSort(A, q+1, right);
    }
}

int main() {
    int A[N];

    srand(time(NULL));
    for(int i = 0; i < N; i++)
        A[i] = rand() % 100;

    printf("Before Sort : ");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    int num;
    printf("1 : selection, 2 : insertion, 3 : bubble, 4: merge, 5 : quick\n->");
    scanf("%d", &num);

    switch(num) {
        case 1:
            selectionSort(A);
            break;
        case 2:
            insertionSort(A);
            break;
        case 3:
            bubbleSort(A);
            break;
        case 4:
            printf("\n<<<<<<<<<<<<<<< merge sorting... >>>>>>>>>>>>>>>>\n");
            mergeSort(A, 0, N-1);
            break;
        case 5:
            printf("\n<<<<<<<<<<<<<<< quick sorting... >>>>>>>>>>>>>>>>\n");
            quickSort(A, 0, N-1);
            break;
        default :
            printf("숫자를 제대로 입력하세요.\n");
    }

    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");

    return 0;
}