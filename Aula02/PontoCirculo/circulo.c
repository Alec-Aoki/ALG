#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "circulo.h"
// #include "ponto.h", circulo.h já inclui ponto.h

struct circulo_{
    PONTO *ponto;

    //coordenada dos pontos centrais
    //float x;
    //float y;

    float raio;
};

CIRCULO *circulo_criar(PONTO *p, float raio){
    if(p == NULL) return NULL;

    CIRCULO *circulo = (CIRCULO *)malloc(sizeof(CIRCULO));
    if(circulo == NULL) return NULL;

    circulo->raio = raio;
    //circulo->x = ponto_get_x(p);
    //circulo->y = ponto_get_y(p);

    circulo->ponto = p;

    return circulo;
}

bool circulo_set_ponto(CIRCULO *c, PONTO *p){
    if((c == NULL) || (p == NULL)) return false;

    //c->x = ponto_get_x(p);
    //c->y = ponto_get_y(p);

    c->ponto = p;

    return true;
}

bool circulo_set_raio(CIRCULO *c, float raio){
    if((c == NULL) || (raio <= 0)) return false;

    c->raio = raio;

    return true;
}

PONTO *circulo_get_ponto(CIRCULO *c){
    if(c == NULL) return NULL;

    //PONTO *ponto = ponto_criar(c->x, c->y);
    //if(ponto == NULL) return NULL;

    return c->ponto;

    //return ponto;
}

float circulo_get_raio(CIRCULO *c){
    if(c != NULL){
        return c->raio;
    }
}

void circulo_apagar(CIRCULO **circulo){
    if((*circulo) != NULL){
        ponto_apagar(&((*circulo)->ponto));
        free(*circulo);
        *circulo = NULL;
    }
    return;
}