#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "item.h"

/*writen by claude ai*/

void test_lista_ordenada();
void test_lista_nao_ordenada();

int main(void) {
    printf("Testing ordered list:\n");
    test_lista_ordenada();

    printf("\nTesting unordered list:\n");
    test_lista_nao_ordenada();

    return 0;
}

void test_lista_ordenada() {
    LISTA *lista = lista_criar(true);
    
    // Test lista_vazia and lista_tamanho
    printf("Is empty: %s\n", lista_vazia(lista) ? "true" : "false");
    printf("Size: %d\n", lista_tamanho(lista));

    // Test lista_inserir and lista_imprimir
    for (int i = 5; i > 0; i--) {
        ITEM *item = item_criar(&i, i);
        lista_inserir(lista, item);
    }
    
    printf("After insertion: ");
    lista_imprimir(lista, false);
    
    printf("Is empty: %s\n", lista_vazia(lista) ? "true" : "false");
    printf("Size: %d\n", lista_tamanho(lista));

    // Test lista_busca
    int chave_busca = 3;
    ITEM *item_encontrado = lista_busca(lista, chave_busca);
    if (item_encontrado) {
        printf("Item with key %d found. Data: %d\n", chave_busca, *(int*)item_getDado(item_encontrado));
    } else {
        printf("Item with key %d not found.\n", chave_busca);
    }

    // Test lista_remover
    ITEM *item_removido = lista_remover(lista, 4);
    if (item_removido) {
        printf("Removed item with key %d\n", item_getChave(item_removido));
        item_apagar(&item_removido);
    }
    
    printf("After removal: ");
    lista_imprimir(lista, false);

    // Test lista_cheia
    printf("Is full: %s\n", lista_cheia(lista) ? "true" : "false");

    // Test lista_apagar
    lista_apagar(&lista);
    printf("List deleted\n");
}

void test_lista_nao_ordenada() {
    LISTA *lista = lista_criar(false);
    
    // Test lista_vazia and lista_tamanho
    printf("Is empty: %s\n", lista_vazia(lista) ? "true" : "false");
    printf("Size: %d\n", lista_tamanho(lista));

    // Test lista_inserir and lista_imprimir
    for (int i = 1; i <= 5; i++) {
        ITEM *item = item_criar(&i, i);
        lista_inserir(lista, item);
    }
    
    printf("After insertion: ");
    lista_imprimir(lista, true);
    
    printf("Is empty: %s\n", lista_vazia(lista) ? "true" : "false");
    printf("Size: %d\n", lista_tamanho(lista));

    // Test lista_busca
    int chave_busca = 3;
    ITEM *item_encontrado = lista_busca(lista, chave_busca);
    if (item_encontrado) {
        printf("Item with key %d found. Data: %d\n", chave_busca, *(int*)item_getDado(item_encontrado));
    } else {
        printf("Item with key %d not found.\n", chave_busca);
    }

    // Test lista_remover
    ITEM *item_removido = lista_remover(lista, 2);
    if (item_removido) {
        printf("Removed item with key %d\n", item_getChave(item_removido));
        item_apagar(&item_removido);
    }
    
    printf("After removal: ");
    lista_imprimir(lista, false);

    // Test lista_cheia
    printf("Is full: %s\n", lista_cheia(lista) ? "true" : "false");

    // Test lista_apagar
    lista_apagar(&lista);
    printf("List deleted\n");
}