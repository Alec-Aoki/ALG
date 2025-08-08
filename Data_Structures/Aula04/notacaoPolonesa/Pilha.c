#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Pilha.h"

struct no{
    ITEM *pont_item;
    NO *proximoNo;
};

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
    if(pilha == NULL || pilha_vazia(pilha)) return NULL;

    NO *noAux = pilha->pont_noTopo;
    ITEM *itemAux = noAux->pont_item;

    pilha->pont_noTopo = noAux->proximoNo;

    noAux->pont_item = NULL;
    noAux->proximoNo = NULL;
    free(noAux);

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
    PILHA *pilha = pilha_criar();

    double *pontChars = (double *)malloc(sizeof(double));
    if(pontChars == NULL) exit(1);

    int contador = 0, quantChars = 0;

    while(sequencia[contador] != '\0'){
        if((sequencia[contador] >= 48) && (sequencia[contador] <= 57)){
            //Salvando o número no vetor pontChars para podermos criar um item com ele
            quantChars++;
            pontChars = (double *)realloc(pontChars, quantChars*sizeof(double));
            if(pontChars == NULL) exit(1);
            pontChars[quantChars-1] = (double)(sequencia[contador] - 48);

            //Criando o item
            ITEM *caractere = item_criar(0, &(pontChars[quantChars-1]));
            pilha_empilhar(pilha, caractere);
        }
        else{
            ITEM *item_n2 = pilha_desempilhar(pilha);
            ITEM *item_n1 = pilha_desempilhar(pilha);
            double *n2 = (double *)item_get_dados(item_n2);
            double *n1 = (double *)item_get_dados(item_n1);
            double n3;

            quantChars++;
            pontChars = (double *)realloc(pontChars, quantChars*sizeof(double));
            if(pontChars == NULL) exit(1);

            switch(sequencia[contador]){
                case 43: //+
                    n3 = (*n1)+(*n2);
                    break;
                case 45: //-
                    n3 = (*n1)-(*n2);
                    break;
                case 42: //*
                    n3 = (*n1)*(*n2);
                    break;
                case 47: ///
                    n3 = (*n1)/(*n2);
                    break;
            }

            pontChars[quantChars-1] = n3;
            ITEM *item_n3 = item_criar(0, &(pontChars[quantChars-1]));
            pilha_empilhar(pilha, item_n3);
        }

        contador++;
    }

    ITEM *itemTemp = pilha_desempilhar(pilha);
    double *resposta = (double *)item_get_dados(itemTemp);

    return *resposta;
}