#ifndef fila_H
	#define fila_H

    #include "PCV.h"
	#include <stdbool.h>

    typedef struct Fila_ Fila;
    typedef struct Permutacao_ Permutacao;

	void Fila_Inicializar(Fila **fila);
	bool Fila_Vazia(Fila *fila);
	bool Fila_Cheia(Fila *fila);
	void Fila_Enfileirar(Fila *fila, Permutacao *p);
	Permutacao* Fila_Desenfileirar(Fila *fila);
	void Fila_Apagar(Fila *fila);
	  
#endif
