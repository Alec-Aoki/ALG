#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Pilha.h"

struct pilha{
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
        free(*pilha);
        *pilha = NULL;
    }

    return;
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    if(pilha == NULL) return false;
    if(pilha->topo == TAM) return false;
    
    pilha->item[pilha->topo] = item;
    (pilha->topo)++;

    return true;
}

ITEM *pilha_desempilhar(PILHA *pilha){
    if(pilha_vazia(pilha)) return NULL;

    ITEM *itemTemporario = pilha_topo(pilha);
    pilha->item[(pilha->topo)-1] = NULL;
    (pilha->topo)--;

    return itemTemporario;
}

ITEM *pilha_topo(PILHA *pilha){
    if(pilha == NULL) return NULL;

    return pilha->item[(pilha->topo)-1];
}

int pilha_tamanho(PILHA *pilha){
    if(pilha == NULL) return -1;

    return pilha->topo;
}

bool pilha_vazia(PILHA *pilha){
    if((pilha == NULL) || ((pilha->topo) == 0)) return true;

    return false;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha == NULL) return false;

    if(pilha->topo == TAM) return true;
}

void pilha_print(PILHA *pilha){
    return;
}

bool balanceada(char *sequencia){
    //*sequencia é um ponteiro que aponta para a string

    PILHA *pilhaAbertos = pilha_criar();
    if(pilhaAbertos == NULL) exit(1);
    int contador=0;

    while(sequencia[contador] != '\0'){

        if((sequencia[contador] == '{') || (sequencia[contador] == '(') || (sequencia[contador] == '[')){
            pilha_empilhar(pilhaAbertos, item_criar(contador, &sequencia[contador]));
        }

        else{
            if(pilha_vazia(pilhaAbertos)) return false;

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '('){
                if(sequencia[contador] != ')') return false;
            }

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '{'){
                if(sequencia[contador] != '}') return false;
            }

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '['){
                if(sequencia[contador] != ']') return false;
            }

            pilha_desempilhar(pilhaAbertos);
        }

        contador++;
    }

    if(pilha_vazia(pilhaAbertos)){
        return true;
    }
    else{
        return false;
    }
}