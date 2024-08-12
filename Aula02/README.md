#Tipos Abstratos de Dados (II)

##Estrutura de **Dados**
- organizar
- armazenar
- processar
-> implementada por meio de um TAD

##TAD
- DADOS
    - inacessíveis ao cliente
- FUNÇÕES
    - alterar
    - setar
    - imprimir
    - apagar
    - processar
    -> devem ser independentes do tipo de dado que vai ser utilizado
        -> ITEM
###ITEM
- o cliente que escolhe o tipo de dado na main
- a ED usará um item (abstração) e não dependerá do tipo de dado utilizado
- o cliente pode declarar um float, int, array etc. e a ED funcionará sem precisar ser alterada

##Arquivo item.h
```c
#ifndef ITEM_H //if not defined, para não incluir a biblioteca dnv se ela já tiver sido definida
    #define ITEM_H

    #include <stdbool.h>

    typedef struct item_ ITEM;

    ITEM *item_criar(int chave, void *comp);
#endif
```

##Arquivo item.c
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

//exemplo de função no TAD
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
```