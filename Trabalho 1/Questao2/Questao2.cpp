#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define INFINITO 100000000
#define vertex int
#define MEMBER 1
#define NONMEMBER 0

struct graph{
    int V;
    int A;
    float **adj;
};

struct cidade{
    char nome[15];
    int numRoteadores;
    int roteadorInicial;
    int roteadorFinal;
    float *coord_x;
    float *coord_y;
};

typedef struct cidade *Cidade;
typedef struct graph *Graph;

static float **MatrixInit(int r, int c, float val){
    float **m = new float*[r];

    for(int i = 0; i < r; i++){
        m[i] = new float[c];
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
    G->adj = MatrixInit(V, V, INFINITO);
    return G;
}

Cidade newCidade(char nome[15], int numRoteadores, int roteadorInicial, int roteadorFinal){
    Cidade cidade = (Cidade) malloc(sizeof *cidade);
    strcpy(cidade->nome, nome);
    cidade->numRoteadores = numRoteadores;
    cidade->roteadorInicial = roteadorInicial;
    cidade->roteadorFinal = roteadorFinal;
    cidade->coord_x = (float *) malloc(numRoteadores * sizeof(float));
    cidade->coord_y = (float *) malloc(numRoteadores * sizeof(float));

    return cidade;
}

void GraphInsertArc(Graph G, vertex v, vertex w, float weight){
    G->adj[v][w] = weight;
    G->adj[w][v] = weight;
    G->A ++;
}

float dijkstra (Graph G, int s, int t){
    float dist[G->V];
    int perm[G->V], path[G->V];
    int current, i, k;
    float smalldist, newdist, dc;

    for (i = 0; i < G->V; i++) {
        perm[i] = NONMEMBER;
        dist[i] = INFINITO;
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
                    newdist = dc + INFINITO;
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

    return dist[t];
}

int main(){
    int numCidades = -1;

    while(numCidades != 0){
        scanf("%d", &numCidades);

        if(numCidades >= 1 && numCidades <= 1000){
            Cidade cidades[numCidades];
            char nomCidade;
            int numRoteadores;
            int numRoteadoresTotal = 0;

            for(int i = 0; i < numCidades; i++){
                char nome[15];
                int numRoteadores;

                scanf("%s", nome);
                scanf("%d", &numRoteadores);

                if(i == 0){
                    cidades[i] = newCidade(nome, numRoteadores, 0, numRoteadores - 1);
                }else{
                    int roteadorInicial = cidades[i-1]->roteadorFinal + 1;
                    cidades[i] = newCidade(nome, numRoteadores, roteadorInicial, roteadorInicial + numRoteadores - 1);
                }

                for(int j = 0; j < numRoteadores; j++){
                    float coord_x, coord_y;

                    scanf("%f", &coord_x);
                    scanf("%f", &coord_y);

                    cidades[i]->coord_x[j] = coord_x;
                    cidades[i]->coord_y[j] = coord_y;
                }

                numRoteadoresTotal += numRoteadores;
            }

            Graph G = GraphInit(numRoteadoresTotal);

            int indices[numCidades];
            for(int i = 0; i < numCidades; i++){
                indices[i] = 0;
            }

            for(int i = 0; i < numCidades - 1; i++){
                char nome1[15];
                char nome2[15];
                Cidade cidade1;
                Cidade cidade2;

                scanf("%s", nome1);
                scanf("%s", nome2);

                int j = 0;
                int achou = 0;
                while(achou < 2){
                    if(strcmp(cidades[j]->nome, nome1) == 0 || strcmp(cidades[j]->nome, nome2) == 0){
                        if(achou == 0){
                            cidade1 = cidades[j];
                            achou++;
                            indices[j]++;
                        }else{
                            cidade2 = cidades[j];
                            achou++;
                            indices[j]++;
                        }

                    }
                    j++;
                }

                for(int k = 0; k < cidade1->numRoteadores; k++){
                    for(int l = 0; l < cidade2->numRoteadores; l++){
                        float newDist = sqrt(pow((cidade1->coord_x[k] - cidade2->coord_x[l]),2) + pow((cidade1->coord_y[k] - cidade2->coord_y[l]),2));

                        if(newDist < G->adj[cidade1->roteadorInicial + k][cidade2->roteadorInicial + l]){
                            GraphInsertArc(G, cidade1->roteadorInicial + k, cidade2->roteadorInicial + l, newDist);
                        }
                    }
                }
            }

            int cidade1 = -1, cidade2 = -1;
            for(int i = 0; i < numCidades; i++){
                if(indices[i] == 1){
                    if(cidade1 == -1){
                        cidade1 = i;
                    }else if(cidade2 == -1){
                        cidade2 = i;
                    }
                }
            }

            float menDist = INFINITO;
            for(int i = cidades[cidade1]->roteadorInicial; i <= cidades[cidade1]->roteadorFinal; i++){
                for(int j = cidades[cidade2]->roteadorInicial; j <= cidades[cidade2]->roteadorFinal; j++){
                    float dist = dijkstra(G, i, j);
                    if(dist < menDist){
                        menDist = dist;
                    }
                }
            }
            printf("%.1f\n", menDist);
        }
    }
}
