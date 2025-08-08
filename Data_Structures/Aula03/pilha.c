#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "pilha.h"

#define TAM 100

struct pilha_{
    ITEM *item[TAM]; //vetor de ponteiros para itens
    int topo; //guarda o índice do topo da pilha
};

PILHA *pilha_criar(void){
    PILHA *pilhaTemporaria = (PILHA *)malloc(sizeof(PILHA));
    if(pilhaTemporaria != NULL){
        pilhaTemporaria->topo = 0;
    }

    return pilhaTemporaria;
}

void pilha_apagar(PILHA **pilha){
    if(*pilha != NULL){

        int tam_pilha = pilha_tamanho(*pilha);
        for (int i=0; i<tam_pilha; i++){
            item_apagar(&((*pilha)->item[i]));
        }

        free(*pilha);
        *pilha = NULL;
    }
    return;
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if((pilha == NULL) || (pilha_cheia(pilha)) || (item == NULL)) return false;

    pilha->item[pilha->topo] = item;
    pilha->topo += 1;

    return true;
}

ITEM *pilha_desempilhar(PILHA *pilha){
    if(pilha_vazia(pilha)) return NULL;

    ITEM *itemTemporario = pilha->item[pilha->topo-1];
    pilha->item[pilha->topo-1] = NULL;
    pilha->topo -= 1;

    return itemTemporario;
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha == NULL) return NULL;

    return pilha->item[pilha->topo-1];
}

int pilha_tamanho(PILHA *pilha){
    if(pilha == NULL) return -1;

    return pilha->topo;
}

bool pilha_vazia(PILHA *pilha){
    if(pilha == NULL) return true;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha == NULL) return false;

    if(pilha->topo == TAM+1) return true;
}
