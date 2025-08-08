#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Pilha.h"

bool balanceada(char *sequencia){
    //*sequencia é um ponteiro que aponta para a string

    PILHA *pilhaAbertos = pilha_criar();
    if(pilhaAbertos == NULL) exit(1);
    int contador=0;

    while(sequencia[contador] != '\0'){

        if((sequencia[contador] == '{') || (sequencia[contador] == '(') || (sequencia[contador] == '[')){
            pilha_empilhar(pilhaAbertos, item_criar(contador, &sequencia[contador]));
        }

        else{
            if(pilha_vazia(pilhaAbertos)) return false;

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '('){
                if(sequencia[contador] != ')') return false;
            }

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '{'){
                if(sequencia[contador] != '}') return false;
            }

            else if(*(char *)item_get_dados(pilha_topo(pilhaAbertos)) == '['){
                if(sequencia[contador] != ']') return false;
            }

            pilha_desempilhar(pilhaAbertos);
        }

        contador++;
    }

    if(pilha_vazia(pilhaAbertos)){
        return true;
    }
    else{
        return false;
    }
}