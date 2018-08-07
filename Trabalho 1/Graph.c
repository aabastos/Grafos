#include <stdlib.h>
#include <stdio.h>
#define vertex int

struct graph{
    int V;
    int A;
    int **adj;
};

typedef struct graph *Graph;

static int **MatrixInit(int r, int c, int val){
    int **m = malloc(r * sizeof(int *));
    for(vertex i = 0; i < r; i++){
        m[i] = malloc(c * sizeof(int));
    }
    for(vertex i = 0; i < r; i++){
        for(vertex j = 0; j < c; j++){
            m[i][j] = val;
        }
    }

    return m;
}

Graph GraphInit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MatrixInit(V, V, 0);
    return G;
}

void GraphInsertArc(Graph G, vertex v, vertex w){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = 1;
        G->A++;
    }
}

void GraphInsertArcWithoutDirection(Graph G, vertex v, vertex w){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = 1;
        G->adj[w][v] = 1;
        G->A++;
    }
}

void GraphInsertArcWithWeight(Graph G, vertex v, vertex w, int weight){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = weight;
        G->A ++;
    }
}

void GraphInsertArcWithoutDirectionWithWeight(Graph G, vertex v, vertex w, int weight){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = weight;
        G->adj[w][v] = weight;
        G->A ++;
    }
}

void GraphRemoveArc(Graph G, vertex v, vertex w){
    if(G->adj[v][w] != 0){
        G->adj[v][w] = 0;
        G->A --;
    }
}

void GraphRemoveArcWithoutDirection(Graph G, vertex v, vertex w){
    if(G->adj[v][w] != 0){
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;
        G->A --;
    }
}

void GraphShow(Graph G){
    for(vertex v = 0; v < G->V; v++){
        printf("%2d:", v);
        for(vertex w = 0; w < G->V; w++){
            if(G->adj[v][w] == 1){
                printf(" %2d", w);
            }
        }
        printf("\n");
    }
}

Graph GraphBuildComplete(int V){
    Graph G;
    G = GraphInit(V);

    for(vertex v = 0; v < G->V; v++){
        for(vertex w = 0; w < G->V; w++){
            if(v != w){
                GraphInsertArc(G, v, w);
            }
        }
    }

    return G;
}

int main(){
  teste
}
