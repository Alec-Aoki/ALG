#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "PCV.h"

// Estrutura para armazenar uma permutação
typedef struct Permutacao_{
    int *elementos; // Elementos da permutação
    int tamanho;    // Tamanho atual da permutação
} Permutacao;

typedef struct Indice_ {  // Dados fornecidos pelo usuário
    int cidadeA;
    int cidadeB;
    int distancia;
} INDICE;

int fatorial(int n);
void gerarPermutacoes(int *vetor, int num_cidades, Permutacao *caminho);
int elementoPresente(int *elementos, int tamanho, int valor);

//função para receber os dados do usuario
INDICE* PCV_ler_dados(int *num, int *ini, int *arestas) {
    scanf(" %d", num); //numero de cidades
    scanf(" %d", ini); //cidade inicial
    scanf(" %d", arestas); //numero de erestas

    INDICE *dist = (INDICE*)malloc(*arestas * sizeof(INDICE)); 
    if (dist == NULL)
        printf("Erro ao alocar memória.\n");
     
    for (int i = 0; i < *arestas; i++) {
        scanf(" %d %d %d", &dist[i].cidadeA, &dist[i].cidadeB, &dist[i].distancia); //cidade A, B e distancia 
    }
    return dist;
}

// função cria todas as pemutações possiveis com os caminhos
Permutacao* PCV_criar_caminhos(int num_cidades, int cidade_inicial, int arestas, INDICE* distancia) {
    int total_caminhos = fatorial(num_cidades-1);  // Calcula o número total de caminhos: (n-1)!

printf("total de caminhos %d\n", total_caminhos);

    Permutacao *caminhos = (Permutacao*)malloc(total_caminhos * sizeof(Permutacao)); // Aloca memória para todos os caminhos
    if (caminhos == NULL) 
        printf("Erro ao alocar memória.\n");
    
    for (int i = 0; i < total_caminhos; i++) {
        caminhos[i].elementos = (int*)malloc((num_cidades + 1) * sizeof(int));
        if (caminhos[i].elementos == NULL) 
            printf("Erro ao alocar memória.\n");
    }

    int x = num_cidades - 1;
    // Preenche o vetor com as cidades
    int vet[x];
    int k = 0;
    for (int i = 0; i < arestas; i++) {
        if (!elementoPresente(vet, k, distancia[i].cidadeA) && cidade_inicial != distancia[i].cidadeA) {
            vet[k++] = distancia[i].cidadeA;
        }
        if (!elementoPresente(vet, k, distancia[i].cidadeB) && cidade_inicial != distancia[i].cidadeB) {
            vet[k++] = distancia[i].cidadeB;
        }
    }

    gerarPermutacoes(vet, x, caminhos); //gera as pemutações e atribuia a caminhos

    //inclui a cidade inicial no inicio e no fim do percurso
    for (int i = 0; i < total_caminhos; i++) {
        caminhos[i].elementos[num_cidades] = cidade_inicial;  
        for (int j = num_cidades - 1; j > 0; j--) { 
            caminhos[i].elementos[j] = caminhos[i].elementos[j - 1];
        }
        caminhos[i].elementos[0] = cidade_inicial;
    }

    //***********************apagar depois**********************************
    printf("Todos os caminhos :\n ");
    for (int i=0;i<total_caminhos;i++){
        printf("Permutações: ");
        for (int j=0;j<num_cidades+1;j++){
            printf("%d", caminhos[i].elementos[j]);  
        }
        printf("\n");      
    }

    return caminhos;
}

// Verifica se um elemento já está presente na permutação
int elementoPresente(int *elementos, int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (elementos[i] == valor) {
            return 1;
        }
    }
    return 0;
}

