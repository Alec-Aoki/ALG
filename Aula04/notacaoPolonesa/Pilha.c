#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Pilha.h"

typedef struct no_{
    ITEM *pont_item;
    NO *proximoNo;
}NO;

struct pilha{
    NO *pont_noTopo;
    int topo;
};

PILHA *pilha_criar(void){
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));
    if(pilha != NULL){
        pilha->pont_noTopo = NULL;
        pilha->topo = 0;
    }

    return pilha;
}

void pilha_apagar(PILHA **pilha){
    if(*pilha == NULL) return;

    while((*pilha)->topo > 0){
        ITEM *itemTemp = pilha_desempilhar(*pilha);
        item_apagar(&itemTemp);
    }

    free(*pilha);
    *pilha = NULL;

    return;
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if(pilha == NULL || item == NULL) return false;
    if(pilha_cheia(pilha)) return false;

    NO *noNovo = (NO *)malloc(sizeof(NO));
    if(noNovo == NULL) return false;

    noNovo->pont_item = item;
    noNovo->proximoNo = pilha->pont_noTopo;

    pilha->pont_noTopo = noNovo;
    (pilha->topo)++;

    return true;
}

ITEM *pilha_desempilhar(PILHA *pilha){
    if(pilha == NULL) return NULL;

    NO *noAux = pilha->pont_noTopo;
    ITEM *itemAux = noAux->pont_item;

    pilha->pont_noTopo = noAux->proximoNo;

    free(noAux);
    noAux->pont_item = NULL;
    noAux->proximoNo = NULL;

    (pilha->topo)--;

    return itemAux;
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha == NULL) return NULL;

    return ((pilha->pont_noTopo)->pont_item);
}

int pilha_tamanho(PILHA *pilha){
    if(pilha == NULL) return -1;

    return pilha->topo;
}

bool pilha_vazia(PILHA *pilha){
    if(pilha == NULL) return true;

    if(pilha->topo == 0) return true;

    return false;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha == NULL) return false;

    NO *noTeste = (NO *)malloc(sizeof(NO));
    if(noTeste != NULL){
        free(noTeste);
        noTeste = NULL;
        return false;
    }

    return true;
}

float rpn(char *sequencia){

}