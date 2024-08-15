#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "ponto.h"


struct ponto_{
    float x;
    float y;
};

PONTO *ponto_criar(float x, float y){
    PONTO *ponto = (PONTO *)malloc(1*sizeof(PONTO));
    if(ponto == NULL) return(NULL);

    ponto->x = x;
    ponto->y = y;

    return ponto;
}

void ponto_apagar(PONTO **p){
    if((*p) != NULL){
        free(*p);
        *p = NULL;   
    }

    return;
}

bool ponto_set(PONTO *p, float x, float y){
    if(p == NULL) return false;

    p->x = x;
    p->y = y;

    return true;
}

float ponto_get_x(PONTO *p){
    if(p != NULL){
        return p->x;
    }
}

float ponto_get_y(PONTO *p){
    if(p != NULL){
        return p->y;
    }
}

void ponto_print(PONTO *p){
    if(p != NULL) {
        printf("Ponto: (%.1f, %.1f)\n", p->x, p->y);
    }

    return;
}

/*Por que colocar a função ponto na ponto.h?

Pois calcular a distância entre dois pontos não possui uma relação fundamental (além do contexto em que a usaremos) com as informações do círculo. Ela está muito mais relacionada com o tópico de pontos em si (e as relações entre eles) que com o tópico de círculos (e os pontos que o formam). Podemos usar a função distancia para calcular a distância entre dois pontos em contextos diferentes daqueles do círculo, o que torna ilógico colocá-la naquele TAD.
*/
float distancia(PONTO *pa, PONTO *pb){
    if((pa == NULL) || (pb == NULL)){
        return -1; //erro
    }

    float distancia;
    // sqrt((xb-xa)^2 + (yb-ya)^2), fórmula da distância entre dois pontos
    distancia = sqrt(pow(((pb->x)-(pa->x)), 2) + pow(((pb->y)-(pa->y)), 2));

    return distancia;
}
