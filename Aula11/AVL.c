#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "AVL.h"

typedef struct no_{
  int chave;
  NO *noEsq;
  NO *noDir;
  int FB; //Fator de Balanceamento
} NO;

/*Funções auxiliares do nó*/
NO *no_criar(int chave, NO *noEsq, NO *noDir);
void no_apagar(NO **no);
void no_apagar_recursivo(NO *no);
NO *no_rodar_direita(NO *noA);
NO *no_rodar_esquerda(NO *noA);
int no_get_altura(NO *no);
void no_trocar_max(NO *noTroca, NO *noRaiz, NO *noPai);
/*Funções auxiliares do nó*/

struct avl_{
  NO *noRaiz;
  int tamanho; //Quantidade total de nós
};

/*Funções auxiliares da árvore*/
NO *avl_inserir_no(NO *noRaiz, NO *noNovo);
bool avl_remover_no(NO **pontNoRaiz, int chave);
/*Funções auxiliares da árvore*/

AVL *avl_criar(void){
  /*Alocando memória*/
  AVL *avl = (AVL *) malloc(sizeof(AVL));
  if(avl == NULL) return NULL;

  /*Inicializando valores*/
  avl->noRaiz = NULL;
  avl->tamanho = 0;

  return avl;
}

void avl_apagar(AVL **avl){
  if(*avl == NULL) return;

  /*Apagando os nós das árvores*/
  no_apagar_recursivo((*avl)->noRaiz);

  /*Desalocando a memória*/
  free(*avl);
  *avl = NULL;

  return;
}

void no_apagar_recursivo(NO *no){
  /*Caso base*/
  if(no == NULL) return;

  /*Pós-ordem*/
  no_apagar_recursivo(no->noEsq);
  no_apagar_recursivo(no->noDir);

  /*Apaga o nó*/
  no_apagar(&no);
  return;
}

void no_apagar(NO **no){
  if(*no == NULL) return;

  /*Desalocando memória*/
  free(*no);
  *no = NULL;
  return;
}

bool avl_inserir(AVL *avl, int chave){
  /*Erro*/
  if(avl == NULL) return false;

  /*Criando o nó*/
  NO* noNovo = no_criar(chave, NULL, NULL);
  if(noNovo == NULL) return false;

  /*Inserindo o nó na árvore*/
  /*Atribuir o resultado de avl_inserir_no diretamente ao nó raiz poderia quebrar a árvore caso a função retorne NULL. Por causa disso, vamos utilizar o noTemp*/
  NO *noTemp = avl_inserir_no(avl->noRaiz, noNovo);
  if(noTemp == NULL) return false;
  avl->noRaiz = noTemp;

  return true;
}

NO *avl_inserir_no(NO *noRaiz, NO *noNovo){
  /*
  noRaiz == NULL -> a árvore está vazia, devemos inserir
  noNovo == NULL -> o nó foi criado incorretamente, não devemos inserir
  */
  if(noNovo == NULL) return NULL;

  /*Inserindo o nó em pré-ordem, que nem uma ABB*/
  if(noRaiz == NULL) noRaiz = noNovo;
  else if(noNovo->chave < noRaiz->chave) noRaiz->noEsq = avl_inserir_no(noRaiz->noEsq, noNovo);
  else noRaiz->noDir = avl_inserir_no(noRaiz->noDir, noNovo);

  /*Definindo os fatores de balanceamento*/
  noRaiz->FB = no_get_altura(noRaiz->noEsq) - no_get_altura(noRaiz->noDir);

  /*Balanceando, se necessário*/
  if(noRaiz->FB == -2){
    if(noRaiz->noDir->FB <= 0) noRaiz = no_rodar_esquerda(noRaiz); /*Rotação esquerda*/
    else{
      /*Rotação direita esquerda*/
      noRaiz->noDir = no_rodar_direita(noRaiz->noDir);
      noRaiz = no_rodar_esquerda(noRaiz);
    }
  }

  if(noRaiz->FB == 2){
    if(noRaiz->noEsq->FB >= 0) noRaiz = no_rodar_direita(noRaiz); /*Rotação direita*/
    /*Rotação esquerda direita*/
    else{
      noRaiz->noEsq = no_rodar_esquerda(noRaiz->noEsq);
      noRaiz = no_rodar_direita(noRaiz);
    }
  }

  return noRaiz;
}

NO *no_criar(int chave, NO *noEsq, NO *noDir){
  /*Alocando memória*/
  NO *no = (NO *) malloc(sizeof(NO));
  if(no == NULL) return NULL;

  /*Definindo valores iniciais*/
  no->chave = chave;
  no->FB = 0;
  no->noEsq = noEsq;
  no->noDir = noDir;

  return no;
}

