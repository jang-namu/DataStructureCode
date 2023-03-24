// 덱은 원형큐와 유사하지만 전, 후단 모두에서 데이터의 삽입과 삭제가 가능한 자료형이다.
// 즉, 원형큐에 전단 추가 함수와 후단 삭제 함수가 추가되는 자료형이다.
// 덱을 구현할 때, front가 음수가 되는것을 방지하기 위해 MAX_SIZE만큼 더한 후 모듈로 연산을 하는 것에 주의하라!!
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEQUE_SIZE 8
typedef int element;
typedef struct {
    element data[MAX_DEQUE_SIZE];
    int front;
    int rear;
} DequeType;

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기 deque는 front와 rear가 0부터 시작한다. (원형큐와 같다.)
void init_deque(DequeType *d) {
    d->front = 0;
    d->rear = 0;
}

// 포화상태와 공백상태를 구분하기 위해, 덱은 한칸을 비워둔다. (원형큐와 같다.)
int is_full(DequeType *d) {
    return (d->rear + 1) % MAX_DEQUE_SIZE == d->front;
}

int is_empty(DequeType *d) {
    return d->rear == d->front;
}

void add_front(DequeType *d, element item) {
    if (is_full(d)) {
        error("큐가 포화상태입니다.");
    }
    d->data[d->front] = item;
    d->front = (d->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
}

void add_rear(DequeType *d, element item) {
    if (is_full(d)) {
        error("큐가 포화상태입니다.");
    }
    d->rear = (d->rear + 1) % MAX_DEQUE_SIZE;
    d->data[d->rear] = item;
}

element delete_front(DequeType *d) {
    if (is_empty(d)){
        error("큐가 비어있음");
    }
    d->front = (d->front + 1) % MAX_DEQUE_SIZE;
    return d->data[d->front];
}

element delete_rear(DequeType *d) {
    if (is_empty(d)){
        error("큐가 비어있음");
    }
    element tmp = d->data[d->rear];
    d->rear = (d->rear + MAX_DEQUE_SIZE - 1) % MAX_DEQUE_SIZE;  // 음수가 될 수 있으므로 더한 후, 모듈로연산
    return tmp;
}

element get_front(DequeType *d) {
    if (is_empty(d)){
        error("큐가 비어있음");
    }
    return d->data[(d->front + 1) % MAX_DEQUE_SIZE];
}

element get_rear(DequeType *d) {
    if (is_empty(d)){
        error("큐가 비어있음");
    }
    return d->data[(d->rear)];
}

void print_deque(DequeType *d) {
    printf("Deque(frong=%d rear=%d) = ", d->front, d->rear);
    if (!is_empty(d)) {
        int i = d->front;
        do {
            i = (i + 1) % MAX_DEQUE_SIZE;
            printf("%d | ", d->data[i]);
            if (i == d->rear)
                break;
        } while (i != d->front);
    }
    printf("\n");
}

int main(void) {
    DequeType deque;
    init_deque(&deque);
    
    for (int i=0; i < 3; i++) {
        add_front(&deque, i);
        print_deque(&deque);
    }

    for (int i=0; i < 3; i++) {
        printf("%d\n", delete_rear(&deque));
        print_deque(&deque);
    }

    return 0;
}