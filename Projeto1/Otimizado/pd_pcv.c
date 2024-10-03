#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 9999999
#define MAX 10000000


    // função que retorna o menor entre dois inteiros
    int min (int a, int b) {
        return (a<b) ? a : b;
    }

    // função auxiliar que aloca uma matriz quadrada de tamanho n(número de cidades)
    int **aloca_matriz(int n) {
        int **matriz = malloc(sizeof(int*)*n);
        for (int i = 0; i < n; i++) {
            (matriz)[i] = malloc (sizeof(int)*n);
        }

        // inicializa matriz com -1
        for (int i = 0; i < n; i++) {
            for (int j = 0 ;j < n ;j++) {
                matriz[i][j] = MAX;
            }
        }

        return matriz;

    }
    // função que lê os dados e guarda numa matriz de adjacencia
    int **ler_dados (int *ini, int *num_cidades, int *num_arestas) {
        scanf(" %d %d %d", num_cidades, ini, num_arestas);

        int** matriz = aloca_matriz(*num_cidades);
        int k = 0;
        while (k < *num_arestas) {
            int origem, destino, dist;
            scanf(" %d %d %d", &origem, &destino, &dist);
            matriz[origem-1][destino-1] = dist;
            matriz[destino-1][origem-1] = dist;
            k++;
        }
        for (int i = 0; i < *num_cidades; i++) {
            matriz[i][i] = 0;
        }

        return matriz;
    }
    // função auxiliar que confere se todas as cidades foram visitadas
    bool tudo_visitado (bool *visitado, int n) {
        for (int i = 0;i < n; i++) {
            if (!(visitado[i])){
                return false;
            }
        }    
        return true;   
    }
    // função que imprime a melhor rota
    void imprimir_caminho (int *caminho, int n) {
        printf("Melhor Caminho : ");
        for (int i = 0; i < n; i++) {
            if(i!=0)
                printf("-> %d ", caminho[i]);
            else {
                printf("%d ", caminho[i]);
            }
        }
         printf("-> %d\n",caminho[0]); 
    }

    //funções para alocar memória para vetores auxiliares, um de booleanos para conferir se já foi visitado, e o outro para guardar a melhor rota
    bool *criar_visitado(int n) {
        bool *visitado = malloc(sizeof(bool)*n);
        for (int i = 0; i < n; i++) {
            visitado[i] = false;
        }
        return visitado;
    }

    int *criar_caminho (int n) {
        int* caminho = malloc(sizeof(int)*n+1);
        if (caminho==NULL){
            printf("ERRO DE ALOCAÇÃO");
            exit(1);
            }
        return caminho;    
    }

    // algoritmo de programação dinamica para calcular a melhor rota
    int PCV (int cidade_atual, int n, bool visitado[],int **matriz, int origem, int *caminho, int pos) {
        int min_custo = INF;

        if (tudo_visitado(visitado, n)) {
            return matriz[cidade_atual][origem];
        }

        for (int prox_cidade = 0; prox_cidade < n; prox_cidade++) {
            if (!visitado[prox_cidade]) {
                visitado[prox_cidade] = true;
                caminho[pos] = prox_cidade+1;
                int custo = matriz[cidade_atual][prox_cidade] + PCV (prox_cidade, n, visitado, matriz, origem, caminho, pos+1);
                min_custo = min(min_custo, custo);
                visitado[prox_cidade] = false;
            }
        }

        return min_custo;
    }

   
    int main () {
        int n, ini, arestas;
        int **matriz = ler_dados(&ini, &n, &arestas);
        bool *visitado = criar_visitado(n);
        int *caminho = criar_caminho(n);
        
        ini -= 1;
        visitado[ini] = true;
        caminho[0] = ini+1;    

        int answer = PCV(ini, n, visitado, matriz, ini, caminho, 1);
        printf("Custo Total : %d\n", answer);
        imprimir_caminho(caminho, n);
       



       free(caminho);
       free(visitado);
       for(int i = 0; i < n; i++) {
        free(matriz[i]);
       }
       free(matriz);
    }
