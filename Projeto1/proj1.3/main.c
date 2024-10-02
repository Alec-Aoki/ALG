#include "PCV.h"
#include <stdio.h>

int main(){
    int num_cidades, cidade_inicial, arestas;

    INDICE* distancia = PCV_ler_dados(&num_cidades, &cidade_inicial, &arestas);
    Permutacao* caminhos = PCV_criar_caminhos(num_cidades, cidade_inicial, arestas, distancia);
    PCV_Melhor_caminho(caminhos, distancia, num_cidades, arestas);
    //PCV_Apagar(distancia, caminhos, num_cidades);
    
    return 0;
}