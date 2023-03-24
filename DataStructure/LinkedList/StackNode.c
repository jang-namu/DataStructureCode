// for linked stack
/*
    연결 리스트로 스택을 만들기 위해서, 굳이 원형이나 이중 연결 리스트를 사용할 필요가 없다.
    스택은 후입 선출로, 데이터가 추가되고 삭제되는 방향이 같다.
    즉, 맨 마지막에 들어온 데이터(노드)에 대한 정보만 가지고 있으면 스택의 모든 원소에 접근할 수 있다.
    배열의 스택은 top을 정수로 사용했지만, linked stack에서는 top을 StackNode를 가리키기 위한 포인터로 선언된다.
*/
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s) {
    s->top = NULL;
}

int is_empty(LinkedStackType *s) {
    return s->top == NULL;
}

int is_full(LinkedStackType *s) {
    // linked stack에서는 동적 할당이 가능한 이상, 스택의 크기가 무한정 늘어난다.
    return 0;
}

void push(LinkedStackType *s, element data) {
    StackNode *newnode = (StackNode *)malloc(sizeof(StackNode));
    newnode->data = data;
    newnode->link = s->top;
    s->top = newnode;
}

void print_stack(LinkedStackType *s) {
    for (StackNode *p = s->top; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    StackNode *removed = s->top;
    element temp = removed->data;
    s->top = s->top->link;
    free(removed);
    return temp;
}

element peek(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    return s->top->data;
}

int main(void) {
    LinkedStackType s;
    init(&s);
    push(&s, 1); print_stack(&s);
    push(&s, 2); print_stack(&s);
    push(&s, 3); print_stack(&s);
    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);
    return 0;
}