#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

typedef struct no_ NO;

struct no_{
    NO *noSeguinte;
    NO *noAnterior;
    ITEM *pontItem;
};

struct lista_{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
};

bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao);
bool lista_inserir_fim(LISTA *lista, ITEM *item);

LISTA *lista_criar(bool ordenacao){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if(lista == NULL) exit(1);

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    lista->ordenada = ordenacao;

    return lista;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);

    if(lista->ordenada){
        int posicao = lista_busca(lista, item_get_chave(item));

        lista_inserir_posicao(lista, item, posicao);
    }
    else{
        lista_inserir_fim(lista, item);
    }

    lista->tamanho++;

    return true;
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    NO *pontNo = lista->inicio;
    while(pontNo != NULL){
        if(chave == item_getChave(pontNo->pontItem)) break;
        pontNo = pontNo->noSeguinte;
    }

    if(pontNo == lista->inicio){
        lista->inicio = pontNo->noSeguinte;
        lista->inicio->noAnterior = NULL;
    }
    else if(pontNo == lista->fim){
        lista->fim = pontNo->noAnterior;
        lista->fim->noSeguinte = NULL;
    }
    else{
        pontNo->noAnterior->noSeguinte = pontNo->noSeguinte;
        pontNo->noSeguinte->noAnterior = pontNo->noAnterior;
    }
    
    ITEM *pontItem_aux;
    pontItem_aux = pontNo->pontItem;

    pontNo->noAnterior = NULL;
    pontNo->noSeguinte = NULL;
    pontNo->pontItem = NULL;
    free(pontNo);
    pontNo = NULL;

    lista->tamanho--;

    return pontItem_aux;
}

bool lista_apagar(LISTA **lista);
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);
int lista_inverter(LISTA **lista);
bool lista_comparar(LISTA *l1, LISTA *l2);

ITEM *lista_busca(LISTA *lista, int chave);


bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao){
    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) exit(1);

    int chaveItem = item_getChave(item);
    NO* pontNo = lista->inicio;

    for(int i=0; i<lista->tamanho; i++){
        if(chaveItem < item_getChave(pontNo->pontItem)){
            if(pontNo == lista->inicio){
                noNovo->noSeguinte = lista->inicio;
                lista->inicio = noNovo;
            }
            else{
                noNovo->noSeguinte = pontNo;
                pontNo->noAnterior->noSeguinte = noNovo;
            }

            lista->tamanho++;
            
            return true;
        }
        else{
            pontNo = pontNo->noSeguinte;
            if(pontNo == NULL) break;
        }
    }

    /*O item não pertence nem ao início nem ao meio da lista, logo inserimos no fim*/
    lista->fim->noSeguinte = noNovo;
    lista->fim = noNovo;
    lista->tamanho++;

    return true;
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);

    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) exit(1);

    noNovo->pontItem = item;
    noNovo->noAnterior = lista->fim;
    noNovo->noSeguinte = NULL;
        
    if(lista->tamanho == 0){
        lista->inicio = noNovo;
    }
    else{
        lista->fim->noSeguinte = noNovo;
    }

    lista->fim = noNovo;

    return true;
}