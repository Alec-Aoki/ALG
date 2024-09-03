#ifndef FILADINAMICA_H
    #define FILADINAMICA_H

    typedef struct fila_ FILA;
    typedef struct no_ NO;
    
    #include "item.h"

    FILA *fila_criar(void);
    bool fila_inserir(FILA *fila, ITEM *item);
    ITEM *fila_remover(FILA *fila);
    ITEM *fila_frente(FILA *fila);
    int fila_tamanho(FILA *fila);
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
#endif