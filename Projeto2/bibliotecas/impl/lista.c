#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

struct lista_ {
  int vet[TAM_MAX];
  int tamanho;
};

LISTA *lista_criar(void){
  LISTA *listaNova = (LISTA *) malloc(sizeof(LISTA));
  if(listaNova == NULL){
    printf("Erro em lista_criar: listaNova == NULL\n");
    return NULL;
  }

  listaNova->tamanho = 0;
  return listaNova;
}

void lista_apagar(LISTA **lista){
  if(*lista == NULL) return;

  free(*lista);
  *lista = NULL;
  return;
}