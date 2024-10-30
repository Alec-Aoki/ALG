#ifndef CONJUNTO_H
    #define CONJUNTO_H

    void conjunto_listaPertence(int* conjA, int tamConjA, int elemento);
    void conjunto_listaUniao(int* conjA, int tamConjA, int* conjB, int tamConjB);
    void conjunto_listaIntersec(int* conjA, int tamConjA, int* conjB, int tamConjB);
    void conjunto_arvPertence(int* conjA, int tamConjA, int elemento);
    void conjunto_arvUniao(int* conjA, int tamConjA, int* conjB, int tamConjB);
    void conjunto_arvIntersec(int* conjA, int tamConjA, int* conjB, int tamConjB);

#endif 
