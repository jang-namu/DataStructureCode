// 선택 정렬
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

int list[MAX_SIZE];
int n;

void selection_sort(int list[], int n) {
    int temp;
    for (int i=0; i < n-1; i++) {
        int least = i;
        for (int j=i+1; j < n; j++) {
            if (list[least] > list[j]) {
                least = j;
            }
        }
        SWAP(list[i], list[least], temp);
    }
}

void insertion_sort(int list[], int n) {
    int v, j;
    for (int i=1; i < n; i++) {
        v = list[i];
        for (j=i-1; j >= 0 && list[j] > v; j--) {
            list[j+1] = list[j];
        }
        list[j+1] = v;
    }
}

void bubble_sort(int list[], int n) {
    int temp;
    for (int i=0; i < n-1; i++) {
        for (int j=0; j < n-i-1; j++) {
            if (list[j] > list[j+1]) 
                SWAP(list[j], list[j+1], temp);
        }
    }
}

void inc_insertion_sort(int list[], int first, int last, int gap) {
    int i, j, key;
    for (i=first + gap; i < last; i = i + gap) {
        key = list[i];
        for (j=i-gap; j >= first && list[j] > key; j = j - gap) {
            list[j+gap] = list[j];
        }
        list[j+gap] = key;
    }
}

void shell_sort(int list[], int n) {
    int i, gap;
    for (gap=n/2; gap > 0; gap=gap/2) {
        if ((gap%2) == 0) gap++;    // gap이 짝수이면 1 증가시키는 것이 효율적.
        for (i=0; i < gap; i++) {
            inc_insertion_sort(list, i, n, gap);
        }
    }
}

int sorted[MAX_SIZE];
void merge(int list[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        } else {
            sorted[k++] = list[j++];
        }
    }

    if (i > mid) {
        for (int x=j; x <= right; x++) {
            sorted[k++] = list[x];
        }
    } else {
        for (int x=i; x <= mid; x++) {
            sorted[k++] = list[x];
        }
    }

    for (int x=left; x <= right; x++) {
        list[x] = sorted[x];
    }
}

void merge_sort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

int partition(int list[], int left, int right) {
    int low, high, temp;
    int pivot = list[left];
    low = left;
    high = right + 1;

    do {
        do {
            low++;
        } while (list[low] < pivot);
        do {
            high--;
        } while (list[high] > pivot);
        if (low < high) 
            SWAP(list[low], list[high], temp);
    } while (low < high);
    SWAP(list[left], list[high], temp);
    return high;
}

void quick_sort(int list[], int left, int right) {
    int q;
    if (left < right) {
        q = partition(list, left, right);
        quick_sort(list, left, q-1);
        quick_sort(list, q+1, right);
    }
}

int main(void) {
    int i;
    n = MAX_SIZE;
    srand(time(NULL));
    for (i=0; i < n; i++) {
        list[i] = rand() % 100;
    }
    for (i=0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    //selection_sort(list, n);
    //insertion_sort(list, n);
    //bubble_sort(list, n);
    //shell_sort(list, n);
    //merge_sort(list,0,n-1);
    quick_sort(list, 0, n-1);
    for (i=0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}