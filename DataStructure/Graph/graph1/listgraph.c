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

typedef struct GraphNode {
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct StackNode {
    int vertex;
    struct StackNode *link;
} StackNode;

typedef struct StackType {
    StackNode *top;
} StackType;

void init_stack(StackType *s) {
    s->top = NULL;
}

void push(StackType *s, int v) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->vertex = v;
    node->link = s->top;
    s->top= node;
}

int is_empty(StackType *s) {
    return s->top == NULL;
}

int pop(StackType *s) {
    StackNode *removed;
    int data;
    if (!is_empty(s)) {
         removed = s->top;
         data = removed->vertex;
         s->top = s->top->link;
         free(removed);
    }
    return data;
}

typedef struct GraphType {
    int n;
    GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void init(GraphType *g) {
    g->n = 0;
    for (int i=0; i < MAX_VERTICES; i ++) {
        g->adj_list[i] = NULL;
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
    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = dest;
    node->link = g->adj_list[src];
    g->adj_list[src] = node;

    node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = src;
    node->link = g->adj_list[dest];
    g->adj_list[dest] = node;
}

void print_adj_list(GraphType *g) {
    for (int i=0; i < g->n; i++) {
        GraphNode *node = g->adj_list[i];
        printf("vertex %d : ", i);
        while (node != NULL) {
            printf("%d -> ", node->vertex);
            node = node->link;
        }
        printf("\n");
    }
}

void free_graph(GraphType *g) {
    for (int i=0; i < g->n; i++) {
        GraphNode *node = g->adj_list[i];
        while (node != NULL) {
            GraphNode *temp = node;
            node = node->link;
            free(temp);
        }
    }
    free(g);
}

int get_degree(GraphType *g, int v) {
    GraphNode *node = g->adj_list[v];
    int count = 0;
    while(node != NULL) {
        node = node->link;
        count++;
    }
    return count;
}

void dfs_list(GraphType *graph, int *visited, int v) {
    visited[v] = 1;
    printf("%d -> ", v);
    for (GraphNode *i=graph->adj_list[v]; i != NULL; i=i->link) {
        if (!visited[i->vertex]) 
            dfs_list(graph, visited, i->vertex);
    }
}


void dfs_stack(GraphType *graph, int v) {
    int node;
    int *visited = (int *)calloc(6, sizeof(int));
    StackType *stack = (StackType *)malloc(sizeof(StackType));
    push(stack, v);
    while (!is_empty(stack)) {
        node = pop(stack);
        if (visited[node]) return;
        visited[node] = 1;
        GraphNode *i;
        for (i = graph->adj_list[node]; i!=NULL; i=i->link) {
            if (visited[i->vertex] == 0) {
                push(stack, i->vertex);
            }
        }
    }
}

void bfs(GraphType *graph, int v) {
    QueueType *queue = (QueueType *)malloc(sizeof(QueueType));
    int *visited = (int *)calloc(6, sizeof(int));
    visited[v] = 1;
    init_queue(queue);
    enqueue(queue, v);

    while (!is_emptyq(queue)) {
        int temp = dequeue(queue);
        printf("%d -> ", temp);
        for (GraphNode *i = graph->adj_list[temp]; i != NULL; i = i->link) {
            if (visited[i->vertex]) 
                continue;
            visited[i->vertex] = 1;
            enqueue(queue, i->vertex);
        }

    }
}


int main(void) {
    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for (int i=0; i < 6; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);
    print_adj_list(g);
    int *visited = (int *)calloc(6, sizeof(int));
    dfs_list(g, visited, 0);
    printf("\n");
    bfs(g, 0);
    printf("\n");
    free_graph(g);

    return 0;
}
