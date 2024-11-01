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
  if((TAD != TAD_LISTA) || (TAD != TAD_ARVORE)) return NULL;

  CONJUNTO *conjunto = (CONJUNTO *) malloc(sizeof(CONJUNTO));
  if(conjunto == NULL) return NULL;

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

bool conjunto_inserir(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    Lista_Inserir(conj->conjuntoLista, elemento);
  }
  else{
    heapmax_inserir(conj->conjuntoHeap, elemento);
  }

  conj->tamanho++;
  return true;
}

int conjunto_remover(CONJUNTO *conj){
  if(conj == NULL) return ERRO;

  int elementoRemovido;
  if(conj->TAD == TAD_LISTA){
    elementoRemovido =  Lista_Remover(conj->conjuntoLista);
  }
  else{
    elementoRemovido = heapmax_remover(conj->conjuntoHeap);
  }

  conj->tamanho--;
  return elementoRemovido;
}

void conjunto_imprimir(CONJUNTO *conj){
  if(conj == NULL) return;

  if(conj->TAD == TAD_LISTA){
    Lista_Imprimir(conj->conjuntoLista);
  }
  else{
    heapmax_imprimir(conj->conjuntoHeap);
  }

  return;
}

bool conjunto_pertence(CONJUNTO *conj, int elemento){
  if(conj == NULL) return false;

  if(conj->TAD == TAD_LISTA){
    return busca_binaria(conj->conjuntoLista, elemento);
  }
  else{
    if (elemento == buscaBinaria(conj->conjuntoHeap, 0, conj->tamanho-1, elemento)) return true;
  }

  return false;
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjA, CONJUNTO *conjB){
  if((conjA == NULL) || (conjB == NULL)) return NULL;

  CONJUNTO *conjUniao = conjunto_criar(conjA->TAD);

  if(conjUniao->TAD == TAD_LISTA){
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = Lista_Remover(conjA->conjuntoLista);
      conjunto_inserir(conjUniao, elemento);
      conjUniao->tamanho++;
    }

    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = Lista_Remover(conjA->conjuntoLista);

      if(!busca_binaria(conjUniao->conjuntoLista, elemento)){
        conjunto_inserir(conjUniao, elemento);
        conjUniao->tamanho++;
      }
    }
  }

  if(conjUniao->TAD == TAD_ARVORE){
    for(int i = 0; i < conjA->tamanho; i++){
      int elemento = heapmax_remover(conjA->conjuntoLista);
      conjunto_inserir(conjUniao, elemento);
      conjUniao->tamanho++;
    }
    
    for(int i = 0; i < conjB->tamanho; i++){
      int elemento = heapmax_remover(conjA->conjuntoLista);

      if(buscaBinaria(conjUniao->conjuntoHeap, 0, conjUniao->tamanho - 1, elemento) == ERRO){
        conjunto_inserir(conjUniao, elemento);
        conjUniao->tamanho++;
      }
    }
  }

  return conjUniao;
}