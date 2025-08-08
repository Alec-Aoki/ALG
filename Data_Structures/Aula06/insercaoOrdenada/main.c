#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

int main(void){
    LISTA *lista = lista_criar();

    int quantItens;
    scanf("%d", &quantItens);

    int n;
    for(int i=0; i<quantItens; i++){
        scanf("%d", &n);
        ITEM *item = item_criar(n, NULL);
        lista_inserir(lista, item);
    }

    lista_imprimir(lista);

    return 0;
}