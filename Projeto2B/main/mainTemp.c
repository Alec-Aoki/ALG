#include <stdio.h>
#include <stdlib.h>

#include "../bibliotecas/lista.h"
#include "../bibliotecas/heapmax.h"

#define LISTA 0
#define ARVORE 1

int main(void) {
    int TAD, tamanho_A, tamanho_B;

    scanf(" %d %d %d", &TAD, &tamanho_A, &tamanho_B);

    if (TAD == LISTA) {
        LISTA *lista_A = Lista_Criar(tamanho_A); 
        LISTA *lista_B = Lista_Criar(tamanho_B); 

        // Leitura dos elementos do conjunto A
        for (int i = 0; i < tamanho_A; i++) {
            scanf(" %d", &temp);  
            Lista_Inserir(lista_A, temp); 
        }

        // Leitura dos elementos do conjunto B
        for (int i = 0; i < tamanho_B; i++) { 
            scanf(" %d", &temp);  
            Lista_Inserir(lista_B, temp); 
        }

    }
    else if (TAD == ARVORE) {
        HEAPMAX *arvore_A = heapmax_criar(); 
        HEAPMAX *arvore_B = heapmax_criar(); 

        int elemento;
        // Leitura dos elementos do conjunto A
        for (int i = 0; i < tamanho_A; i++) {
            scanf(" %d", &elemento);  
            Arvore_Inserir(arvore_A, elemento); 
        }

        // Leitura dos elementos do conjunto B
        for (int i = 0; i < tamanho_B; i++) { 
            scanf(" %d", &elemento);  
            Arvore_Inserir(arvore_B, elemento); 
        }

    } else {
        printf("Comando inválido!\n");  // Tratamento de erro para operação inválida
        return 1;
    }

    // Leitura da operação a ser realizada (1: Pertencimento, 2: União, 3: Interseção)
    scanf("%d", &operacao);
    if (operacao == 1) {  // Se a operação for de pertencimento, lê o elemento
        scanf("%d", &elemento);
    }

    // Seleção do tipo de TAD para a operação: 0 para lista, 1 para árvore
    if (TAD == 0) {

        switch (operacao) {
            case 1:
                Conjunto_Pertence_0(lista_A, tamanho_A, elemento);  // Verifica pertencimento usando lista
                break;
            case 2:
                Conjunto_Uniao_0(lista_A, tamanho_A, lista_B, tamanho_B);  // União de conjuntos usando lista
                break;
            case 3:
                Conjunto_Intersecao_0(lista_A, tamanho_A, lista_B, tamanho_B);  // Interseção de conjuntos usando lista
                break;
            default:
                printf("Comando inválido!\n");  // Tratamento de erro para operação inválida
                return 1;
        }
    } else if (TAD == 1) {

        switch (operacao) {
            case 1:
                Conjunto_Pertence_1(arvore_A, tamanho_A, elemento);  // Verifica pertencimento usando árvore
                break;
            case 2:
                Conjunto_Uniao_1(arvore_A, tamanho_A, arvore_B, tamanho_B);  // União de conjuntos usando árvore
                break;
            case 3:
                Conjunto_Intersecao_1(arvore_A, tamanho_A, arvore_B, tamanho_B);  // Interseção de conjuntos usando árvore
                break;
            default:
                printf("Comando inválido!\n");  // Tratamento de erro para operação inválida
                return 1;
        }
    }

    return 0;
}
