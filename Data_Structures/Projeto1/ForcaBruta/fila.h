#ifndef fila_H
	#define fila_H

    #include "PCV.h"
	#include <stdbool.h>

    typedef struct Fila_ Fila;
	typedef struct PERMUTACAO_ PERMUTACAO;

	void Fila_Inicializar(Fila **fila);
	bool Fila_Vazia(Fila *fila);
	bool Fila_Cheia(Fila *fila);
	void Fila_Enfileirar(Fila *fila, PERMUTACAO *p);
	PERMUTACAO* Fila_Desenfileirar(Fila *fila);
	void Fila_Apagar(Fila *fila);
	  
#endif
