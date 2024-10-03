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

bool lista_inserir_posicao(LISTA *lista, ITEM *item);
bool lista_inserir_fim(LISTA *lista, ITEM *item);
ITEM *lista_busca_sequencial(LISTA *lista, int chave);
ITEM *lista_busca_ordenada(LISTA *lista, int chave);

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
    if(lista_cheia(lista)) return false;

    if(lista->ordenada){
        lista_inserir_posicao(lista, item);
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
        else{
            pontNo = pontNo->noSeguinte;
        }
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

bool lista_apagar(LISTA **lista){
    if(*lista == NULL) exit(1);

    NO *pontNo = (*lista)->inicio;

    for(int i=0; i<(*lista)->tamanho; i++){
        item_apagar(pontNo->pontItem);
        pontNo->pontItem = NULL;

        (*lista)->inicio = pontNo->noSeguinte;
        pontNo->noAnterior = NULL;
        pontNo->noSeguinte = NULL;
        free(pontNo);
        pontNo = (*lista)->inicio;

        (*lista)->tamanho--;
    }

    if((*lista)->tamanho == 0){
        (*lista)->inicio = NULL;
        (*lista)->fim = NULL;
        free(*lista);
        lista = NULL;

        return true;
    }
    else{
        return false;
    }
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) exit(1);

    return lista->tamanho;
}

bool lista_vazia(LISTA *lista){
    if(lista == NULL) exit(1);

    if(lista->tamanho == 0) return true;
    else{
        return false;
    }
}

bool lista_cheia(LISTA *lista){
    if(lista == NULL) exit(1);

    NO *noTeste = (NO *)malloc(sizeof(NO));
    if(noTeste == NULL) return true;
    else{
        free(noTeste);
        noTeste = NULL;

        return false;
    }
}

void lista_imprimir(LISTA *lista){
    if(lista == NULL) exit(1);

    NO *pontNo = lista->inicio;
    
    for(int i=0; i<lista->tamanho-1; i++){
        pritnf("%d ", item_getChave(pontNo->pontItem));
        pontNo = pontNo->noSeguinte;
    }
    printf("%d\n", item_getChave(pontNo->pontItem));

    return;
}

bool lista_inverter(LISTA *lista){
    if(lista == NULL) exit(1);
    if(lista->tamanho == 0) return false;

    NO *pontNo = lista->inicio;

    /*invertendo os ponteiros do primeiro nó*/
    pontNo->noAnterior = pontNo->noSeguinte;
    pontNo->noSeguinte = NULL;
    pontNo = pontNo->noAnterior;

    for(int i=0; i<lista->tamanho-1; i++){
        pontNo->noAnterior = pontNo->noSeguinte;
        pontNo->noSeguinte = pontNo;
        pontNo = pontNo->noAnterior;
        if(pontNo == NULL) break;
    }

    pontNo = lista->fim;
    lista->fim = lista->inicio;
    lista->inicio = pontNo;

    return true;
}

bool lista_comparar(LISTA *l1, LISTA *l2){
    if((l1 == NULL) || (l2 == NULL)) exit(1);

    if(l1->tamanho != l2->tamanho) return false;

    NO *pontL1 = l1->inicio;
    NO *pontL2 = l2->inicio;

    for(int i=0; i<l1->tamanho; i++){
        if(item_getChave(pontL1) != item_getChave(pontL2)) return false;
        else{
            pontL1 = pontL1->noSeguinte;
            pontL2 = pontL2->noSeguinte;
        }
    }

    return true;
}

ITEM *lista_busca(LISTA *lista, int chave){
    if(lista == NULL) exit(1);
    if(lista->tamanho == 0) exit(1);

    if(lista->ordenada) return lista_busca_ordenada(lista, chave);
    else if(!lista->ordenada) return lista_busca_sequencial(lista, chave);
}

ITEM *lista_busca_ordenada(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    NO *pontNo = lista->inicio;

    for(int i=0; i<lista->tamanho; i++){
        if(item_getChave(pontNo->pontItem) == chave) return pontNo->pontItem;
        else if(item_getChave(pontNo->pontItem) > chave) return NULL;
        else{
            pontNo = pontNo->noSeguinte;
            if(pontNo == NULL) return NULL;
        }
    }
}

ITEM *lista_busca_sequencial(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    NO *pontNo = lista->inicio;

    for(int i=0; i<lista->tamanho; i++){
        if(item_getChave(pontNo->pontItem) == chave) return pontNo->pontItem;
        else{
            pontNo = pontNo->noSeguinte;
            if(pontNo == NULL) return NULL;
        }
    }
}

bool lista_inserir_posicao(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);

    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) exit(1);
    noNovo->noAnterior = NULL;
    noNovo->noSeguinte = NULL;

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