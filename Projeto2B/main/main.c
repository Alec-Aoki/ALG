#include <stdio.h>
#include <stdlib.h>

#include "../bibliotecas/lista.h"
#include "../bibliotecas/heapmax.h"

#define LISTA 0
#define ARVORE 1

int main(void){
  int TAD;
  scanf("%d", &TAD);

  if(TAD == LISTA){

  }
  else if(TAD == ARVORE){

  }
  else{
    printf("Digite 0 para lista e 1 para árvore\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}