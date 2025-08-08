#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "PCV.h"

// Estrutura para armazenar uma permutação
typedef struct PERMUTACAO_{
    int *elementos; // Elementos da permutação
    int tamanho;    // Tamanho atual da permutação
    int custo;
} PERMUTACAO;

typedef struct INDICE_ {  // Dados fornecidos pelo usuário
    int cidadeA;
    int cidadeB;
    int distancia;
} INDICE;

PERMUTACAO* gerarPermutacoes(int *vetor, int num_cidades, INDICE* distancia, int arestas, int cidade_inicial);
void PCV_Melhor_caminho(PERMUTACAO* caminho, INDICE* distancia, int num_cidades, int arestas, PERMUTACAO* melhor_caminho);
int elementoPresente(int *elementos, int tamanho, int valor);

// Função para receber os dados do usuario
INDICE* PCV_ler_dados(int *num, int *ini, int *arestas) {
    scanf(" %d", num); // Número de cidades
    scanf(" %d", ini); // Cidade inicial
    scanf(" %d", arestas); // Número de erestas

    INDICE *dist = (INDICE*)malloc(*arestas * sizeof(INDICE)); 
    if (dist == NULL){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (int i = 0; i < *arestas; i++) {
        scanf(" %d %d %d", &dist[i].cidadeA, &dist[i].cidadeB, &dist[i].distancia); //cidade A, B e distancia 
    }

    return dist;
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
PERMUTACAO* Permutacao_Alocar(int n) {
    PERMUTACAO* caminhos = (PERMUTACAO*)malloc(sizeof(PERMUTACAO));
    if (caminhos == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    caminhos->elementos = (int*)malloc(n * sizeof(int));
    if (caminhos->elementos == NULL) {
        printf("Erro ao alocar memória.\n");
        free(caminhos);
        exit(1);
    }

    caminhos->tamanho = 0;
    caminhos->custo = -1;
    return caminhos;
}

// Função cria todas as pemutações possiveis com os caminhos
PERMUTACAO* PCV_Melhor_Caminho(int num_cidades, int cidade_inicial, int arestas, INDICE* distancia) {
    int x = num_cidades - 1;  // Número de cidades a serem permutadas
    int vet[x];               // Vetor para armazenar cidades
    int k = 0;                // Índice para preencher o vetor

    // Preenche o vetor com as cidades excluindo a cidade inicial
    for (int i = 0; i < arestas; i++) {
        if (!elementoPresente(vet, k, distancia[i].cidadeA) && cidade_inicial != distancia[i].cidadeA) {
            vet[k++] = distancia[i].cidadeA;
        }
        if (!elementoPresente(vet, k, distancia[i].cidadeB) && cidade_inicial != distancia[i].cidadeB) {
            vet[k++] = distancia[i].cidadeB;
        }
        // Verifica se já preencheu todas as cidades necessárias
        if (k >= x) {
            break;
        }
    }

    PERMUTACAO *melhor_caminho = gerarPermutacoes(vet, num_cidades, distancia, arestas, cidade_inicial); // Gera as pemutações e atribuia a caminhos

    if (melhor_caminho->custo != -1) {
        for (int i = 0 ; i < num_cidades ; i++) {
            printf("%d-", melhor_caminho->elementos[i]);
        }
        printf("%d ", melhor_caminho->elementos[num_cidades]);
        printf("%d\n", melhor_caminho->custo);
    } else {
        printf("Não foi possível encontrar um caminho válido.\n");
    }

    return (melhor_caminho);
}

PERMUTACAO* gerarPermutacoes(int *vetor, int num_cidades, INDICE* distancia, int arestas, int cidade_inicial) {
    
    PERMUTACAO *melhor_caminho = Permutacao_Alocar(num_cidades + 1);
    PERMUTACAO* PermutacaoInicial = Permutacao_Alocar(num_cidades-1);// Cria a permutação inicial (vazia)

    Fila* fila = NULL; // Ponteiro para a estrutura de fila que armazenará permutações parciais
    Fila_Inicializar(&fila); 
    Fila_Enfileirar(fila, PermutacaoInicial);

    // Loop enquanto houver permutações parciais na fila a serem processadas
    while (!Fila_Vazia(fila)) {
        PERMUTACAO* atual = Fila_Desenfileirar(fila);

        // Se a permutação atual tiver o tamanho máximo (ou seja, contém todas as cidades)
        if (atual->tamanho == num_cidades - 1) {
            // Cria o caminho completo incluindo a cidade inicial no começo e no fim
            PERMUTACAO* caminho_completo = Permutacao_Alocar(num_cidades + 1);
            
            caminho_completo->elementos[0] = cidade_inicial;
            for (int i=0 ; i<atual->tamanho ; i++){
                caminho_completo->elementos[i+1] = atual->elementos[i];}
            
            caminho_completo->elementos[num_cidades] = cidade_inicial;
            caminho_completo->tamanho = num_cidades + 1;

            /*
            // Exibe a permutação atual
            printf("Permutação: ");
            for (int i = 0; i < caminho_completo->tamanho; i++) {
                printf("%d ", caminho_completo->elementos[i]);
            }
            printf("\n");
            */

            // Avalia o caminho completo para ver se é o melhor caminho
            PCV_Melhor_caminho(caminho_completo, distancia, num_cidades, arestas, melhor_caminho);

            free(caminho_completo->elementos);
            free(caminho_completo);

        } else {
            // Se a permutação ainda não está completa, tenta adicionar novos elementos
            for (int i = 0; i < num_cidades-1; i++) {
                // Verifica se o elemento vetor[i] já está presente na permutação atual
                if (!elementoPresente(atual->elementos, atual->tamanho, vetor[i])) {
                    PERMUTACAO* Nova_Pemutacao = Permutacao_Alocar(num_cidades-1);
                    // Copia os elementos da permutação atual para a nova permutação
                    for (int i=0 ; i<atual->tamanho ; i++){
                        Nova_Pemutacao->elementos[i] = atual->elementos[i];}
                    Nova_Pemutacao->tamanho = atual->tamanho;
                    // Adiciona o novo elemento (vetor[i]) na nova permutação
                    Nova_Pemutacao->elementos[Nova_Pemutacao->tamanho] = vetor[i];
                    Nova_Pemutacao->tamanho++;  // Incrementa o tamanho da nova permutação

                    Fila_Enfileirar(fila, Nova_Pemutacao);
                }
            }
        }

        free(atual->elementos);  // Libera os elementos da permutação atual
        free(atual);             // Libera a permutação atual
    }

    // Limpa a fila residual (caso algo tenha ficado)
    while (!Fila_Vazia(fila)) {
        PERMUTACAO* p = Fila_Desenfileirar(fila);
        free(p->elementos);  // Libera os elementos da permutação
        free(p);             // Libera a permutação
    }
    Fila_Apagar(fila);

    return melhor_caminho;  // Retorna o melhor caminho encontrado
}

void PCV_Melhor_caminho(PERMUTACAO* caminho, INDICE* distancia, int num_cidades, int arestas, PERMUTACAO* melhor_caminho) {
    int custo = 0;
    int caminho_valido = 1;

    // Loop para calcular o custo do caminho
    for (int j = 0; j < num_cidades; j++) {  // Corrigido para evitar acesso fora dos limites
        if (caminho_valido == 0)
            break;

        int origem = caminho->elementos[j];
        int destino = caminho->elementos[j + 1];
        int distancia_ij = -1;

        // Encontra a distância entre a origem e o destino
        for (int k = 0; k < arestas; k++) {
            if ((distancia[k].cidadeA == origem && distancia[k].cidadeB == destino) ||
                (distancia[k].cidadeA == destino && distancia[k].cidadeB == origem)) {
                distancia_ij = distancia[k].distancia;
                break;
            }
        }

        // Se não encontrou uma distância válida, desconsidera o caminho
        if (distancia_ij == -1) {
            caminho_valido = 0;
            break;
        }

        // Incrementa o custo do caminho
        custo += distancia_ij;
    }

    // Verifica se o caminho é válido e se é o melhor até agora
    if (caminho_valido && (melhor_caminho->custo == -1 || custo < melhor_caminho->custo)) {
        melhor_caminho->custo = custo;
        for (int i=0 ; i<num_cidades+1 ; i++){
            melhor_caminho->elementos[i] = caminho->elementos[i];
        }
    }
}

// Função para liberar memória
void PCV_Apagar(INDICE* distancia, PERMUTACAO* melhor_caminho ) {

    // Libera a memória alocada para o melhor caminho
    free(melhor_caminho->elementos);  
    free(melhor_caminho);
    free(distancia);

}