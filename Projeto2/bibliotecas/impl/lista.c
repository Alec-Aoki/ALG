#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

struct lista_ {
  int vet[TAM_MAX];
  int tamanho;
};

LISTA *lista_criar(void){
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  if(lista == NULL){
    printf("Erro em lista_criar: lista == NULL\n");
    return NULL;
  }

  lista->tamanho = 0;
  return lista;
}

void lista_apagar(LISTA **lista){
  if(*lista == NULL) return;

  free(*lista);
  *lista = NULL;
  return;
}

bool lista_inserir(LISTA *lista, int elemento){
  if(lista == NULL){
    printf("Erro em lista_inserir: lista == NULL\n");
    return false;
  }

  int i = 0;
  while(lista->vet[i] > elemento) i++;

  for(int j = lista->tamanho; j > i; j--){
    lista->vet[j] = lista->vet[j-1];
  }
  lista->vet[i] = elemento;
  lista->tamanho++;

  return true;
}

int lista_remover(LISTA *lista){
  if(lista == NULL){
    printf("Erro em lista_remover: lista == NULL\n");
    return ERRO;
  }

  int elemRemovido = lista->vet[lista->tamanho - 1];
  lista->vet[lista->tamanho - 1] = ERRO;
  lista->tamanho--;

  return elemRemovido;
}

void lista_imprimir(LISTA *lista){
  if(lista == NULL){
    printf("Erro em lista_imprimir: lista == NULL\n");
    return;
  }

  for(int i = 0; i < lista->tamanho; i++){
    printf("%d ", lista->vet[i]);
  }
  printf("\n");

  return;
}

int lista_busca(LISTA *lista, int chave){
  if(lista == NULL){
    printf("Erro em lista_busca: lista == NULL\n");
    return ERRO;
  }

  return buscaBinaria(lista->vet, 0, lista->tamanho - 1, chave);
}