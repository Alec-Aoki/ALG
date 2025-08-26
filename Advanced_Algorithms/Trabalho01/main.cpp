#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "trie.h"
using namespace std;

int main(void){
    int quantLinhas, quantColunas;
    cin >> quantLinhas >> quantColunas;

    /* Geração da matriz de letras */
    char matrizLetras[quantLinhas][quantColunas];
    string linha;
    // Lendo linha por linha da grid
    for(int i = 0; i < quantLinhas; i++){
        cin >> linha;
        // Para cada linha lida, pegamos o caractere
        // de cada coluna e inserimos na matriz
        for(int j = 0; j < quantColunas; j++){
            matrizLetras[i][j] = linha.at(j);
        }
    }

    /* Geração da árvore trie com as palavras do dicionário */
    int quantPalavrasDic;
    cin >> quantPalavrasDic;

    TRIE *arvTrie = trie_criar();
    if(arvTrie == NULL) return 1; // Erro

    string palavra; // Variável reutilizável
    for(int i = 0; i < quantPalavrasDic; i++){
        cin >> palavra;
        trie_inserir(arvTrie, palavra);
    }

    /* Buscando as palavras na grid */
    set<string> palavrasEncontradas;
    set<string> resFinal;
    // Percorrendo letra por letra da matriz
    for(int i = 0; i < quantLinhas; i++){
        for(int j = 0; j < quantColunas; j++){
            // Pegando a linha em cada uma das 8 direções e jogando ela na busca
            
            // Direita
            palavra.clear();
            for(int k = j; k < quantColunas; k++) palavra += matrizLetras[i][k];
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Esquerda
            palavra.clear();
            for(int k = j; k >= 0; k--) palavra += matrizLetras[i][k];
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Cima
            palavra.clear();
            for(int k = i; k >= 0; k--) palavra += matrizLetras[k][j];
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Baixo
            palavra.clear();
            for(int k = i; k < quantLinhas; k++) palavra += matrizLetras[k][j];
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Diagonal superior direita
            palavra.clear();
            int lin = i;
            int col = j;
            while(lin >= 0 && col < quantColunas){
                palavra += matrizLetras[lin][col];
                lin--;
                col++;
            }
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Diagonal inferior direita
            palavra.clear();
            lin = i;
            col = j;
            while(lin < quantLinhas && col < quantColunas){
                palavra += matrizLetras[lin][col];
                lin++;
                col++;
            }
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Diagonal superior esquerda
            palavra.clear();
            lin = i;
            col = j;
            while(lin >= 0 && col >= 0){
                palavra += matrizLetras[lin][col];
                lin--;
                col--;
            }
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);

            // Diagonal inferior esquerda
            lin = i;
            col = j;
            while(lin < quantLinhas && col >= 0){
                palavra += matrizLetras[lin][col];
                lin++;
                col--;
            }
            palavrasEncontradas = trie_check_linha(arvTrie, palavra);
            // Concatenando os vetores
            resFinal.merge(palavrasEncontradas);
        }
    }

    cout << resFinal.size() << endl;
    for(string str : resFinal){
        cout << str << endl;
    }

    trie_destruir(arvTrie);

    return 0;
}