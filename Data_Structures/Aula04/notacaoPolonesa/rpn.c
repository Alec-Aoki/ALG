#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Pilha.h"
#include "item.h"

float rpn(char *sequencia){
    PILHA *pilha = pilha_criar();

    double *pontChars = (double *)malloc(sizeof(double));
    if(pontChars == NULL) exit(1);

    int contador = 0, quantChars = 0;

    while(sequencia[contador] != '\0'){
        if((sequencia[contador] >= 48) && (sequencia[contador] <= 57)){
            //Salvando o número no vetor pontChars para podermos criar um item com ele
            quantChars++;
            pontChars = (double *)realloc(pontChars, quantChars*sizeof(double));
            if(pontChars == NULL) exit(1);
            pontChars[quantChars-1] = (double)(sequencia[contador] - 48);

            //Criando o item
            ITEM *caractere = item_criar(0, &(pontChars[quantChars-1]));
            pilha_empilhar(pilha, caractere);
        }
        else{
            ITEM *item_n2 = pilha_desempilhar(pilha);
            ITEM *item_n1 = pilha_desempilhar(pilha);
            double *n2 = (double *)item_get_dados(item_n2);
            double *n1 = (double *)item_get_dados(item_n1);
            double n3;

            quantChars++;
            pontChars = (double *)realloc(pontChars, quantChars*sizeof(double));
            if(pontChars == NULL) exit(1);

            switch(sequencia[contador]){
                case 43: //+
                    n3 = (*n1)+(*n2);
                    break;
                case 45: //-
                    n3 = (*n1)-(*n2);
                    break;
                case 42: //*
                    n3 = (*n1)*(*n2);
                    break;
                case 47: ///
                    n3 = (*n1)/(*n2);
                    break;
            }

            pontChars[quantChars-1] = n3;
            ITEM *item_n3 = item_criar(0, &(pontChars[quantChars-1]));
            pilha_empilhar(pilha, item_n3);
        }

        contador++;
    }

    ITEM *itemTemp = pilha_desempilhar(pilha);
    double *resposta = (double *)item_get_dados(itemTemp);

    return ((float)(*resposta));
}