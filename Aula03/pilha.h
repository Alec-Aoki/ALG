#ifndef PILHA_H
    #define PILHA_H

    typedef struct pilha_ PILHA;

    PILHA *pilha_criar(void);
    void pilha_apagar(PILHA **pilha);
    bool pilha_empilhar(PILHA *pilha, ITEM *item);
    ITEM *pilha_desempilhar(PILHA *pilha);
    ITEM *pilha_topo(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    bool pilha_vazia(PILHA *pilha);
    bool pilha_cheia(PILHA *pilha);
#endif