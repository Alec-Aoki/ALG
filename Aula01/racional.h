#ifndef RACIONAL_H
    #define RACIONAL_H

    typedef struct racional_ RACIONAL;

    RACIONAL *racional_crie(int numerador, int denominador);

    void racional_apague(RACIONAL *racional);

    RACIONAL *racional_multiplique(RACIONAL *r1, RACIONAL *r2);

    void racional_imprima(RACIONAL *racional);
#endif