#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 8
typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

void init_queue(QueueType *q) {
    q->front = 0;
    q->rear = 0;
}

int is_full(QueueType *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int is_empty(QueueType *q) {
    return q->rear == q->front;
}

void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        fprintf(stderr, "큐가 포화상태입니다.");
        exit(1);
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType *q) {
    if (is_empty(q)){
        fprintf(stderr, "큐가 비어있음");
        exit(1);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType *q) {
    if (is_empty(q)){
        fprintf(stderr, "큐가 비어있음");
        exit(1);
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int service_time = 0;
    int service_customer;
    QueueType queue;
    init_queue(&queue);

    srand(time(NULL));
    for (int clock=0; clock < minutes; clock++) {
        printf("현재시각 = %d\n", clock);
        if ((rand()%10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n",
                    customer.id, customer.arrival_time, customer.service_time);
        }
        if (service_time > 0) {
            printf("고객 %d 업무처리중\n", service_customer);
            service_time--;
        }
        else {
            if (!is_empty(&queue)) {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time =  customer.service_time;
                printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
                        customer.id, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }
    }
    printf("전체 대기시간 = %d분\n", total_wait);
    return 0;
}