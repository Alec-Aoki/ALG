#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "AB.h"

struct no_{
  int chave;
  NO *noEsq;
  NO *noDir;
};
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
void no_trocar_max(NO *noTroca, NO *noRaiz, NO *noPai);

struct ab_{
  NO *noRaiz;
  int tamanho;
  //int profundidade;
};
void ab_imprimir_pre(NO *noRaiz);
void ab_imprimir_em(NO *noRaiz);
void ab_imprimir_pos(NO *noRaiz);
void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai);
void ab_busca_no(NO *noRaiz, int chave, bool *pertence);
bool ab_remover_no(NO **noRaiz, int chave);

AB *ab_criar(void){
  AB *arv = (AB *) malloc(sizeof(AB));
  if(arv == NULL) return NULL;

  arv->noRaiz = NULL;
  arv->tamanho = 0;
  //arv->profundidade = -1;

  return arv;
}

void ab_apagar(AB **arv){
  if(*arv == NULL) return;

  no_apagar_recursivo((*arv)->noRaiz);
  free(*arv);
  *arv = NULL;

  return;
}

bool ab_inserir(AB *arv, int elemento, int chavePai, int lado){
  if(arv == NULL) return false;

  NO *noNovo = no_criar(elemento, NULL, NULL);
  if(noNovo == NULL) return false;

  ab_inserir_no(arv->noRaiz, noNovo, lado, chavePai);
  arv->tamanho++;

  return true;
}

void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai){
  if(noRaiz == NULL) return;

  /*PÓS ORDEM*/
  ab_inserir_no(noRaiz->noEsq, noInserir, lado, chavePai);
  ab_inserir_no(noRaiz->noDir, noInserir, lado, chavePai);
  if(chavePai == noRaiz->chave){
    if(lado == ESQ){
      noRaiz->noEsq = noInserir;
    }
    else{
      noRaiz->noDir = noInserir;
    }
  }

  return;
}

bool ab_remover(AB *arv, int chave){
  if(arv == NULL) return false;

  return ab_remover_no(&(arv->noRaiz), chave);
}

/*Casos a serem considerados na remoção:
  1. O nó é folha;
  2. O nó possui uma sub-árvore (esquerda ou direita);
  3. O nó possui duas sub-árvores.
*/

bool ab_remover_no(NO **pontNoRaiz, int chave){
  //Caso base da recursão:
  if(*pontNoRaiz == NULL) return false;

  if((*pontNoRaiz)->chave == chave){
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
    if((*pontNoRaiz)->chave > chave){
      return ab_remover_no((*pontNoRaiz)->noEsq, chave);
    }
    else{
      return ab_remover_no((*pontNoRaiz)->noDir, chave);
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

  noRaiz->chave = noTroca->chave;
  no_apagar(&noTroca);
  return;
}

int ab_busca(AB *arv, int chave){
  if(arv == NULL) return -1;

  bool pertence = false;
  ab_busca_no(arv->noRaiz, chave, &pertence);
  if(pertence) return chave;
  //else:
  return -1;
}

void ab_busca_no(NO *noRaiz, int chave, bool *pertence){
  if(noRaiz == NULL) return;

  /*PÓS ORDEM*/
  ab_busca_no(noRaiz->noEsq, chave, pertence);
  ab_busca_no(noRaiz->noDir, chave, pertence);
  if(noRaiz->chave == chave) *pertence = true;

  return;
}

void ab_imprimir(AB *arv, int ordem){
  if(arv == NULL) return;

  switch(ordem){
    case PRE_ORDEM:{
      ab_imprimir_pre(arv->noRaiz);
      printf("\n");
      break;
    }
    case EM_ORDEM:{
      ab_imprimir_em(arv->noRaiz);
      printf("\n");
      break;
    }
    case POS_ORDEM:{
      ab_imprimir_pos(arv->noRaiz);
      printf("\n");
      break;
    }
    default:{
      return;
    }
  }
}

void ab_imprimir_pre(NO *noRaiz){
  if(noRaiz == NULL) return;

  printf("%d ", noRaiz->chave);
  ab_imprimir_pre(noRaiz->noEsq);
  ab_imprimir_pre(noRaiz->noDir);

  return;
}

void ab_imprimir_em(NO *noRaiz){
  if(noRaiz == NULL) return;

  ab_imprimir_em(noRaiz->noEsq);
  printf("%d ", noRaiz->chave);
  ab_imprimir_em(noRaiz->noDir);

  return;
}

void ab_imprimir_pos(NO *noRaiz){
  if(noRaiz == NULL) return;

  ab_imprimir_pos(noRaiz->noEsq);
  ab_imprimir_pos(noRaiz->noDir);
  printf("%d ", noRaiz->chave);

  return;
}

bool ab_cheia(AB *arv){
  if(arv == NULL) return false;

  NO *noTeste = no_criar(-1, NULL, NULL);
  if(noTeste == NULL) return true;

  no_apagar(&noTeste);
  return true;
}

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  NO *noNovo = (NO *) malloc(sizeof(NO));
  if(noNovo == NULL) return NULL;

  noNovo->chave = chave;
  noNovo->noEsq = noEsq;
  noNovo->noDir = noDir;
  return noNovo;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

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