#ifndef PCV_H
	#define PCV_H

    #include "fila.h"

    typedef struct Indice_ INDICE;
    typedef struct Permutacao_ Permutacao;

    INDICE* PCV_ler_dados(int *num,  int *cidade_inicial, int *arestas);
    Permutacao* PCV_criar_caminhos(int num_cidades, int cidade_inicial, int arestas, INDICE* distancia);
    void PCV_Melhor_caminho(Permutacao* caminhos, INDICE* distancia, int num_cidades, int arestas);
    void PCV_Apagar(INDICE* distancia, Permutacao* caminhos, int num_cidades);
    
#endif
