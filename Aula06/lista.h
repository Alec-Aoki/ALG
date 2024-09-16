#ifndef LISTA_H
    #define LISTA_H
    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenacao);
    bool lista_inserir(LISTA *lista, ITEM *item);
    ITEM *item_remover(LISTA *lista, ITEM *item);
    ITEM *lista_busca(LISTA *lista, ITEM *item);
    bool lista_apagar(LISTA **lista);
#endif