#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ABB.h"

typedef struct no_ NO;

struct no_{
  ITEM *item;
  NO *noEsq;
  NO *noDir;
};

struct abb{
  NO *raiz;
  int tamanho;
};

/*Funções auxiliares*/
NO *buscaBinariaABB(NO *noRaiz, int chave);
NO *inserirABB(NO *noRaiz, NO *noNovo);
void imprimirOrdenada(NO *noRaiz);
NO *no_criar(ITEM *item, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_copiar_recursivo(NO *no);
bool abb_remover_no(NO **pontNoRaiz, int chave);
void no_trocar_max(NO *noTroca, NO *noRaiz, NO *noPai);
void contar_nos(NO *no, int *quantNos);

bool abb_perfeitamente_balanceada(ABB *T){
  if(T == NULL) return !false;
  if(abb_vazia(T)) return !true;

  int quantNosEsq = 0;
  int quantNosDir = 0;

  contar_nos(T->raiz->noEsq, &quantNosEsq);
  contar_nos(T->raiz->noDir, &quantNosDir);

  if((quantNosEsq - quantNosDir == 1) || (quantNosEsq - quantNosDir == -1) || (quantNosEsq - quantNosDir == 0)) return !true;
  return !false;
}

void contar_nos(NO *no, int *quantNos){
  if(no == NULL) return;

  (*quantNos)++;
  contar_nos(no->noEsq, quantNos);
  contar_nos(no->noDir, quantNos);

  return;
}

ABB *abb_criar(void){
  ABB *arvore = (ABB *) malloc(sizeof(ABB));
  if(arvore == NULL) return NULL;

  arvore->raiz = NULL;
  arvore->tamanho = 0;
  return arvore;
}

void abb_apagar(ABB **T){
  if(*T == NULL) return;

  no_apagar_recursivo((*T)->raiz);

  free(*T);
  *T = NULL;
  return;
}

bool abb_inserir(ABB *T, ITEM *item){
  if(T == NULL) return false;

  NO *noNovo = no_criar(item, NULL, NULL);
  if(noNovo == NULL) return false;

  /*inserirABB() explicada mais adiante*/
  T->raiz = inserirABB(T->raiz, noNovo);
  if(T->raiz == NULL) return false;

  T->tamanho++;
  return true;
}

bool abb_remover(ABB *T, int chave){
  if(T == NULL) return false;
  if(T->raiz == NULL) return false;
  if(T->tamanho == 0) return false;

  return abb_remover_no(&(T->raiz), chave);
}

void abb_imprimir(ABB *T){
  if(T == NULL) return;

  imprimirOrdenada(T->raiz);
  printf("\n");

  return;
}

ITEM *abb_busca(ABB *T, int chave){
  if(T == NULL) return NULL;
  if(T->tamanho == 0) return NULL;

  NO *noChave = buscaBinariaABB(T->raiz, chave);
  if(noChave == NULL) return NULL;

  return noChave->item;
}

NO *buscaBinariaABB(NO *noRaiz, int chave){
  if((noRaiz == NULL) || (item_get_chave(noRaiz->item) == chave)){
    return noRaiz;
  }

  if(item_get_chave(noRaiz->item) > chave){
    return buscaBinariaABB(noRaiz->noEsq, chave);
  }
  else{
    return buscaBinariaABB(noRaiz->noDir, chave);
  }
}

NO *inserirABB(NO *noRaiz, NO *noNovo){
  if(noRaiz == NULL){
    return noNovo;
  }

  if(item_get_chave(noRaiz->item) > item_get_chave(noNovo->item)){
    noRaiz->noEsq = inserirABB(noRaiz->noEsq, noNovo); 
  }
  else{
    noRaiz->noDir = inserirABB(noRaiz->noDir, noNovo);
  }

  return noRaiz;
}

void imprimirOrdenada(NO *noRaiz){
  if(noRaiz != NULL){
    imprimirOrdenada(noRaiz->noEsq);
    printf("%d ", item_get_chave(noRaiz->item));
    imprimirOrdenada(noRaiz->noDir);
  }

  return;
}

NO *no_criar(ITEM *item, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL) return NULL;

  noNovo->item = item;
  noNovo->noEsq = noEsq;
  noNovo->noDir = noDir;
  return noNovo;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

  item_apagar(&((*no)->item));
  free(*no);
  *no = NULL;
  return;
}

void no_apagar_recursivo(NO *no){
  if(no == NULL) return;

  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);
  no_apagar(&no);

  return;
}

bool abb_vazia(ABB *T){
  if(T == NULL) return true;
  if(T->raiz == NULL) return true;
  if(T->tamanho == 0) return true;

  return false;
}

bool abb_remover_no(NO **pontNoRaiz, int chave){
  //Caso base da recursão:
  if(*pontNoRaiz == NULL) return false;

  if(item_get_chave((*pontNoRaiz)->item) == chave){
    if(((*pontNoRaiz)->noEsq == NULL) || ((*pontNoRaiz)->noDir == NULL)){
      /*O nó atual tem um ou nenhum filho -> resolve os casos 1 e 2*/

      NO *noRemovido = *pontNoRaiz;
      if((*pontNoRaiz)->noEsq == NULL) *pontNoRaiz = (*pontNoRaiz)->noDir;
      if((*pontNoRaiz)->noDir == NULL) *pontNoRaiz = (*pontNoRaiz)->noEsq;

      no_apagar(&noRemovido);
      return true;
    }
    else{
      /*O nó atual tem dois filhos -> resolve o caso 3*/

      /*Troca o nó atual pelo nó com a maior chave da sub-árvore
      esquerda em relação ao nó atual*/
      no_trocar_max((*pontNoRaiz)->noEsq, *pontNoRaiz, *pontNoRaiz);
      return true;
    }
  }
  else{
    if(item_get_chave((*pontNoRaiz)->item) > chave){
      return abb_remover_no(&(*pontNoRaiz)->noEsq, chave);
    }
    else{
      return abb_remover_no(&(*pontNoRaiz)->noDir, chave);
    }
  }
}

void no_trocar_max(NO *noTroca, NO *noRaiz, NO *noPai){
  if(noTroca->noDir != NULL){
    /*Achando o máximo nó folha direito possível*/
    no_trocar_max(noTroca->noDir, noRaiz, noTroca);
    return;
  }

  if(noRaiz == noPai) noPai->noEsq = noTroca->noEsq;
  else noPai->noDir = noTroca->noEsq;

  item_set_chave(noRaiz->item, item_get_chave(noTroca->item));
  no_apagar(&noTroca);
  return;
}