#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"
#include "../heapmax.h"
#include "../conjunto.h"

struct conjunto_{
  int TAD;
  LISTA *conjuntoLista;
  HEAPMAX *conjuntoHeap;
  int tamanho;
};

CONJUNTO *conjunto_criar(int TAD){
  if((TAD != TAD_LISTA) || (TAD != TAD_ARVORE)){
    printf("TAD inválido\n");
    return NULL;
  }

  CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO));
  if(conjunto == NULL){
    printf("Erro em conjunto_criar: conjunto == NULL\n");
    return NULL;
  }

  conjunto->TAD = TAD;
  conjunto->tamanho = 0;
  if(TAD == TAD_LISTA){
    conjunto->conjuntoLista = Lista_Criar();
    conjunto->conjuntoHeap = NULL;
  }
  else if(TAD == TAD_ARVORE){
    conjunto->conjuntoHeap = heapmax_criar();
    conjunto->conjuntoLista = NULL;
  }

  return conjunto;
}

bool conjunto_apagar(CONJUNTO **conj){
  if(*conj == NULL) return true;

  if((*conj)->TAD == TAD_LISTA){
    Lista_Apagar(&((*conj)->conjuntoLista));
  }
  else{
    heapmax_apagar(&((*conj)->conjuntoHeap));
  }

  free(*conj);
  *conj = NULL;

  return true;
}