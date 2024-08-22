#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "Pilha.h"

/*
-> criar duas pilhas
    -> aberta: recebe as coisinhas abertas
    -> fechada: recebe as coisinhas fechadas
-> depois que ter colocado tudo:
    -> checar o tamanho das duas pilhas:
        -> tam. diferentes -> NÃO BALANCEADO
        -> tam. iguais:
            -> ir formando parzinhos
            -> par de tipos diferentes -> NÃO BALANCEADO
            -> terminou -> BALANCEADO
*/

int main(void){
    int quantCasosTeste;
    scanf(" %d", &quantCasosTeste);

    char string[1005];

    while(quantCasosTeste){
        scanf("%s", string);

        char *ponteiroString = &string[0];
        if(balanceada(ponteiroString)) printf("BALANCEADO\n");
        else{
            printf("NÃO BALANCEADO\n");
        }

        quantCasosTeste--;
    }

    return 0;
}