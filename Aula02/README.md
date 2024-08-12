# Tipos Abstratos de Dados (II)

## Estrutura de **Dados**
- organizar
- armazenar
- processar
- implementada por meio de um TAD

## TAD
- DADOS
    - inacessíveis ao cliente
- FUNÇÕES
    - alterar
    - setar
    - imprimir
    - apagar
    - processar
    - devem ser independentes do tipo de dado que vai ser utilizado
        - ITEM

### ITEM
- o cliente que escolhe o tipo de dado na main
- a ED usará um item (abstração) e não dependerá do tipo de dado utilizado
- o cliente pode declarar um float, int, array etc. e a ED funcionará sem precisar ser alterada

## Arquivo item.h
```c
#ifndef ITEM_H //if not defined, para não incluir a biblioteca dnv se ela já tiver sido definida
    #define ITEM_H

    #include <stdbool.h>

    typedef struct item_ ITEM;

    ITEM *item_criar(int chave, void *comp); //cria o dado
    bool item_apagar (ITEM **item); //apaga o dado
    int item_get_chave (ITEM *item); //pega o identificador
    bool item_set_chave (ITEM *item); //define uma informação (o identificador) sobre o daod
    void *item_get_dados (ITEM *item); //pega uma informação sobre o dado
#endif
```

## Arquivo item.c
```c
#include <stdlib.h>
#include <stdio.h>
#include <item.h>

struct item_{
    int chave; //indexador (identificador)
    void *dados; //ponteiro para o dado
    //ponteiro void, faz a conversão automática de tipos!
}
//OBS: a struct está dentro do item.c para o cliente não acessá-la

//exemplos de funções no TAD:
ITEM *item_criar(int chave, void *dado){
    ITEM *item;
    item = (ITEM *)malloc(sizeof(ITEM));

    if(item != NULL){
        item->chave = chave;
        item->dados = dado;
        return(item);
    }
    return(NULL);
}

bool item_apagar(ITEM **item){
    if(*item != NULL){
        free(*item);
        *item = NULL;
        return(true);
    }
    return(false);
}

int item_get_chave(ITEM *item, int chave){
    if(item != NULL)
        return(item->chave);
    return(NULL);
}

bool int_set_chave(ITEM *item, int chave){
    if(item != NULL){
        item->chave = chave;
        return(true);
    }
    return false;
}

void item_get_dados (ITEM *item){
    if(item != NULL)
        return(item->dados);
    return(NULL);
}
```