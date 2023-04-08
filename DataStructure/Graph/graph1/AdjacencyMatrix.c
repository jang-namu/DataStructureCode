#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int **adj_matrix;
    int num_vertices;
} Graph;

Graph* create_graph(int num_vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_matrix = (int **)malloc(num_vertices * sizeof(int*));
    for (int i=0; i < num_vertices; i++) {
        graph->adj_matrix[i] = (int *)malloc(num_vertices * sizeof(int));
        for (int j=0; j < num_vertices; j++) {
            graph->adj_matrix[i][j] = 0;
        }
    }
    return graph;
}

void add_edge(Graph *graph, int start, int end) {
    // 무방향 그래프
    graph->adj_matrix[start][end] = 1;
    graph->adj_matrix[end][start] = 1;
}

void print_graph(Graph *graph) {
    for (int i=0; i < graph->num_vertices; i++) {
        for (int j=0; j < graph->num_vertices; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void add_vertex(Graph *graph) {
    int num_vertex = graph->num_vertices;
    graph->num_vertices++;

    graph->adj_matrix = (int **)realloc(graph->adj_matrix, graph->num_vertices * sizeof(int *));
    for (int i=0; i < num_vertex; i++) {
        graph->adj_matrix[i] = (int *)realloc(graph->adj_matrix[i], graph->num_vertices * sizeof(int));
        graph->adj_matrix[i][graph->num_vertices] = 0;
    }

    graph->adj_matrix[num_vertex] = (int *)malloc(graph->num_vertices * sizeof(int));
    for (int i=0; i < graph->num_vertices; i++) {
        graph->adj_matrix[num_vertex][i] = 0;
    }
}

void free_graph(Graph *graph) {
    for (int i=0; i < graph->num_vertices; i++) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}


int main(void) {
    // 그래프 생성 및 간선 추가 예시
    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    
    // 그래프 출력 예시
    print_graph(graph);
    
    add_vertex(graph);
    add_edge(graph, 1, graph->num_vertices-1);
    print_graph(graph);


    // 그래프 메모리 해제
    free_graph(graph);
    
    return 0;
}