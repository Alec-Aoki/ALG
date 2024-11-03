#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

struct lista_ {
  int vet[TAM_MAX];
  int tamanho;
};

int buscaBinariaLista(int v[], int inicio, int fim, int chave);

LISTA *lista_criar(void){
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  if(lista == NULL) return NULL;

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
  if(lista == NULL) return false;
  if(lista->tamanho > TAM_MAX) return false;

  /*Percorremos o vetor até encontrarmos o primeiro
  elemento maior que o elemento a ser inserido*/
  int i = 0;
  while((i < lista->tamanho) && (lista->vet[i] < elemento)) i++;
  /*Se o elemento já existe na lista, ele não é inserido*/
  if(lista_busca(lista, elemento) == elemento) return false;

  /*Deslocamos parte do vetor para a direita (a partir da
  posição correta), abrindo espaço para o elemento ser inserido*/
  for(int j = lista->tamanho; j > i; j--){
    lista->vet[j] = lista->vet[j-1];
  }
  lista->vet[i] = elemento;
  lista->tamanho++;

  return true;
}

int lista_remover(LISTA *lista){
  if(lista == NULL) return ERRO;
  if(lista->tamanho == 0) return ERRO;

  int elemRemovido = lista->vet[lista->tamanho - 1];
  /*Ao remover, substituimos o elemento por ERRO*/
  lista->vet[lista->tamanho - 1] = ERRO;
  lista->tamanho--;

  return elemRemovido;
}

void lista_imprimir(LISTA *lista){
  if(lista == NULL) return;

  for(int i = 0; i < lista->tamanho; i++){
    /*Devido à forma como removemos, checamos o elemento
    para não imprimirmos itens removidos*/
    if(lista->vet[i] != ERRO) printf("%d ", lista->vet[i]);
  }
  printf("\n");

  return;
}

/*Retorna a chave se ela foi encontrada, ERRO senão*/
int lista_busca(LISTA *lista, int chave){
  if(lista == NULL) return ERRO;
  if(lista->tamanho == 0) return ERRO;

  if(buscaBinariaLista(lista->vet, 0, lista->tamanho - 1, chave) != ERRO) return chave;
  return ERRO;
}

LISTA *lista_copiar(LISTA *lista){
  if(lista == NULL) return NULL;

  LISTA *listaCopia = lista_criar();
  if(listaCopia == NULL) return NULL;

  for(int i = 0; i < lista->tamanho; i++){
    listaCopia->vet[i] = lista->vet[i];
  }

  return listaCopia;
}

/*Retorna a posição do elemento em que ele foi encontrado (ERRO se não foi)*/
int buscaBinariaLista(int v[], int inicio, int fim, int chave){
  if(inicio > fim) return ERRO;

  int meio = (inicio + fim) / 2;

  if(v[meio] == chave) return meio;
  else if(chave < v[meio]) return buscaBinariaLista(v, inicio, meio - 1, chave);
  else{
    return buscaBinariaLista(v, meio + 1, fim, chave);
  }
}