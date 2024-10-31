// lista.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

typedef struct Lista_ {
    int *dados;
    int tamanho;
    int capacidade;
}LISTA;

// Função auxiliar para busca binária
bool busca_binaria(LISTA *lista, int elemento) {
    int esquerda = 0, direita = lista->tamanho - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (lista->dados[meio] == elemento) {
            return true;
        } else if (lista->dados[meio] < elemento) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return false;
}

LISTA* Lista_Criar(int capacidade) {
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    lista->dados = (int*)malloc(capacidade * sizeof(int));
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
}

void Lista_Apagar(LISTA *lista) {
    free(lista->dados);
    free(lista);
}

void Lista_Inserir(LISTA *lista, int elemento) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->dados = (int*)realloc(lista->dados, lista->capacidade * sizeof(int));
    }

    // Encontra posição para inserção para manter a ordenação
    int i = lista->tamanho - 1;
    while (i >= 0 && lista->dados[i] > elemento) {
        lista->dados[i + 1] = lista->dados[i];
        i--;
    }
    lista->dados[i + 1] = elemento;
    lista->tamanho++;
}

void Lista_Remover(LISTA *lista) {
    if (lista->tamanho > 0) {
        lista->tamanho--;
    }
}

void Lista_Imprimir(LISTA *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d ", lista->dados[i]);
    }
    printf("\n");
}

int Lista_Consultar (LISTA *lista, int i){
    return lista->dados[i];
} 

