#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stack.h"
#define INF 9999999
#define MAX 10000000

/*Funções do PCV*/
int min(int a, int b);
int **aloca_matriz(int n);
int **ler_dados(int *ini, int *num_cidades, int *num_arestas);
bool tudo_visitado(bool *visitado, int n);
bool *criar_visitado(int n);
int *criar_caminho(int n);
int PCV(int cidade_atual, int n, bool visitado[], int **matriz, int origem, int *caminho, int *min_custo_global, int pos, int custo_atual, PILHA *pilha);
void liberar_memoria(int ***matriz, int **caminho, bool **visitado, int n);

/*Funções/struct do timer*/
typedef struct{
    clock_t start;
    clock_t end;
}Timer;
void start_timer(Timer *timer);
double stop_timer(Timer *timer);

// Função principal
int main() {
    int n, ini, arestas;
    int **matriz = ler_dados(&ini, &n, &arestas);
    bool *visitado = criar_visitado(n);
    int *caminho = criar_caminho(n);
    PILHA *pilha = pilha_criar();


    ini -= 1;  // Ajusta para índice 0
    visitado[ini] = true;
    caminho[0] = ini + 1;  // Adiciona a cidade inicial ao caminho

    int min_custo_global = INF;

    Timer tempoTimer;
    double tempoExec;
    start_timer(&tempoTimer);

    PCV(ini, n, visitado, matriz, ini, caminho, &min_custo_global, 1, 0, pilha);

    tempoExec = stop_timer(&tempoTimer);
    printf("\nTempo de execucao: %lfs\n", tempoExec);
   
    pilha_desempilha_imprime(pilha);
    printf(" %d\n", min_custo_global);

    // desalocação de memória
    liberar_memoria(&matriz, &caminho, &visitado, n);
    pilha_apagar(&pilha);


    return EXIT_SUCCESS;
}

// Função que retorna o menor entre dois inteiros
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Função auxiliar que aloca uma matriz quadrada de tamanho n (número de cidades)
int **aloca_matriz(int n) {
    int **matriz = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(sizeof(int) * n);
    }

    // Inicializa a matriz com MAX
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = MAX;
        }
    }

    return matriz;
}

// Função que lê os dados e guarda numa matriz de adjacência
int **ler_dados(int *ini, int *num_cidades, int *num_arestas) {
    scanf("%d %d %d", num_cidades, ini, num_arestas);

    int **matriz = aloca_matriz(*num_cidades);
    int k = 0;
    while (k < *num_arestas) {
        int origem, destino, dist;
        scanf("%d %d %d", &origem, &destino, &dist);
        matriz[origem - 1][destino - 1] = dist;
        matriz[destino - 1][origem - 1] = dist;
        k++;
    }
    for (int i = 0; i < *num_cidades; i++) {
        matriz[i][i] = 0;
    }

    return matriz;
}

// Função auxiliar que confere se todas as cidades foram visitadas
bool tudo_visitado(bool *visitado, int n) {
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            return false;
        }
    }
    return true;
}

// Funções para alocar memória para vetores auxiliares
bool *criar_visitado(int n) {
    bool *visitado = malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        visitado[i] = false;
    }
    return visitado;
}

int *criar_caminho(int n) {
    int *caminho = malloc(sizeof(int) * (n + 1));
    if (caminho == NULL) {
        printf("ERRO DE ALOCAÇÃO");
        exit(1);
    }
    return caminho;
}

// Algoritmo para calcular a melhor rota
int PCV(int cidade_atual, int n, bool visitado[], int **matriz, int origem, int *caminho, int *min_custo_global, int pos, int custo_atual, PILHA *pilha) {
    // Se todas as cidades foram visitadas, retornamos ao ponto de origem
    if (tudo_visitado(visitado, n)) {
        int custo_total = custo_atual + matriz[cidade_atual][origem];
        if (custo_total < *min_custo_global) {
            *min_custo_global = custo_total;
            pilha_desempilha_tudo(pilha);
            for (int i = 0; i < n; i++) {
                pilha_empilhar(pilha, caminho[i]);
            }
            pilha_empilhar(pilha, origem+1);
        }
        return custo_total;
    }

    // Variável para manter o menor custo
    int min_custo = INF;
    
    // Tentamos visitar todas as cidades não visitadas
    for (int prox_cidade = 0; prox_cidade < n; prox_cidade++) {
        if (!visitado[prox_cidade]) {
            visitado[prox_cidade] = true;
            caminho[pos] = prox_cidade + 1;

            // Recursão principal com o custo atual incrementado
            int custo = PCV(prox_cidade, n, visitado, matriz, origem, caminho, min_custo_global, pos + 1, custo_atual + matriz[cidade_atual][prox_cidade], pilha);

            min_custo = min(min_custo, custo);
            visitado[prox_cidade] = false;
        }
    }

    return min_custo;
}

// Função para liberar a memória
void liberar_memoria(int ***matriz, int **caminho, bool **visitado, int n) {
    for (int i = 0; i < n; i++) {
        free((*matriz)[i]);
    }
    free(*matriz);
    free(*caminho);
    free(*visitado);
}

void start_timer(Timer *timer){
    timer->start = clock();
    return;
}

double stop_timer(Timer *timer){
    timer->end = clock();
    return((double)(timer->end - timer->start)) / CLOCKS_PER_SEC;
}