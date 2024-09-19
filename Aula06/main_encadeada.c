#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

int main(int argc, char *argv[]){
    
    LISTA *lista;
    ITEM *item;
    
    lista = lista_criar(false);
    printf("Lista criada\n");
        
    lista_inserir(lista, item_criar(NULL, 1));
    printf("Item 1 inserido\n");
    lista_inserir(lista, item_criar(NULL, 2));
    printf("Item 2 inserido\n"); 
    lista_inserir(lista, item_criar(NULL, 8));
    printf("Item 3 inserido\n");
    lista_inserir(lista, item_criar(NULL, 12));
    printf("Item 4 inserido\n");
    lista_inserir(lista, item_criar(NULL, 18));
    printf("Item 5 inserido\n");

    item = lista_remover(lista, 12); // remove no do meio da lista
    printf("Item 4 removido\n");
    item_apagar(&item); //apaga o item retornado. responsabilidade do chamado em vez de ser ser lista_remover(); decisão de projeto
    //lista_imprimir(lista);
    
    item = lista_remover(lista, 111); //remove 1o item da lista
    printf("Item inexistente\n");
    item_apagar(&item);
   // lista_imprimir(lista);

        
    //lista_apagar(&lista);
    //lista_imprimir(lista);
   	
    return (0);
}


