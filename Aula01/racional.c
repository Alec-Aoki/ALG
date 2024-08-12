#include <stdlib.h>
#include <stdio.h>
#include "racional.h"

struct racional_{
    int numerador;
    int denominador;
};

RACIONAL *racional_crie(int numerador, int denominador){
    if(denominador == 0){
        exit(1);
    }

    RACIONAL *racional;
    racional = (RACIONAL *)malloc(1*sizeof(RACIONAL));
    if (racional == NULL){
        exit(1);
    }

    racional->numerador = numerador;
    racional->denominador = denominador;

    return racional;
}

void racional_apague(RACIONAL *racional){
    if(racional != NULL){
        free(racional);
    }
    return;
}

RACIONAL *racional_multiplique(RACIONAL *r1, RACIONAL *r2){
    if((r1 == NULL) && (r2 == NULL)){
        return NULL;
    }
    
    RACIONAL *r3;
    r3->numerador = (r1->numerador)*(r2->numerador);
    r3->denominador = (r1->denominador)*(r2->denominador);
    
    return r3;
}

void racional_imprima(RACIONAL *racional){
    printf("%d/%d", racional->numerador, racional->denominador);
}
