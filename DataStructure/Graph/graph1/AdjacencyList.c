#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *link;
} Node;

typedef struct Graph {
    int num_vertices;
    Node **adj_list;
} Graph;

Node* create_node(int v) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->vertex = v;
    node->link = NULL;
    return node;
}

Graph* create_graph(int num_vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_list = (Node **)malloc(num_vertices * sizeof(Node*));
    for (int i=0; i < num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

// 일반적으로 src:원본, dest:사본 의미. 여기서는 출발지, 목적지
void add_edge(Graph *graph, int src, int dest) {
    Node *node = create_node(dest);
    node->link = graph->adj_list[src];
    graph->adj_list[src] = node;

    node = create_node(src);
    node->link = graph->adj_list[dest];
    graph->adj_list[dest] = node;
}

void add_vertex(Graph *graph) {
    int num_vertex = graph->num_vertices;
    graph->num_vertices++;
    graph->adj_list = (Node **)realloc(graph->adj_list, graph->num_vertices * sizeof(Node*));
    graph->adj_list[num_vertex] = NULL;
}

void free_graph(Graph *graph) {
    for (int i=0; i < graph->num_vertices; i++) {
        Node *node = graph->adj_list[i];
        while (node != NULL) {
            Node *temp = node;
            node = node->link;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);
}

void print_graph(Graph *graph) {
    for (int i=0; i < graph->num_vertices; i++) {
        printf("vertex %d : ", i);
        Node *node = graph->adj_list[i];
        while (node != NULL) {
            printf("%d -> ", node->vertex);
            node = node->link;
        }
        printf("\n");
    }
}

int main() {
    // 그래프 생성 및 간선 추가 예시
    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    
    // 그래프 출력 예시
    print_graph(graph);
    printf("\n");
    add_vertex(graph);
    add_edge(graph, 1, graph->num_vertices-1);
    print_graph(graph);

    // 그래프 메모리 해제
    free_graph(graph);
    
    return 0;
}