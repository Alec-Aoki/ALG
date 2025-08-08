#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "lista.h"

struct lista_{
    ITEM *item[TAM_MAX]; //vetor de ponteiros que apontam para itens
    int inicio;
    int fim; //indica próxima posição livre para inserir o item
    //int tamanho;
    bool ordenada;
};

bool lista_inserir_fim(LISTA *lista, ITEM *item);
bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao);
int lista_busca_sequencial(LISTA *lista, int chave);
int busca_binaria(LISTA *lista, int inicio, int fim, int chave);

LISTA *lista_criar(void){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    
    if(lista != NULL){
        lista->inicio = 0;
        lista->fim = 0;
        //lista->tamanho = 0;
        lista->ordenada = true; //OBS: ordenação em ordem crescente!
    }

    return lista;
}

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    if(!lista->ordenada){
        return lista_inserir_fim(lista, item);
    }
    else{
        int posicao = busca_binaria(lista, lista->inicio, lista->fim-1, item_get_chave(item));
        
        return lista_inserir_posicao(lista, item, posicao);
    }
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    lista->item[lista->fim] = item;
    lista->fim++;
    //lista->tamanho++;

    return true;
}

bool lista_inserir_posicao(LISTA *lista, ITEM *item, int posicao){
    if(lista == NULL) return false;
    if(lista_cheia(lista)) return false;

    /*shiftando todos os elementos da lista para a direita, abrindo espaço pro novo item*/
    for(int i = (lista->fim)-1; i >= posicao; i--){
        lista->item[i+1] = lista->item[i];
    }

    lista->item[posicao] = item;
    lista->fim++;
    //lista->tamanho++;

    return true;
}

int lista_busca_sequencial(LISTA *lista, int chave){
    if(lista == NULL) return -1;

    for(int i=0; i<lista->fim; i++){
        if(item_get_chave(lista->item[i]) == chave) return i;
    }

    return -1;
}

int busca_binaria(LISTA *lista, int inicio, int fim, int chave){
    if(lista == NULL);
    if(fim == -1) return 0;

    while(inicio < fim){
        int meio=(inicio+fim)/2;
        
        if(chave <= item_get_chave(lista->item[meio])) fim = meio;
        else{
            inicio = meio+1;
        }
    }

    if(item_get_chave(lista->item[inicio]) >= chave) return inicio;
    else{
        return fim+1;
    }
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) return -1;

    return lista->fim;
}

bool lista_vazia(LISTA *lista){
    if(lista == NULL) return true;
    if(lista->fim == lista->inicio) return true;
    
    return false;
}

bool lista_cheia(LISTA *lista){
    if(lista == NULL) return false;
    if(lista->fim == TAM_MAX) return true;
    
    return false;
}

void lista_imprimir(LISTA *lista){
    if(lista == NULL) return;

    for(int i=0; i<(lista->fim-1); i++){
        printf("%d ", item_get_chave(lista->item[i]));
    }
    printf("%d\n", item_get_chave(lista->item[lista->fim-1]));
}