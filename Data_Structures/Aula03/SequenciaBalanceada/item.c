#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"

struct item_{
    void *dado;
    int ID;
};

ITEM *item_criar(int chave, void *comp){

    ITEM *item = (ITEM *)malloc(sizeof(ITEM));
    if(item != NULL){
        item->ID = chave;
        item->dado = comp;
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

int item_get_chave(ITEM *item){
    if(item == NULL) return 0; //NULL character

    return item->ID;
}

bool item_set_chave(ITEM *item, int chave){
    if(item == NULL) return false;

    item->ID = chave;
    return true;
}

void *item_get_dados (ITEM *item){
    if(item == NULL) return NULL;

    return item->dado;
}
