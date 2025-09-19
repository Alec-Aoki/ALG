#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

/*
Dado um conjunto de N de trechos (2 ≤ N ≤ 10), cada trecho com J (2 ≤ J ≤ 10^5)
jogadores, e as posições iniciais S0 e Sf ( 0 ≤ S0 ≤ Sf ≤ 10^8) finais de cada um, ordene
os trechos T pela quantidade de ultrapassagens U , do maior valor ao menor, informando
a quantidade de ultrapassagens de cada um.
É considerada uma ultrapassagem quando dois jogadores se encontram em uma mesma
posição. Assuma que todos os jogadores se movem com uma velocidade constante até
alcançar a posição final Sf 
*/

/*
Algoritmo O(n^2):
1. Ordernar vetor por ordem de chegada
2. Percorrer cada elemento do vetor, comparando o elemento atual (A) com cada um dos
próximos (B). Se o elemento A tiver posição inicial menor que B, houve ultrapassagem.
*/

int main(void){
    short int quantTrechos = 0;
    unsigned int quantJogadores = 0;

    cin >> quantTrechos;

    vector<pair<int, int>> posicoes; // Vetor de pares posição final e posição inical
    unsigned int posInicial = 0;
    unsigned int posFinal = 0;
    unsigned int quantPassagens = 0;

    vector<pair<int, int>> trechos; // Vetor de pares quantidade de passagens e trecho

    for(int i = 0; i < quantTrechos; i++){
        cin >> quantJogadores;
        
        // Lendo as posições iniciais e finais de cada jogador
        for (int j = 0; j < quantJogadores; j++){
            cin >> posInicial >> posFinal;
            posicoes.push_back({posFinal, posInicial}); // Note a ordem das posições no pair!
        }

        // Ordernar o vetor por ordem de chegada
        // O(n logn)
        sort(posicoes.begin(), posicoes.end());

        // Ultrapassagens
        // O(n^2)
        for (int j = 0; j < quantJogadores - 1; j++){
            for(int k = j + 1; k < quantJogadores; k++){
                if(posicoes[j].second >= posicoes[k].second){
                    quantPassagens++;
                }
            }
        }

        trechos.push_back({quantPassagens, i});

        quantPassagens = 0;
        posicoes.clear();
    }

    sort(trechos.rbegin(), trechos.rend());

    for(int i = 0; i < quantTrechos; i++){
        cout << trechos[i].second << " " << trechos[i].first << endl;
    }
}