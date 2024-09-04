#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Deque.h"

int main(void){
    ITEM *item1 = item_criar(0, NULL);
    ITEM *item2 = item_criar(1, NULL);

    DEQUE *deque = deque_criar();

    deque_inserir_inicio(deque, item1);
    deque_inserir_fim(deque, item2);

    int chaveInicio = item_get_chave(deque_primeiro(deque));
    printf("%d\n", chaveInicio);

    int chaveFim = item_get_chave(deque_ultimo(deque));
    printf("%d\n", chaveFim);

    return 0;
}