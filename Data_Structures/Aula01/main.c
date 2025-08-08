#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

int main(void){
    RACIONAL *r1, *r2;
    r1 = racional_crie(2, 3);
    r2 = racional_crie(3, 4);

    RACIONAL *r3 = (RACIONAL *)racional_multiplique(r1, r2);
    if(r3 == NULL){
        exit(1);
    }

    racional_imprima(r3);
    printf("\n");

    racional_apague(r1);
    racional_apague(r2);
    racional_apague(r3);

    return 0;
}