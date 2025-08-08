#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h>
#include "PCV.h"

/*Funções do timer*/
/*
typedef struct{
    clock_t start;
    clock_t end;
}Timer;
void start_timer(Timer *timer);
double stop_timer(Timer *timer);*/

int main(void){
    int num_cidades, cidade_inicial, arestas;

    INDICE* distancia = PCV_ler_dados(&num_cidades, &cidade_inicial, &arestas);

    //Timer tempoTimer;
    //double tempoExec;

    //start_timer(&tempoTimer);

    PERMUTACAO* melhor_caminho = PCV_Melhor_Caminho(num_cidades, cidade_inicial, arestas, distancia);
    
    //tempoExec = stop_timer(&tempoTimer);
    //printf("\nTempo de execucao: %lfs\n", tempoExec);

    PCV_Apagar(distancia, melhor_caminho);
    
    return 0;
}

/*
void start_timer(Timer *timer){
    timer->start = clock();
    return;
}

double stop_timer(Timer *timer){
    timer->end = clock();
    return((double)(timer->end - timer->start)) / CLOCKS_PER_SEC;
}*/