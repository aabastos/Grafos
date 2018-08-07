#include <stdlib.h>
#include <stdio.h>
#define vertex int
#define INFINITY 1000000000000
#define MEMBER 1
#define NONMEMBER 0

struct graph{
    int V;
    int A;
    int **adj;
};

typedef struct graph *Graph;

static int **MatrixInit(int r, int c, int val){
    int **m = new int*[r];

    for(int i = 0; i < r; i++){
        m[i] = new int[c];
    }

    for(vertex i = 0; i < r; i++){
        for(vertex j = 0; j < c; j++){
            m[i][j] = val;
        }
    }

    return m;
}

Graph GraphInit(int V){
    Graph G = (Graph) malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MatrixInit(V, V, 0);
    return G;
}

void GraphInsertArc(Graph G, vertex v, vertex w, int weight){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = weight;
        G->adj[w][v] = weight;
        G->A++;
    }
}

void dijkstra (Graph G, int s, int t){
    long dist[G->V];
    int perm[G->V], path[G->V];
    int current, i, k;
    long smalldist, newdist, dc;

    for (i = 0; i < G->V; i++) {
        perm[i] = NONMEMBER;
        dist[i] = INFINITY;
    }

    perm[s] = MEMBER;
    dist[s] = 0;

    current = s;
    k = current;

    while (current != t) {
        smalldist = INFINITY;
        dc = dist[current];

        for (i = 0; i < G->V; i++) {
            if (perm[i] == NONMEMBER) {
                if(G->adj[current][i] == 0){
                    newdist = dc + INFINITY;
                }else{
                    newdist = dc + G->adj[current][i];
                }

                if (newdist < dist[i]) {
                    dist[i] = newdist;
                    path[i] = current;
                }

                if (dist[i] < smalldist) {
                    smalldist = dist[i];
                    k = i;
                }
            }
        }

        current = k;
        perm[current] = MEMBER;
    }

    printf("%lu ", dist[t]);
}

int main(){
    int qtdFormigueiros = -1;

    while (qtdFormigueiros != 0) {
        scanf("%d", &qtdFormigueiros);
        Graph G;
        G = GraphInit(qtdFormigueiros);

        if(qtdFormigueiros >= 2 && qtdFormigueiros <= 100000){
            for(int i = 1; i < qtdFormigueiros; i++){
                int tunel, comprimento;
                scanf("%d", &tunel);
                scanf("%d", &comprimento);
                if((tunel >= 0 && tunel <= i - 1) && (comprimento >= 1 && comprimento <= 1000000000)){
                    GraphInsertArc(G, i, tunel, comprimento);
                }
            }

            int numConsultas;
            scanf("%d", &numConsultas);

            if(numConsultas >= 1 && numConsultas <= 100000){
                for(int i = 0; i < numConsultas; i++){
                    int origem, destino;
                    scanf("%d", &origem);
                    scanf("%d", &destino);

                    dijkstra(G, origem, destino);
                }
                printf("\n");
            }
        }
    }
}
