#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

#ifndef STRUCTS_
    #define STRUCTS_

    struct lista_{ 
        ITEM *lista[TAM_MAX];
        int inicio; // pos do primeiro item
        int fim; // pos do próximo espaço vazio
        int tamanho;
    };
#endif

bool lista_inserir(LISTA *lista, ITEM *item);
int busca_binaria(LISTA *lista, int inicio, int fim, int chave);
bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao);

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista->tamanho == TAM_MAX) return false;

    int posicao = busca_binaria(lista, lista->inicio, lista->fim-1, item_get_chave(item));
        
    return lista_inserir_posicao(lista, item, posicao);
}

int busca_binaria(LISTA *lista, int inicio, int fim, int chave){
    if(fim == -1) return 0;

    while(inicio < fim){
        int meio=(inicio+fim)/2;
        
        if(chave <= item_get_chave(lista->lista[meio])) fim = meio;
        else{
            inicio = meio+1;
        }
    }

    if(item_get_chave(lista->lista[inicio]) >= chave) return inicio;
    else{
        return fim+1;
    }
}

bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao){
    if(lista == NULL) return false;
    if(lista->tamanho == TAM_MAX) return false;

    /*shiftando todos os elementos da lista para a direita, abrindo espaço pro novo item*/
    for(int i = (lista->fim)-1; i >= posicao; i--){
        lista->lista[i+1] = lista->lista[i];
    }

    lista->lista[posicao] = item;
    lista->fim++;
    lista->tamanho++;

    return true;
}