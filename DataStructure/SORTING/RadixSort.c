#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

int list[MAX_SIZE];
int n;

typedef struct QueueNode {
    int data;
    struct QueueNode *link;
} QueueNode;

typedef struct QueueType {
    QueueNode *head;
    QueueNode *tail;
} QueueType;

void init_queue(QueueType *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

int is_empty(QueueType *queue) {
    return queue->head == NULL && queue->tail == NULL;
}

void enqueue(QueueType *q, int v) {
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = v;
    node->link = NULL;
    if (q->head == NULL && q->tail == NULL) {
        q->head = node;
        q->tail = node;
        return;
    }
    q->tail->link = node;
    q->tail = node;
}

int dequeue(QueueType *q) {
    if (is_empty(q)) {
        exit(1);
    }
    QueueNode *removed = q->head;
    int item = removed->data;
    q->head = q->head->link;
    if (is_empty(q)) {
        q->tail = NULL;
    }
    free(removed);
    return item;
}

#define BUCKETS 10
#define DIGITS 4
void radix_sort(int list[], int n) {
    int i, b, d, factor = 1;
    QueueType **queues = (QueueType **)malloc(BUCKETS * sizeof(QueueType*));

    for (b=0; b < BUCKETS; b++) {
        queues[b] = (QueueType *)malloc(sizeof(QueueType));
        init_queue(queues[b]);
    }

    for (d=0; d<DIGITS; d++) {
        for (i=0; i<n; i++) {
            enqueue(queues[(list[i]/factor) %10], list[i]);
        }
        for (b=i=0; b < BUCKETS; b++) {
            while (!is_empty(queues[b])) {
                list[i++] = dequeue(queues[b]);
            }
        }
        factor *= 10;
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
    //quick_sort(list, 0, n-1);
    radix_sort(list, 10);
    for (i=0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}