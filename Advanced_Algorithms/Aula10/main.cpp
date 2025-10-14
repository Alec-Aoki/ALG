#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/*
Tem-se um conjunto de N pedras de dominó enfileiradas sobre a mesa, onde a quantidade
de pontos que cada uma agrega é a soma dos números em seus dois lados.
- Lista (ordem dos elementos importa) de valores (soma dos lados)

Os jogadores alternam turnos, e em cada turno um jogador deve escolher uma das
pedras das extremidades da fila e removê-la da mesa, somando seu valor à sua pontuação,
até que todas as pedras tenham sido retiradas.
- Retirar ou do inicio ou do fim da lista

O objetivo é determinar por meio de programação dinâmica a pontuação máxima que
Maria pode garantir, assumindo que ela começa o jogo e que ambos os jogadores jogam
de forma ótima, sempre planejando suas escolhas para maximizar seu próprio resultado
e antecipando as jogadas do adversário.

Dado um vetor de valores, intercaladamente remover um valor de uma extremidade de forma 
a ter removido a maior quantidade de valor possível

4
(3,6) (6,6) (6,0) (0,3)

*/

int forca_bruta(vector<int> pecas, int i, int j, bool vezMaria){
    // Caso base
    if(i > j) return 0;

    if(vezMaria){
        int pegarEsq = pecas[i] + forca_bruta(pecas, i + 1, j, false);
        int pegarDir = pecas[j] + forca_bruta(pecas, i, j - 1, false);
        return max(pegarEsq, pegarDir);
    }
    else {
        int pegarEsq = forca_bruta(pecas, i + 1, j, true);
        int pegarDir = forca_bruta(pecas, i, j - 1, true);
        return min(pegarEsq, pegarDir);
    }
}

int forca_bruta_otimizado(vector<int> pecas, int i, int j, int vezMaria, vector<vector<vector<int>>> &memoria){
    // Caso base
    if(i > j) return 0;

    if(memoria[i][j][vezMaria] != -1){
        return memoria[i][j][vezMaria];
    }

    if(vezMaria){
        int pegarEsq = pecas[i] + forca_bruta_otimizado(pecas, i + 1, j, 0, memoria);
        int pegarDir = pecas[j] + forca_bruta_otimizado(pecas, i, j - 1, 0, memoria);
        int res = max(pegarEsq, pegarDir);
        memoria[i][j][vezMaria] = res;
        return res;
    }
    else {
        int pegarEsq = forca_bruta_otimizado(pecas, i + 1, j, 1, memoria);
        int pegarDir = forca_bruta_otimizado(pecas, i, j - 1, 1, memoria);
        int res = min(pegarEsq, pegarDir);
        memoria[i][j][vezMaria] = res;
        return res;
    }
}

int main(void) {
    int quantCasosTeste;
    cin >> quantCasosTeste;

    int quantPecas;
    vector<int> pecas;
    int pontuacaoMaxima;
    while(quantCasosTeste > 0){
        cin >> quantPecas;

        /* Leitura das peças de domino */
        for(int i = 0; i < quantPecas; i++){
            char abre, virgula, fecha;
            int primeiroValor, segundoValor;
            cin >> abre >> primeiroValor >> virgula >> segundoValor >> fecha;
            pecas.push_back(primeiroValor + segundoValor);
        }

        vector<vector<vector<int>>> memoria;
        
        // Inicializando com -1
        memoria.assign(quantPecas, vector<vector<int>>(quantPecas, vector<int>(2, -1)));

        cout << forca_bruta_otimizado(pecas, 0, pecas.size() - 1, 1, memoria) << endl;

        // cout << forca_bruta(pecas, 0, pecas.size() - 1, true) << endl;

        // cout << endl;

        pecas.clear();
        pontuacaoMaxima = 0;
        quantCasosTeste--;
    }

    return 0;
}
