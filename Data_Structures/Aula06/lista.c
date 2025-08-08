#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

/*Lista Linear Simplesmente Encadeada*/

typedef struct no_ NO;

struct no_{
    ITEM *item;
    NO *noSeguinte;
};

struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
};

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    
    if(lista != NULL){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
    }

    return lista;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    //if(lista_cheia(lista)) return false;

    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) return false;
    noNovo->item = item;

    if(lista->tamanho == 0){
        lista->inicio = noNovo;
        lista->fim = noNovo;
        noNovo->noSeguinte = NULL;
    }

    lista->tamanho++;

    if(lista->ordenada){
        int chave_noNovo = item_getChave(item);
        NO *pontAux = lista->inicio;
        NO *pontAux_noAnterior = lista->inicio;

        for(int i=0; i<(lista->tamanho-1); i++){
            if(item_getChave(pontAux->item) > chave_noNovo){
                pontAux_noAnterior->noSeguinte = noNovo;
                noNovo->noSeguinte = pontAux;

                return true;
            }
            pontAux_noAnterior = pontAux;
            pontAux = pontAux->noSeguinte;
        }
    }

    else{
        lista->fim->noSeguinte = noNovo;
        lista->fim = noNovo;

        noNovo->noSeguinte = NULL;
    }

    return true;
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista == NULL) return NULL;
    //if(lista_vazia(lista)) return NULL;

    NO *pontAux = lista->inicio;
    NO *pontAux_noAnterior = lista->inicio;
    ITEM *item = NULL;

    lista->tamanho--;

    for(int i=0; i<(lista->tamanho+1); i++){
        if(item_getChave(pontAux->item) == chave){
            item = pontAux->item;
            pontAux_noAnterior->noSeguinte = pontAux->noSeguinte;
            
            pontAux->noSeguinte = NULL;
            pontAux->item = NULL;
            free(pontAux);
            pontAux = NULL;

            return item;
        }
        
        if(i == lista->tamanho) return item;

        pontAux_noAnterior = pontAux;
        pontAux = pontAux->noSeguinte;
    }
}