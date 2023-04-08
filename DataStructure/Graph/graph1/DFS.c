#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int num_vertices;
    int **adj_matrix;
} Graph;

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

Graph* create(int size) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_vertices = size;
    graph->adj_matrix = (int **)malloc(graph->num_vertices * sizeof(int *));
    for (int i=0; i < graph->num_vertices; i++) {
        graph->adj_matrix[i] = (int *)malloc(graph->num_vertices * sizeof(int));
        for (int j=0; j < graph->num_vertices; j++) {
            graph->adj_matrix[i][j] = 0;
        }
    }
    return graph;
}   

void insert_vertex(Graph *graph) {
    int num_vertex = graph->num_vertices;
    graph->num_vertices++;

    graph->adj_matrix = (int **)realloc(graph->adj_matrix, graph->num_vertices * sizeof(int*));
    for (int i=0; i < num_vertex; i++) {
        graph->adj_matrix[i] = (int *)realloc(graph->adj_matrix[i], graph->num_vertices * sizeof(int));
        graph->adj_matrix[i][num_vertex] = 0;
    }
    
    graph->adj_matrix[num_vertex] = (int *)malloc(graph->num_vertices * sizeof(int));
    for (int i=0; i < graph->num_vertices; i++) {
        graph->adj_matrix[num_vertex][i] = 0;
    }   
}

void insert_edge(Graph *graph, int src, int dest) {
    if (src >= graph->num_vertices || dest >= graph->num_vertices) {
        fprintf(stderr, "out of range");
        exit(1);
    }
    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1;
}


void print_graph(Graph *graph) {
    for (int i=0; i < graph->num_vertices; i++) {
        for (int j=0; j < graph->num_vertices; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void dfs(Graph *graph, int node, int *visited) {
    if (visited[node] == 1) {
        return;
    }
    visited[node] = 1;
    printf("%d -> ", node);
    for (int i=0; i < graph->num_vertices; i++) {
        if (graph->adj_matrix[node][i]) { 
            dfs(graph, i, visited);
        }
    }
}

void bfs(Graph *graph, int v) {
    QueueType *queue = (QueueType *)malloc(sizeof(QueueType));
    int *visited = (int *)calloc(graph->num_vertices, sizeof(int));
    visited[v] = 1;
    init_queue(queue);
    enqueue(queue, v);

    while(!is_emptyq(queue)) {
        int temp = dequeue(queue);
        printf("%d -> ", temp);
        for (int i=0; i < graph->num_vertices; i++) {
            if (graph->adj_matrix[temp][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    free(visited);
    free(queue);
}

int main(void) {
    Graph *graph = create(5);
    insert_vertex(graph);
    insert_edge(graph, 0, 2);
    insert_edge(graph, 2, 1);
    insert_edge(graph, 2, 3);
    insert_edge(graph, 0, 4);
    insert_edge(graph, 4, 5);
    insert_edge(graph, 1, 5);
    print_graph(graph);
    int *visited = (int *)calloc(graph->num_vertices, sizeof(int));
    int i = 0;
    dfs(graph, i, visited);
    printf("\n");
    bfs(graph, 0);
    printf("\n");
    return 0;
}