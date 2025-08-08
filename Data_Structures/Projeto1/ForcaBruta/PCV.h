#ifndef PCV_H
	#define PCV_H

    #include "fila.h"

    typedef struct INDICE_ INDICE;
    typedef struct PERMUTACAO_ PERMUTACAO;

    INDICE* PCV_ler_dados(int *num,  int *cidade_inicial, int *arestas);
    PERMUTACAO* PCV_Melhor_Caminho(int num_cidades, int cidade_inicial, int arestas, INDICE* distancia);
    void PCV_Apagar(INDICE* distancia, PERMUTACAO* melhor_caminho);


#endif
