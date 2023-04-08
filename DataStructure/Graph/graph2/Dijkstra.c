#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int processed[MAX_VERTICES];

int choose(int distance[], int n, int processed[]) {
    int i, min, minpos;
    min = INF;
    minpos = -1;
    for (i=0; i < n; i++) {
        if (!processed[i] && min > distance[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void dijkstra(GraphType *g, int start) {
    int i, u, w;
    for (int i=0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        processed[i] = FALSE;
    }
    processed[start] =TRUE;

    for (i=0; i < g->n; i++) {
        u = choose(distance, g->n, processed);
        processed[u] = TRUE;
        for (w=0; w < g->n; w++) {
            if (!processed[w]) {
                if (distance[w] > distance[u] + g->weight[u][w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }
}