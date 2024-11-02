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

  
}