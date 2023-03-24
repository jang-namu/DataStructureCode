// linked Queue
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;

typedef struct LinkedQueueType {
    QueueNode *front;
    QueueNode *rear;
} LinkedQueueType;

void init(LinkedQueueType *s) {
    s->front = NULL;
    s->rear = NULL;
}

int is_empty(LinkedQueueType *s) {
    return s->front == NULL;
}

void enqueue(LinkedQueueType *s, element item) {
    QueueNode *newnode = (QueueNode *)malloc(sizeof(QueueNode));
    newnode->data = item;
    newnode->link = NULL;
    if (is_empty(s)) {
        s->front = s->rear = newnode;
    } else {
        s->rear->link = newnode;
        s->rear = newnode;
    }
}

element dequeue(LinkedQueueType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "큐가 비어있습니다 \n");
        exit(1);
    }
    QueueNode *removed = s->front;
    element value = removed->data;
    s->front = removed->link;
    if (s->front == NULL) { // 공백상태가 될 때, rear도 NULL로 초기화 시켜주는 것에 유의!
        s->rear = NULL;
    }
    free(removed);
    return value;
}

element peek(LinkedQueueType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "큐가 비어있습니다 \n");
        exit(1);
    }
    return s->front->data;
}

void print_queue(LinkedQueueType *s) {
    for (QueueNode *p = s->front; p != NULL; p = p->link) {
        printf(" <- | %d |", p->data);
    }
    printf(" <- NULL\n");
}

int main(void) {
    LinkedQueueType s;
    init(&s);

    for (int i = 0; i < 5; i++) {
        enqueue(&s, i);
        print_queue(&s);
    }

    for (int i = 0; i < 5; i++) {
        dequeue(&s);
        print_queue(&s);
    }
    
    return 0;
}