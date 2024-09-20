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
int lista_busca_ordenada(LISTA *lista, int chave);
int busca_binaria(LISTA *lista, int inicio, int fim, int chave);
bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao);

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista->tamanho == TAM_MAX) return false;

    int posicao = lista_busca_ordenada(lista, item_get_chave(item));
        
    return lista_inserir_posicao(lista, item, posicao);
}

int lista_busca_ordenada(LISTA *lista, int chave){
    if(lista == NULL) return -1;

    return busca_binaria(lista, lista->inicio, lista->fim-1, chave);
}

int busca_binaria(LISTA *lista, int inicio, int fim, int chave){
    int meio = (inicio + fim)/2;
    if(lista->lista[meio] == NULL){
        return 0;
    }
    
    int chaveMeio = item_get_chave(lista->lista[meio]);

    if((chave > chaveMeio) && (chave <= item_get_chave(lista->lista[fim]))){
        if(chave < item_get_chave(lista->lista[meio+1])){
            return meio+1;
        }
        return busca_binaria(lista, meio+1, fim, chave);
    }
    else if ((chave < chaveMeio) && (chave >= item_get_chave(lista->lista[inicio]))){
        if(chave > item_get_chave(lista->lista[meio-1])){
            return meio-1;
        }
        return busca_binaria(lista, inicio, meio-1, chave);
    }
    else{
        return fim+1;
    }
}

bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    /*shiftando todos os elementos da lista para a direita, abrindo espaço pro novo item*/
    if(posicao <= (lista->fim)-1){
        for(int i = (lista->fim)-1; i >= posicao; i--){
            lista->lista[i+1] = lista->lista[i];
        }
    }

    lista->lista[posicao] = item;
    lista->fim++;
    lista->tamanho++;

    return true;
}