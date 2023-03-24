#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element *data;
    int capacity;
    int top;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

int is_full(StackType *s) {
    return s->top == s->capacity - 1;
}

int is_empty(StackType *s) {
    return s->top == -1;
}

void push(StackType *s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

// 연습문제 14번
int size(StackType *s) {
    return s->top + 1;
}


int main(void) {
    StackType s;
    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    free(s.data);   // 메모리 해제
    return 0;
}