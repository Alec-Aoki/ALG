#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "AB.h"

typedef struct no_ NO;
struct no_{
  int chave;
  NO *noEsq;
  NO *noDir;
};
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_copiar_recursivo(NO *no);

struct ab_{
  NO *noRaiz;
  int profund;
  int tam; //quantidade total de nós
};

void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai);
void ab_preordem(NO *noRaiz);
void ab_emordem(NO *noRaiz);
void ab_posordem(NO *noRaiz);

AB *ab_criar(void){
  AB *ab = (AB *) malloc(sizeof(AB));
  if(ab != NULL){
    ab->noRaiz = NULL;
    ab->profund = -1;
    ab->tam = 0;
  }

  return ab;
}

void ab_apagar(AB **arv){
  if(*arv != NULL){
    no_apagar_recursivo((*arv)->noRaiz);
    free(*arv);
    *arv = NULL;
  }

  return;
}

bool ab_inserir(AB *arv, int elemento);
int ab_remover(AB *arv);

void ab_imprimir(AB *arv, int ordem){
  if(arv == NULL) return;

  switch(ordem){
    case PRE_ORDEM:{
      ab_preordem(arv->noRaiz);
      break;
    }
    case EM_ORDEM:{
      ab_emordem(arv->noRaiz);
      break;
    }
    case POS_ORDEM:{
      ab_posordem(arv->noRaiz);
      break;
    }
  }
}

int ab_busca(AB *arv, int chave);

AB *ab_copiar(AB *arv){
  if(arv == NULL) return NULL;

  AB *arvCopia = ab_criar();
  if(arvCopia == NULL) return NULL;

  arvCopia->noRaiz = no_copiar_recursivo(arv->noRaiz);
  arvCopia->tam = arv->tam;
  arvCopia->profund = arv->profund;

  return arvCopia;
}

bool ab_cheia(AB *arv){
  if(arv == NULL) return false;
  AB *arvTeste = ab_criar();
  if(arvTeste != NULL){
    ab_apagar(arvTeste);
    return true;
  }
  return false;
}

void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai){
  if(noRaiz == NULL) return;

  ab_inserir_no(noRaiz->noEsq, noInserir, lado, chavePai);
  ab_inserir_no(noRaiz->noDir, noInserir, lado, chavePai);

  if(chavePai == noRaiz->chave){
    if(lado == ESQ) noRaiz->noEsq = noInserir;
    else if(lado == DIR) noRaiz->noDir = noInserir;
  }

  return;
}

void ab_preordem(NO *noRaiz){
  if(noRaiz != NULL){
    printf("%d ", noRaiz->chave);
    ab_preordem(noRaiz->noEsq);
    ab_preordem(noRaiz->noDir);
  }
  return;
}

void ab_emordem(NO *noRaiz){
  if(noRaiz != NULL){
    ab_emordem(noRaiz->noEsq);
    printf("%d ", noRaiz->chave);
    ab_emordem(noRaiz->noDir);
  }
  return;
}

void ab_posordem(NO *noRaiz){
  if(noRaiz != NULL){
    ab_posordem(noRaiz->noEsq);
    ab_posordem(noRaiz->noDir);
    printf("%d ", noRaiz->chave);
  }
  return;
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
NO *no_copiar_recursivo(NO *no){
  if(no == NULL) return NULL;

  NO *noNovo = no_criar(no->chave, NULL, NULL);
  if(noNovo == NULL) return NULL;

  noNovo->noEsq = no_copiar_recursivo(no->noEsq);
  noNovo->noDir = no_copiar_recursivo(no->noDir);

  return noNovo;
}