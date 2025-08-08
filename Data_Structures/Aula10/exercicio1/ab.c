#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ab.h"

typedef struct no_ NO;
struct no_{
  ITEM *item;
  NO *noEsq;
  NO *noDir;
};
NO *no_criar(ITEM *item, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);

struct arv_bin{
  NO *noRaiz;
  int tamanho;
};
void ab_imprimir_pos(NO *noRaiz);
void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai);
void ab_checar_filhos(NO *noRaiz, bool *binaria);

int ab_estritamente_binaria (AB *T){
  if(T == NULL) return ERRO;

  bool estrtBin = true;
  ab_checar_filhos(T->noRaiz, &estrtBin);

  if(estrtBin) return 0;
  //else:
  return 1;
}

void ab_checar_filhos(NO *noRaiz, bool *binaria){
  if(noRaiz == NULL) return;

  int quantFilhos = 0;

  ab_checar_filhos(noRaiz->noEsq, binaria);
  ab_checar_filhos(noRaiz->noDir, binaria);


  if(noRaiz->noEsq == NULL) quantFilhos++;
  if(noRaiz->noDir == NULL) quantFilhos++;

  if((quantFilhos != 0) && (quantFilhos != 2)) *binaria = false;

  return;
}

AB *ab_criar(void){
  AB *arv = (AB *) malloc(sizeof(AB));
  if(arv == NULL) return NULL;

  arv->noRaiz = NULL;
  arv->tamanho = 0;

  return arv;
}

bool ab_inserir (AB *T, ITEM *item, int lado, int chave){
  if((T == NULL) || (item == NULL)) return false;

  NO *noNovo = no_criar(item, NULL, NULL);
  if(noNovo == NULL) return false;

  if(T->tamanho == 0){
    T->noRaiz = noNovo;
  }
  else{
    ab_inserir_no(T->noRaiz, noNovo, lado, chave);
  }
  T->tamanho++;

  return true;
}

void ab_inserir_no(NO *noRaiz, NO *noInserir, int lado, int chavePai){
  if(noRaiz == NULL) return;

  /*PÓS ORDEM*/
  ab_inserir_no(noRaiz->noEsq, noInserir, lado, chavePai);
  ab_inserir_no(noRaiz->noDir, noInserir, lado, chavePai);
  if(chavePai == item_get_chave(noRaiz->item)){
    if(lado == FILHO_ESQ){
      noRaiz->noEsq = noInserir;
    }
    else{
      noRaiz->noDir = noInserir;
    }
  }

  return;
}


void ab_imprimir (AB *T){
  if(T == NULL) return;

  ab_imprimir_pos(T->noRaiz);
  printf("\n");

  return;
}

void ab_imprimir_pos(NO *noRaiz){
  if(noRaiz == NULL) return;

  ab_imprimir_pos(noRaiz->noEsq);
  ab_imprimir_pos(noRaiz->noDir);
  printf("%d ", item_get_chave(noRaiz->item));

  return;
}

void ab_apagar_arvore(AB **T){
  if(*T == NULL) return;

  no_apagar_recursivo((*T)->noRaiz);
  free(*T);
  *T = NULL;

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