#include <iostream>
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

Dá TLE no caso 6 :(
*/

/*
Algortimo O(n log n) (divisão e conquista):
1. Ordenar jogadores por posição final (ordem de chegada)  
2. Extrair sequência de posições iniciais nesta ordem de chegada
3. Contar "inversões" nesta sequência usando merge sort modificado
*/

// Função para fazer merge e contar ultrapassagens
long long merge_e_conta(vector<int>& posIni, vector<int>& vetTemp, int i_esq, int i_meio, int i_dir) {
    int i_metade_esq = i_esq;
    int i_metade_dir = i_meio + 1; 
    int i_vetTemp = i_esq;
    long long quantPassagens = 0;
    
    // Merge das duas metades contando as inversões
    while (i_metade_esq <= i_meio && i_metade_dir <= i_dir) {
        if (posIni[i_metade_esq] <= posIni[i_metade_dir]) {
            vetTemp[i_vetTemp++] = posIni[i_metade_esq++];
        }
        else {
            // Todos os elementos da primeira metade restantes são maiores (ultrapassagens)
            vetTemp[i_vetTemp++] = posIni[i_metade_dir++];
            quantPassagens += (i_meio - i_metade_esq + 1);
        }
    }
    
    // Copiar elementos restantes da primeira metade
    while (i_metade_esq <= i_meio) {
        vetTemp[i_vetTemp++] = posIni[i_metade_esq++];
    }
    
    // Copiar elementos restantes da segunda metade
    while (i_metade_dir <= i_dir) {
        vetTemp[i_vetTemp++] = posIni[i_metade_dir++];
    }
    
    // Copiar de volta para o vetor original
    for (int indice = i_esq; indice <= i_dir; indice++) {
        posIni[indice] = vetTemp[indice];
    }
    
    return quantPassagens;
}

// Função recursiva do mergeSort que conta ultrapassagens
long long mergeSort(vector<int>& posIni, vector<int>& vetTemp, int i_esq, int i_dir) {
    long long totPassagens = 0;
    
    if (i_esq < i_dir) {
        int i_meio = i_esq + (i_dir - i_esq) / 2;
        
        // Contar ultrapassagens na metade esquerda
        totPassagens += mergeSort(posIni, vetTemp, i_esq, i_meio);
        
        // Contar ultrapassagens na metade direita  
        totPassagens += mergeSort(posIni, vetTemp, i_meio + 1, i_dir);
        
        // Contar ultrapassagens entre as duas metades
        totPassagens += merge_e_conta(posIni, vetTemp, i_esq, i_meio, i_dir);
    }
    
    return totPassagens;
}

int main() {
    int quantidadeTrechos;
    cin >> quantidadeTrechos;
    
    vector<pair<long long, int>> resultadosTrechos; // {ultrapassagens, numero do trecho}
    
    for (int i = 0; i < quantidadeTrechos; i++) {
        int quantJogadores;
        cin >> quantJogadores;
        
        vector<pair<int, int>> posicoes;
        int posInicial, posFinal;
        
        // Lendo as posições iniciais e finais de cada jogador
        for (int j = 0; j < quantJogadores; j++){
            cin >> posInicial >> posFinal;
            posicoes.push_back({posFinal, posInicial}); // Note a ordem das posições no pair!
        }

        // Ordenar o vetor por ordem de chegada (posição final)
        // O(n log n)
        sort(posicoes.begin(), posicoes.end());

        // Extrair posições iniciais na ordem de chegada
        vector<int> posIniOrd;
        for (int j = 0; j < quantJogadores; j++){
            posIniOrd.push_back(posicoes[j].second);
        }

        // Contar ultrapassagens usando divide and conquer
        // O(n log n)
        vector<int> vetTemp(quantJogadores);
        long long quantPassagens = mergeSort(posIniOrd, vetTemp, 0, quantJogadores - 1);
        
        resultadosTrechos.push_back({quantPassagens, i});
    }
    
    // Ordenar trechos pela quantidade de ultrapassagens (maior para menor)
    sort(resultadosTrechos.begin(), resultadosTrechos.end(), greater<pair<long long, int>>());
    
    // Imprimir resultados
    for (int i = 0; i < quantidadeTrechos; i++) {
        cout << resultadosTrechos[i].second << " " << resultadosTrechos[i].first << endl;
    }
    
    return 0;
}