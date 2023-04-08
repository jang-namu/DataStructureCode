#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50


typedef struct GraphNode {
    int dest;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode *adj[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *graph) {
    graph->n = 0;
    for (int i=0; i < MAX_VERTICES; i++) {
        graph->adj[i] = NULL;
    }
}

void insert_vertex(GraphType *graph, int v) {
    if ((graph->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점개수초과");
        return;
    }
    graph->n++;
}

void insert_edge(GraphType *graph, int u, int v) {
    GraphNode *node;
    if (u >= graph->n || v >= graph->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    node->dest = v;
    node->link = graph->adj[u];
    graph->adj[u] = node;
}

#define MAX_STACK_SIZE 100

typedef struct StackNode {
    int data;
    struct StackNode *link;
} StackNode;

typedef struct StackType {
    StackNode *top;
} StackType;

void init_stack(StackType *stack) {
    stack->top = NULL;
}

int is_empty(StackType *stack) {
    return stack->top == NULL;
}

void push(StackType *stack, int v) {
    StackNode *node;
    node->data = v;
    node->link = stack->top;
    stack->top = node;
}

int pop(StackType *stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "스택이 비어있음");
        exit(1);
    }
    int item = stack->top->data;
    stack->top = stack->top->link;
    return item;
}

int topological_sort(GraphType *graph) {
    int i;
    StackType *s;
    init_stack(s);
    GraphNode *node;

    int *in_degree = (int *)malloc(sizeof(graph->n));
    for (i=0; i < graph->n; i++) {
        in_degree[i] = 0;
    }
    for (i=0; i < graph->n; i++) {
        GraphNode *temp = graph->adj[i];
        while (temp != NULL) {
            temp = temp->link;
            in_degree[temp->dest]++;
        }
    }

    for (i=0; i < graph->n; i++) {
        if (in_degree[i] == 0) {
            push(s, i);
        }
    }

    i = 0;
    while (!is_empty(s)) {
        int w = pop(s);
        i++;
        printf("정점 %d ->", w);
        GraphNode *node = graph->adj[w];
        while (node != NULL) {
            in_degree[node->dest]--;
            if (in_degree[node->dest] == 0) {
                push(s, node->dest);
            }
            node = node->link;
        }
    }
    free(in_degree);
    free(s);
    printf("\n");
    return i == graph->n;
}

int main(void) {
    GraphType g;
    graph_init(&g);
    insert_vertex(&g, 0);
    insert_vertex(&g, 1);
    insert_vertex(&g, 2);
    insert_vertex(&g, 3);
    insert_vertex(&g, 4);
    insert_vertex(&g, 5);

    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 5);
    topological_sort(&g);
    return 0;
}