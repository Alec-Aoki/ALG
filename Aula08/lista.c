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
    NO *noCabeca;
    int tamanho;
    bool ordenada;
};

NO *no_criar(NO *noAnterior, NO *noSeguinte, ITEM *item);
bool lista_inserir_posicao(LISTA *lista, ITEM *item);
bool lista_inserir_fim(LISTA *lista, ITEM *item);
ITEM *lista_busca_sequencial(LISTA *lista, int chave);
ITEM *lista_busca_ordenada(LISTA *lista, int chave);

NO *no_criar(NO *noAnterior, NO *noSeguinte, ITEM *item){
    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) exit(1);

    noNovo->pontItem = item;
    noNovo->noAnterior = noAnterior;
    noNovo->noSeguinte = noSeguinte;

    return noNovo;
}

LISTA *lista_criar(bool ordenacao){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if(lista == NULL) exit(1);

    NO *noCabeca = no_criar(NULL, NULL, NULL);
    noCabeca->noAnterior = noCabeca;
    noCabeca->noSeguinte = noCabeca;

    /* Verificar se
        NO *noCabeca = no_criar(noCabeca, noCabeca, NULL);
    funcionaria
    */

    lista->noCabeca = noCabeca;
    lista->tamanho = 0;
    lista->ordenada = ordenacao;

    return lista;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);
    if(lista_cheia(lista)) return false;

    if(lista->ordenada){
        return lista_inserir_posicao(lista, item);
    }
    else{
        return lista_inserir_fim(lista, item);
    }
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);

    NO *noNovo = no_criar(lista->noCabeca->noAnterior, lista->noCabeca, item);

    lista->noCabeca->noAnterior->noSeguinte = noNovo;
    lista->noCabeca->noAnterior = noNovo;

    lista->tamanho++;

    return true;
}

bool lista_inserir_posicao(LISTA *lista, ITEM *item){
    if(lista == NULL) exit(1);

    int chaveItem = item_getChave(item);
    NO *pontNoBusca = lista->noCabeca->noSeguinte;

    lista->noCabeca->pontItem = item;

    while(chaveItem > item_getChave(pontNoBusca->pontItem)){
        pontNoBusca = pontNoBusca->noSeguinte;
    }

    if(pontNoBusca == lista->noCabeca){
        lista->noCabeca->pontItem = NULL;
        return lista_inserir_fim(lista, item);
    }
    
    //else:
    NO *noNovo = no_criar(pontNoBusca->noAnterior, pontNoBusca, item);

    pontNoBusca->noAnterior->noSeguinte = noNovo;
    pontNoBusca->noAnterior = noNovo;

    lista->tamanho++;
        
    return true;
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    ITEM *itemTempCabeca = item_criar(NULL, chave);
    lista->noCabeca->pontItem = itemTempCabeca;
    NO *pontNoBusca = lista->noCabeca->noSeguinte;

    while(item_getChave(pontNoBusca) != chave){
        pontNoBusca = pontNoBusca->noSeguinte;
    }

    if(pontNoBusca == lista->noCabeca){
        item_apagar(&itemTempCabeca);
        lista->noCabeca->pontItem = NULL;
        
        return NULL;
    }
    
    //else:
    pontNoBusca->noAnterior->noSeguinte = pontNoBusca->noSeguinte;
    pontNoBusca->noSeguinte->noAnterior = pontNoBusca->noAnterior;

    pontNoBusca->noAnterior = NULL;
    pontNoBusca->noSeguinte = NULL;
    ITEM *itemRemovido = pontNoBusca->pontItem;
    pontNoBusca->pontItem = NULL;
    free(pontNoBusca);
    pontNoBusca = NULL;

    lista->tamanho--;

    return itemRemovido;
}

bool lista_apagar(LISTA **lista){
    if(*lista == NULL) exit(1);

    NO *pontNoBusca = (*lista)->noCabeca->noSeguinte;

    while(!lista_vazia(*lista)){
        int chaveAtual = item_getChave(pontNoBusca->pontItem);
        ITEM *itemTemp = lista_remover(*lista, chaveAtual);
        item_apagar(&itemTemp);
        
        pontNoBusca = pontNoBusca->noSeguinte;
    }

    return true;
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) exit(1);

    return lista->tamanho;
}

bool lista_vazia(LISTA *lista){
    if(lista == NULL) exit(1);

    if(lista->tamanho == 0) return true;
    
    //else:
    return false;
}

bool lista_cheia(LISTA *lista){
    if(lista == NULL) exit(1);

    NO *noTeste = no_criar(NULL, NULL, NULL);

    if(noTeste == NULL) return true;

    else{
        free(noTeste);
        noTeste = NULL;

        return false;
    }
}

void lista_imprimir(LISTA *lista, bool comQuebraDeLinha){
    if(lista == NULL) exit(1);

    NO *noPercorrer = lista->noCabeca->noSeguinte;

    if(comQuebraDeLinha){
        while(noPercorrer != lista->noCabeca){
            printf("%d\n", item_getChave(noPercorrer->pontItem));
            noPercorrer = noPercorrer->noSeguinte;
        }

        return;
    }

    //else:
    for(int i=0; i<lista->tamanho-1; i++){
        printf("%d ", item_getChave(noPercorrer->pontItem));
        noPercorrer = noPercorrer->noSeguinte;
    }
    printf("%d\n", item_getChave(noPercorrer->pontItem));

    return;
}

ITEM *lista_busca(LISTA *lista, int chave){
    if(lista == NULL) exit(1);

    ITEM *itemTempCabeca = item_criar(NULL, chave);
    lista->noCabeca->pontItem = itemTempCabeca;

    NO *pontNoBusca = lista->noCabeca->noSeguinte;
    while(item_getChave(pontNoBusca) != chave){
        pontNoBusca = pontNoBusca->noSeguinte;
    }

    if(pontNoBusca == lista->noCabeca){
        item_apagar(&itemTempCabeca);
        lista->noCabeca->pontItem = NULL;

        return NULL;
    }
    //else:
    return pontNoBusca->pontItem;
}