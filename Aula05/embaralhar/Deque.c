#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Deque.h"

struct deque_{
    ITEM *item[MAX_TAMANHO];
    int inicio;
    int fim;
    int total;
};

DEQUE* deque_criar(void){
    DEQUE *deque = (DEQUE *)malloc(sizeof(DEQUE));
    if(deque != NULL){
        deque->inicio = 0;
        deque->fim = 0;
        deque->total = 0;
    }

    return deque;
}

void deque_apagar(DEQUE** deque){
    if(*deque != NULL){
        for(int i=0; i<MAX_TAMANHO; i++){
            if((*deque)->item[i] != NULL){
                item_apagar(&((*deque)->item[i]));
            }
        }

        free(*deque);
        *deque = NULL;
    }

    return;
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){
    if(deque == NULL || item == NULL) return false;
    if(deque_cheia(deque)) return false;

    if((deque->inicio == 0) && (deque->item[deque->inicio] != NULL)){
        deque->inicio = MAX_TAMANHO-1;
    }
    else if (deque->inicio != 0){
        (deque->inicio)--;
    }

    deque->item[deque->inicio] = item;
    (deque->total)++;

    return true;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){
    if((deque == NULL) || (item == NULL)) return false;
    if(deque_cheia(deque)) return false;

    if(deque->fim == MAX_TAMANHO) deque->fim = 0;

    deque->item[deque->fim] = item;
    (deque->fim)++;
    (deque->total)++;

    return true;
}

ITEM* deque_remover_inicio(DEQUE* deque){
    if(deque == NULL) return NULL;
    if(deque_vazia(deque)) return NULL;

    ITEM *itemAux = deque->item[deque->inicio];
    deque->item[deque->inicio] = NULL;
    (deque->inicio)++;
    if(deque->inicio = MAX_TAMANHO) deque->inicio = 0;

    (deque->total)--;

    return itemAux;
}

ITEM* deque_remover_fim(DEQUE* deque){
    if(deque == NULL) return NULL;
    if(deque_vazia(deque)) return NULL;

    if(deque->fim == 0){
        deque->fim = MAX_TAMANHO-1;
    }
    else{
        (deque->fim)--;
    }

    ITEM *itemAux = deque->item[deque->fim];
    deque->item[deque->fim] = NULL;

    return itemAux;
}

ITEM* deque_primeiro(DEQUE* deque){
    if(deque == NULL) return NULL;
    if(deque_vazia(deque)) return NULL;

    ITEM *itemAux = deque->item[deque->inicio];

    return itemAux;
}

ITEM* deque_ultimo(DEQUE* deque){
    if(deque == NULL) return NULL;
    if(deque_vaza(deque)) return NULL;

    ITEM *itemAux;

    if(deque->fim == 0){
        itemAux = deque->item[MAX_TAMANHO-1];
        
        return itemAux;
    }

    itemAux = deque->item[(deque->fim)-1];

    return itemAux;
}

int deque_contar(DEQUE* deque){
    if(deque == NULL) return ERRO;

    return  deque->total;
}

bool deque_vazia(DEQUE* deque){
    if((deque == NULL) || (deque->total == 0)) return true;

    //else
    return false;
}

bool deque_cheia(DEQUE* deque){
    if(deque != NULL){
        if(deque->total == MAX_TAMANHO) return true;
    }

    return false;
}