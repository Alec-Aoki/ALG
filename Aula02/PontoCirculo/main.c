#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ponto.h"
#include "circulo.h"

/*
Sejam as interfaces dos TADs Ponto e Circulo como definidas. Desenvolva a
implementação dos TADs e um programa cliente (main.c) que use os dois TADs. O
programa cliente deve, pela ordem:
1. Criar um ponto p e um círculo r definidos pelo usuário (stdin);
2. Imprimir as coordenadas do ponto;
3. Imprimir as coordenadas do ponto central do círculo e o de seu raio;
4. Apagar o ponto e apagar o círculo.

Atenção: Para ser corretamente corrigido, seu código, se entregue em um único arquivo Zip/Makefile: deve obrigatoriamente ter um arquivo Makefile na raíz do arquivo zip; deve conter apenas o comando de compilação na diretiva "all" (ou seja, será executado o comando "make all" para compilar o seu código); deve conter apenas o comando de execução na diretiva "run" (ou seja, será executado o comando "make run" para execução do seu código);
*/

/*PROTOTIPAGEM DAS FUNÇÕES*/
PONTO *criarPonto(void);
CIRCULO *criarCirculo(void);
void printarCirculo(CIRCULO *circulo);

/*FUNÇÃO MAIN*/
int main(void){
    /*Criar ponto*/
    PONTO *p = criarPonto();

    /*Criar circulo*/
    CIRCULO *r = criarCirculo();

    /*Imprimir ponto*/
    ponto_print(p);

    /*Imprimir circulo*/
    printarCirculo(r);

    /*Apagar ponto e circulo*/
    ponto_apagar(&p);
    circulo_apagar(&r);

    return 0;
}

/*FUNÇÕES*/
PONTO *criarPonto(void){
    float x, y;
    scanf("%f", &x);
    scanf("%f", &y);

    PONTO *ponto = ponto_criar(x, y);
    if(ponto != NULL) return ponto;

    return NULL;
}

CIRCULO *criarCirculo(void){
    PONTO *pontoCirculo = criarPonto();
    if(pontoCirculo == NULL) return NULL;

    float raio;
    scanf("%f", &raio);

    CIRCULO *circulo = circulo_criar(pontoCirculo, raio);
    if(circulo != NULL) return circulo;

    return NULL;
}

void printarCirculo(CIRCULO *circulo){
    if(circulo == NULL) return;

    PONTO *ponto = circulo_get_ponto(circulo);
    if(ponto == NULL) return;

    printf("Circulo: Centro(%.1f, %.1f), Raio = %.1f\n", ponto_get_x(ponto), ponto_get_y(ponto), circulo_get_raio(circulo));
}