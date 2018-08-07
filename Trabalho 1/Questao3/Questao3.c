#include <stdlib.h>
#include <stdio.h>
#define INFINITY 1000000000000
#define vertex int
#define MEMBER 1
#define NONMEMBER 0

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

void GraphInsertArc(Graph G, vertex v, vertex w, int weight){
    if(G->adj[v][w] == 0){
        G->adj[v][w] = weight;
        G->A ++;
    }
}

void GraphRemoveArc(Graph G, vertex v, vertex w){
    if(G->adj[v][w] > 0){
        G->adj[v][w] = 0;
        G->A --;
    }
}

long dijkstra (Graph G, int s, int t){
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
        printf(".\n");
        smalldist = INFINITY;
        dc = dist[current];

        int smallPath;
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
                    smallPath = i;
                    smalldist = dist[i];
                    k = i;
                }
            }
        }

        GraphRemoveArc(G, current, smallPath);
        current = k;
        perm[current] = MEMBER;
    }

    return dist[t];
}

int main(){
    int numCidades;
    int numRotas;

    scanf("%d", &numCidades);
    scanf("%d", &numRotas);

    if((numCidades >= 2 && numCidades <= 50) && (numRotas >= 1 && numRotas <= 5000)){
        Graph G = GraphInit(numCidades);

        for(int i = 0; i < numRotas; i++){
            int a, b, c;

            scanf("%d", &a);
            scanf("%d", &b);
            scanf("%d", &c);

            if((a >= 1 && a <= numCidades) && (b >= 1 && b <= numCidades)){
                GraphInsertArc(G, a-1, b-1, c);
            }
        }

        int numPessoas;
        int numAssentos;

        scanf("%d", &numPessoas);
        scanf("%d", &numAssentos);

        int preco = 0;
        while(numPessoas >= 0){
            if(numPessoas > numAssentos){
                preco += numAssentos * dijkstra(G, 0, numCidades - 1);
            }else{
                preco += numPessoas * dijkstra(G, 0, numCidades - 1);
            }

            numPessoas = numPessoas - numAssentos;
        }

        printf("%d\n", preco);
    }
}