// Função para alocar uma nova permutação
Permutacao* permutacao_alocar(int n) {
    Permutacao* caminhos = (Permutacao*)malloc(sizeof(Permutacao));
    if (caminhos == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    caminhos->elementos = (int*)malloc(n * sizeof(int));
    if (caminhos->elementos == NULL) {
        printf("Erro ao alocar memória.\n");
        free(caminhos);
        return NULL;
    }

    caminhos->tamanho = 0;
    return caminhos;
}

// Função para gerar todas as permutações usando fila
void gerarPermutacoes(int *vetor, int num_cidades, Permutacao *caminho) {
    int contador = 0;  // Contador para acompanhar o número de permutações geradas
    Fila* fila = NULL; // Ponteiro para a estrutura de fila que armazenará permutações parciais
    Fila_Inicializar(&fila); 

    Permutacao* permutacaoInicial = permutacao_alocar(num_cidades);
    if (permutacaoInicial == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    // Enfileira a permutação inicial vazia na fila para iniciar a construção das permutações
    Fila_Enfileirar(fila, permutacaoInicial);

    // Loop enquanto houver permutações parciais na fila a serem processadas
    while (!Fila_Vazia(fila)) {
        Permutacao* atual = Fila_Desenfileirar(fila);
        if (atual == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        // Se a permutação atual tiver o tamanho máximo (ou seja, contém todas as cidades)
        if (atual->tamanho == num_cidades) {
            caminho[contador] = *atual;
            contador++;
        } else {
            // Se a permutação ainda não está completa, tenta adicionar novos elementos
            for (int i = 0; i < num_cidades; i++) {
                // Verifica se o elemento vetor[i] já está presente na permutação atual
                if (!elementoPresente(atual->elementos, atual->tamanho, vetor[i])) {
                    Permutacao* novaPermutacao = permutacao_alocar(num_cidades);
                    if (novaPermutacao == NULL) {
                        printf("Erro ao alocar memória.\n");
                        exit(1);
                    }

                    // Copia os elementos da permutação atual para a nova permutação
                    memcpy(novaPermutacao->elementos, atual->elementos, atual->tamanho * sizeof(int));
                    // Ajusta o tamanho da nova permutação para o mesmo tamanho da permutação atual
                    novaPermutacao->tamanho = atual->tamanho;
                    // Adiciona o novo elemento (vetor[i]) na nova permutação
                    novaPermutacao->elementos[novaPermutacao->tamanho] = vetor[i];
                    novaPermutacao->tamanho++;  // Incrementa o tamanho da nova permutação

                    Fila_Enfileirar(fila, novaPermutacao);
                }
            }
        }
        free(atual);
    }
    while (!Fila_Vazia(fila)) {
        Permutacao* p = Fila_Desenfileirar(fila);
        free(p->elementos);  // Libera os elementos da permutação
    }
    Fila_Apagar(fila);
}


// Função para calcular o fatorial
int fatorial(int n) {
    if (n < 0) {
        printf("Erro: Fatorial não definido para números negativos.\n");
        exit(1);
    }
    int resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

// Função para encontrar o melhor caminho
void PCV_Melhor_caminho(Permutacao* caminhos, INDICE* distancia, int num_cidades, int arestas) {
    int total_caminhos = fatorial(num_cidades - 1);
    int melhor_caminho = 0;
    int melhor_custo = -1;

    for (int i = 0; i < total_caminhos; i++) {
        int custo = 0;
        int caminho_valido = 1;

        for (int j = 0; j < num_cidades; j++) {
            int origem = caminhos[i].elementos[j];
            printf("%d ", origem); //*******************************************
            int destino = caminhos[i].elementos[j + 1];
            printf("-> %d  ", destino); //**************************************
            int distancia_ij = -1;

            // Encontra a distancia entre duas cidades 
            for (int k = 0; k < arestas; k++) {
                if ((distancia[k].cidadeA == origem && distancia[k].cidadeB == destino) ||
                    (distancia[k].cidadeA == destino && distancia[k].cidadeB == origem)) {
                    distancia_ij = distancia[k].distancia;
                    printf("distancia %d \n", distancia[k].distancia);
                    break;
                }
            }

            //verifica se o caminho existe se não desconsidera o caminho
            if (distancia_ij == -1) {
                caminho_valido = 0;
                break;
            }

            //incrementa o custo
            custo += distancia_ij;
        }

        printf("custo : %d\n", custo);

        // Recebe o melhor caminho
        if (caminho_valido && (melhor_custo == -1 || custo < melhor_custo)) {
            melhor_custo = custo;
            melhor_caminho = i;
        }
    }

    if (melhor_custo != -1) {
        printf("\nMelhor Caminho: ");
        for (int i = 0; i < num_cidades; i++) {
            printf("%d ", caminhos[melhor_caminho].elementos[i]);
        }
        printf("%d\n", caminhos[melhor_caminho].elementos[0]);
        printf("Custo Total: %d\n", melhor_custo);
    } else {
        printf("Não foi possível encontrar um caminho válido.\n");
    }
}

// Função para liberar memória
void PCV_Apagar(INDICE* distancia, Permutacao* caminhos, int num_cidades) {
    int total_caminhos = fatorial(num_cidades - 1);

    for (int i = 0; i < total_caminhos; i++) {
        free(caminhos[i].elementos);
    }

    free(distancia);
    free(caminhos);  
}