int no_get_altura(NO *no){
  int alt = -1;
  if(no == NULL) return alt;

  int altEsq = no_get_altura(no->noEsq);
  int altDir = no_get_altura(no->noDir);
  alt = max(altEsq, altDir);
  alt++;

  return alt;
}

NO *no_rodar_direita(NO *noA){
  /*noA é o nó desbalanceado*/
  NO *noB = noA->noEsq;
  
  /*Rotacionando*/
  noA->noEsq = noB->noDir;
  noB->noDir = noA;

  /*Definindo os fatores de balanceamento
  OBS: Do jeito que fizemos aqui, a complexidade pode ser afetada.
  Podemos evitar isso usando ifs.
  */
  noA->FB = no_get_altura(noA->noEsq) - no_get_altura(noA->noDir);
  noB->FB = no_get_altura(noB->noEsq) - no_get_altura(noB->noDir);

  return noB;
}

NO *no_rodar_esquerda(NO *noA){
  /*noA é o nó desbalanceado*/
  NO *noB = noA->noDir;
  
  /*Rotacionando*/
  noA->noDir = noB->noEsq;
  noB->noEsq = noA;

  /*Definindo os fatores de balanceamento
  OBS: Do jeito que fizemos aqui, a complexidade pode ser afetada.
  Podemos evitar isso usando ifs.
  */  noA->FB = no_get_altura(noA->noEsq) - no_get_altura(noA->noDir);
  noB->FB = no_get_altura(noB->noEsq) - no_get_altura(noB->noDir);

  return noB;
}

int avl_get_altura(AVL *avl){
  if(avl == NULL) return -9999; //ERRO

  return no_get_altura(avl->noRaiz);
}

bool avl_remover(AVL *avl, int chave){
  if(avl == NULL) return false;

  return avl_remover_no(&(avl->noRaiz), chave);
}

//Verificar se isso aqui funciona kk
bool avl_remover_no(NO **pontNoRaiz, int chave){
  /*Casos a serem considerados na remoção:
    1. O nó é folha;
    2. O nó possui uma sub-árvore (esquerda ou direita);
    3. O nó possui duas sub-árvores.
  */
  //Caso base da recursão:
  if(*pontNoRaiz == NULL) return false;

  if((*pontNoRaiz)->chave == chave){
    if(((*pontNoRaiz)->noEsq == NULL) || ((*pontNoRaiz)->noDir == NULL)){
      /*O nó atual tem um ou nenhum filho -> resolve os casos 1 e 2*/

      NO *noRemovido = *pontNoRaiz;
      if((*pontNoRaiz)->noEsq == NULL) *pontNoRaiz = (*pontNoRaiz)->noDir;
      if((*pontNoRaiz)->noDir == NULL) *pontNoRaiz = (*pontNoRaiz)->noEsq;

      no_apagar(&noRemovido);
    }
    else{
      /*O nó atual tem dois filhos -> resolve o caso 3*/

      /*Troca o nó atual pelo nó com a maior chave da sub-árvore
      esquerda em relação ao nó atual*/
      no_trocar_max((*pontNoRaiz)->noEsq, *pontNoRaiz, *pontNoRaiz);
    }
  }
  else if(chave < (*pontNoRaiz)->chave){
    avl_remover_no((*pontNoRaiz)->noEsq, chave);
  }
  else if(chave > (*pontNoRaiz)->chave){
    avl_remover_no((*pontNoRaiz)->noDir, chave);
  }

  if(*pontNoRaiz == NULL) return false;
  //else:
  /*Ajustando o fator de balanceamento*/
  (*pontNoRaiz)->FB = no_get_altura((*pontNoRaiz)->noEsq) - no_get_altura((*pontNoRaiz)->noDir);

  /*Balanceando, se necessário*/
  if((*pontNoRaiz)->FB == -2){
    if((*pontNoRaiz)->noDir->FB <= 0) *pontNoRaiz = no_rodar_esquerda(*pontNoRaiz); /*Rotação esquerda*/
    else{
      /*Rotação direita esquerda*/
      (*pontNoRaiz)->noDir = no_rodar_direita((*pontNoRaiz)->noDir);
      *pontNoRaiz = no_rodar_esquerda(*pontNoRaiz);
    }
  }

  if((*pontNoRaiz)->FB == 2){
    if((*pontNoRaiz)->noEsq->FB >= 0) *pontNoRaiz = no_rodar_direita(*pontNoRaiz); /*Rotação direita*/
    /*Rotação esquerda direita*/
    else{
      (*pontNoRaiz)->noEsq = no_rodar_esquerda((*pontNoRaiz)->noEsq);
      *pontNoRaiz = no_rodar_direita(*pontNoRaiz);
    }
  }

  return true;
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