#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a, b, t) ( (t) = (a), (a) = (b), (b) = (t) )
#define SIZE 5
#define MAX_WORD_SIZE 50
#define MAX_MEANING_SIZE 500
typedef struct element {
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
} element;
element list[SIZE];
element sorted[SIZE];

int compare(element e1, element e2) {
    return strcmp(e1.word, e2.word);
}

void merge(element list[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (compare(list[i], list[j]) <= 0) {
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
    for (i=left; i <= right; i++) {
        list[i] = sorted[i];
    }
}

void merge_sort(element list[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

int main(void) {
    int i, j;
    element temp;

    printf("5개의 단어와 의미를 입력하시오\n");
    for (i=0; i < SIZE; i++) {
        scanf("%s", list[i].word);
        scanf("%s", list[i].meaning);
    }

    merge_sort(list, 0, SIZE-1);
    printf("\n 정렬 후 사전 내용\n");
    for (i=0; i < SIZE; i++) {
        printf("%s : %s \n", list[i].word, list[i].meaning);
    }
    return 0;
}

/*

dog 개
cat 고양이
note 노트
pen 펜
node 노드


*/