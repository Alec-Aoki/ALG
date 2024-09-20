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
int lista_busca_ordenada(LISTA *lista, int chave);
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

    printf("Item a ser inserido: %d\n", item_get_chave(item));

    if(!lista->ordenada){
        printf("Inserindo fim\n");
        return lista_inserir_fim(lista, item);
    }
    else{
        int posicao = lista_busca_ordenada(lista, item_get_chave(item));
        printf("Posicao onde inserir: %d\n", posicao);
        
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
    if(posicao <= (lista->fim)-1){
        for(int i = (lista->fim)-1; i >= posicao; i--){
            lista->item[i+1] = lista->item[i];
        }
    }

    lista->item[posicao] = item;
    lista->fim++;
    //lista->tamanho++;

    printf("Item inserido: %d\n", item_get_chave(item));

    return true;
}

int lista_busca_sequencial(LISTA *lista, int chave){
    if(lista == NULL) return -1;

    for(int i=0; i<lista->fim; i++){
        if(item_get_chave(lista->item[i]) == chave) return i;
    }

    return -3;
}

int lista_busca_ordenada(LISTA *lista, int chave){
    if(lista == NULL){
        return -4;
    }

    return busca_binaria(lista, lista->inicio, lista->fim-1, chave);
}

int busca_binaria(LISTA *lista, int inicio, int fim, int chave){
    int meio = (inicio + fim)/2;
    if(lista->item[meio] == NULL){
        return 0;
    }
    
    int chaveMeio = item_get_chave(lista->item[meio]);

    if((chave > chaveMeio) && (chave <= item_get_chave(lista->item[fim]))){
        if(chave < item_get_chave(lista->item[meio+1])){
            return meio+1;
        }
        printf("Maior\n");
        return busca_binaria(lista, meio+1, fim, chave);
    }
    else if ((chave < chaveMeio) && (chave >= item_get_chave(lista->item[inicio]))){
        if(chave > item_get_chave(lista->item[meio-1])){
            return meio-1;
        }
        printf("Menor\n");
        return busca_binaria(lista, inicio, meio-1, chave);
    }
    else{
        return fim+1;
    }
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) return -6;

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
        printf("[%d]; ", item_get_chave(lista->item[i]));
    }
    printf("[%d];\n", item_get_chave(lista->item[lista->fim-1]));
}