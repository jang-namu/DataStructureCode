#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct QueueNode {
    int data;
    struct QueueNode *link;
} QueueNode;

typedef struct QueueType {
    QueueNode *head;
    QueueNode *tail;
} QueueType;

void init_queue(QueueType *q) {
    q->head = q->tail = NULL;
}

int is_emptyq(QueueType *q) {
    return q->head == NULL;
}

void enqueue(QueueType *q, int v) {
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = v;
    node->link = NULL;
    if (is_emptyq(q)) {
        q->head = q->tail = node;
        return;
    }
    q->tail->link = node;
    q->tail = node;
}

int dequeue(QueueType *q) {
    QueueNode *removed;
    int temp;
    if (!is_emptyq(q)) {
        removed = q->head;
        temp = removed->data;
        q->head = removed->link;
        if (q->head == NULL) {
            q->tail = NULL;
        }
        free(removed);
        return temp;
    } else {
        fprintf(stderr, "오류");
        exit(1);
    }
}

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void init(GraphType *g) {
    g->n = 0;
    for (int i=0; i < MAX_VERTICES; i++) {
        for (int j=0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

void insert_vertex(GraphType *g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프 : 최대 정점 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType *g, int src, int dest) {
    if (src >= g->n || dest >= g->n) {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    g->adj_mat[src][dest] = 1;
    g->adj_mat[dest][src] = 1;
}

void print_adj_mat(GraphType *g) {
    for (int i=0; i < g->n; i++) {
        for (int j=0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}


int main(void) {
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for (int i=0; i < 4; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 1);
    insert_edge(g, 2, 1);
    insert_edge(g, 3, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 2, 3);
    print_adj_mat(g);
    free(g);
    return 0;
}
