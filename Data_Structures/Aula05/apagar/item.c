#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"

struct item_{
    void *dado;
    int index;
};

ITEM *item_criar(int index, void *dado){
    if(dado == NULL) return NULL;

    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    if(item != NULL){
        item->dado = dado;
        item->index = index;
    }
    
    return item;
}

bool item_apagar(ITEM **item){
    if(*item != NULL){
        free(*item);
        *item = NULL;
        
        return true;
    }
    return false;
}

void *item_get_dados(ITEM *item){
    if(item == NULL) return NULL;

    return item->dado;
}

int item_get_chave(ITEM *item){
    if(item == NULL) return -1;

    return item->index;
}

bool item_set_chave(ITEM *item, int chave){
    if(item == NULL) return false;

    item->index = chave;
    return true;
}