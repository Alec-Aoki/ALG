#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"

#define LISTA 0
#define ARVORE 1
#define PERTENCE 1

int main(void) {
    int TAD, tamConjA, tamConjB, op, elemPertence;
    
    scanf("%d %d %d", &TAD, &tamConjA, &tamConjB);
    int conjA[tamConjA], conjB[tamConjB]; //100% proibido mano

    /*Lendo os elementos*/
    for(int i = 0; i < tamConjA; i++){
        scanf("%d", &conjA[i]);   
    }
    for(int i = 0; i < tamConjB; i++){ 
        scanf("%d", &conjB[i]);
    }

    scanf("%d", &op);
    if(op == PERTENCE){
        scanf("%d", &elemPertence);
    }

    if(TAD == LISTA){
        switch(op){
            case 1:
                conjunto_listaPertence(conjA, tamConjA, elemPertence);
                break;
            case 2:
                conjunto_listaUniao(conjA, tamConjA, conjB, tamConjB);
                break;
            case 3:
                conjunto_listaIntersec(conjA, tamConjA, conjB, tamConjB);
                break;
            default:
                printf("Comando inválido!\n");
                return EXIT_FAILURE;
        }

    }
    else if(TAD == ARVORE){
        switch(op){
            case 1:
                conjunto_arvPertence(conjA, tamConjA, elemPertence);
                break;
            case 2:
                conjunto_arvUniao(conjA, tamConjA, conjB, tamConjB);
                break;
            case 3:
                conjunto_arvIntersec(conjA, tamConjA, conjB, tamConjB);
                break;
            default:
                printf("Comando inválido!\n"); 
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
