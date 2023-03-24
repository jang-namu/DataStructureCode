// 선형큐, 원형큐 존재
// 선형큐는 배열의 삭제 시, 데이터를 한칸씩 당겨줘야됨 => 거의 안 쓴다.
// 원형큐 구현 시, 모듈로 연산을 통해 front와 rear를 갱신하는 것에 주의!!
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 8
typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

// 초기 원형큐는 front와 rear가 0부터 시작한다.
void init_queue(QueueType *q) {
    q->front = 0;
    q->rear = 0;
}

// 포화상태와 공백상태를 구분하기 위해, 원형큐는 한칸을 비워둔다.
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

void print_queue(QueueType *q) {
    printf("Queue(frong=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

int main(void) {
    QueueType q;
    int a;
    init_queue(&q);
    
    printf("--데이터 추가단계--\n");
    while (!is_full(&q)) {
        printf("정수를 입력하세요 : ");
        scanf("%d", &a);
        enqueue(&q, a);
        print_queue(&q);
    }

    printf("--데이터 삭제단계--\n");
    for (int i = 0; i < 6; i++) {
        printf("%d\n", dequeue(&q));
        print_queue(&q);
    }

    printf("--데이터 추가단계--\n");
    for (int i = 0; i < 6; i++) {
        printf("정수를 입력하세요 : ");
        scanf("%d", &a);
        enqueue(&q, a);
        print_queue(&q);
    }

    return 0;
}