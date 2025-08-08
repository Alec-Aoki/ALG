#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "fila.h"

typedef struct no_ NO;

struct no_{
    ITEM *item;
    //NO *noAnterior;
    NO *noSeguinte;
};

struct fila_{
    int total;
    NO *noInicio;
    NO *noFim;
};

FILA *fila_criar(void){
    FILA *fila = (FILA *)malloc(sizeof(FILA));
    if(fila != NULL){
        fila->total = 0;
        fila->noInicio = NULL;
        fila->noFim = NULL;
    }

    return fila;
}

bool fila_inserir(FILA *fila, ITEM *item){
    if(fila == NULL || item == NULL) return false;
    if(fila_cheia(fila)) return false;

    NO *noNovo = (NO *)malloc(sizeof(NO));
    noNovo->item = item;
    if(fila->total == 0) fila->noInicio = noNovo;
    noNovo->noSeguinte = fila->noFim;

    fila->noFim = noNovo;
    (fila->total)++;

    return true;
}

ITEM *fila_remover(FILA *fila){
    if(fila == NULL || fila_vazia(fila)) return NULL;

    ITEM *itemAux = (fila->noInicio)->item;
    (fila->noInicio)->item = NULL;

    fila->noInicio = fila->noFim;

    for(int i=1; i<(fila->total)-1; i++){
        fila->noInicio = (fila->noInicio)->noSeguinte;
    }

    free((fila->noInicio)->noSeguinte);
    fila->noInicio->noSeguinte = NULL;

    return itemAux;
}

ITEM *fila_frente(FILA *fila){
    if(fila == NULL || fila_vazia(fila)) return NULL;

    NO *noAux = fila->noInicio;
    ITEM *itemAux = noAux->item;

    return itemAux;
}

int fila_tamanho(FILA *fila){
    if(fila == NULL) return NULL;

    return fila->total;
}

bool fila_cheia(FILA *fila){
    if(fila == NULL) return false;

    NO* noTemp = (NO *)malloc(sizeof(NO));
    if(noTemp != NULL){
        free(noTemp);
        noTemp = NULL;

        return false;
    }

    return true;
}

bool fila_vazia(FILA *fila){
    if(fila == NULL || fila->total == 0) return true;

    return false;
}

void fila_apagar(FILA **fila){
    apagar_no((*fila)->noFim);
    
    free(*fila);
    *fila = NULL;
    return;
}

void apagar_no(NO *no){
    if(no->noSeguinte != NULL){
        apagar_no(no->noSeguinte);
        no->noSeguinte = NULL;
    }

    if(no->noSeguinte == NULL){
        item_apagar(&(no->item));
        no->item = NULL;
        
        free(no);
        //no = NULL;

        return;
    }
}