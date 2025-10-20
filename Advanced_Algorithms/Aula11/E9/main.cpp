#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

/*
3 opções:
- Avançar sem agir
- Comprar passe de garimpo (gasta diamante)
- Usar passe de garimpo (ganha diamante)

Regras:
-> Máximo de um passe de garimpo guardado
-> Após usar um passe de garimpo, descansa o dia seguinte

Observações:
-> O jogador começa com no mínimo 10 diamantes

Vetores de inteiros representando a quantidade de diamantes de
comprar ou usar do dia

Objetivo: maximizar a quantidade de diamantes

Força bruta: para cada casa, chama as 3 opções:
1. Avançar sem agir
2. Gastar o passe
3. Comprar o passe

// Árvore de decisão
- Tem que descansar?
    - Sim:
        - Descansa (não ganha nem perde diamante, vai pro dia seguinte)
    - Não:
        - Tem passe?
            - Sim:
                - Usa
                - Não usa
            - Não:
                - Tem diamante suficiente para comprar?
                    - Sim:
                        - Compra
                        - Não compra
                    - Não:
                        - Não compra
*/

int forca_bruta(vector<int> vetor_dias, int quantDiamantes, int i_dia, bool descanso, bool temPasse);
int forca_bruta_otim(vector<int> vetor_dias, int quantDiamantes, int i_dia, bool temPasse);
int memoizacao(map<tuple<int, int, int>, int> &memoria, vector<int> vetor_dias, int quantDiamantes, int i_dia, int temPasse);

int bottom_up(vector<int> vetor_dias, int quantDias, int quantDiamantesInicial){
    // dp[dia][temPasse]
    vector<vector<int>> dp(quantDias + 2, vector<int>(2, -1));
    
    // Estado inicial
    dp[0][0] = quantDiamantesInicial;
    
    // Preenchendo a tabela
    for(int dia = 0; dia < quantDias; dia++){
        for(int temPasse = 0; temPasse <= 1; temPasse++){
            if(dp[dia][temPasse] == -1) continue;
            
            int diamantes = dp[dia][temPasse];
            
            if(temPasse){
                // Usa o passe
                int proximoDia = dia + 2;
                int novosDiamantes = diamantes + vetor_dias[dia];
                dp[proximoDia][0] = max(dp[proximoDia][0], novosDiamantes);
                
                // Não usa o passe
                proximoDia = dia + 1;
                dp[proximoDia][1] = max(dp[proximoDia][1], diamantes);
            } else {
                // Compra passe
                if(diamantes >= vetor_dias[dia]){
                    int proximoDia = dia + 1;
                    int novosDiamantes = diamantes - vetor_dias[dia];
                    dp[proximoDia][1] = max(dp[proximoDia][1], novosDiamantes);
                }
                
                // Não compra
                int proximoDia = dia + 1;
                dp[proximoDia][0] = max(dp[proximoDia][0], diamantes);
            }
        }
    }
    
    // Encontrando o máximo de diamantes ao final
    int resultado = 0;
    for(int dia = quantDias; dia < quantDias + 2; dia++){
        for(int temPasse = 0; temPasse <= 1; temPasse++){
            if(dp[dia][temPasse] != -1){
                resultado = max(resultado, dp[dia][temPasse]);
            }
        }
    }
    
    return resultado;
}

int main(void){
    int quantFases;
    cin >> quantFases;

    int quantDiamantesInicial;
    int quantDias;
    vector<int> vetor_dias;
    while(quantFases > 0){
        /* Leitura da entrada de cada fase */
        cin >> quantDiamantesInicial;
        cin >> quantDias;
        cin.ignore();

        string linha = "";
        getline(cin, linha);

        stringstream ss(linha);

        int valorDia;
        int i = quantDias;
        while(ss >> valorDia){
            if(i > 0){
                vetor_dias.push_back(valorDia);
            }
            i--;
        }

        /* Força bruta */
        // cout << forca_bruta(vetor_dias, quantDiamantesInicial, 0, false, false) << endl;
        // cout << forca_bruta_otim(vetor_dias, quantDiamantesInicial, 0, false) << endl;

        /* Força bruta com memoização */
        // map<tuple<int, int, int>, int> memoria;
        // cout << memoizacao(memoria, vetor_dias, quantDiamantesInicial, 0, 0) << endl;

        /* DP bottom up */
        cout << bottom_up(vetor_dias, quantDias, quantDiamantesInicial) << endl;

        quantFases--;
        vetor_dias.clear();
    }

    return 0;
}

int forca_bruta(vector<int> vetor_dias, int quantDiamantes, int i_dia, bool descanso, bool temPasse){
    // Caso base
    if(i_dia == vetor_dias.size()){
        return quantDiamantes;
    }

    // Árvore de decisão
    if (descanso){
        return forca_bruta(vetor_dias, quantDiamantes, i_dia + 1, false, temPasse);
    } else {
        if(temPasse){
            return max(
                forca_bruta(vetor_dias, quantDiamantes + vetor_dias[i_dia], i_dia + 1, true, false), // Usa o passe
                forca_bruta(vetor_dias, quantDiamantes, i_dia + 1, false, true) // Não usa o passe
            );
        } else {
            if(quantDiamantes >= vetor_dias[i_dia]){
                // Pode comprar
                return max(
                    forca_bruta(vetor_dias, quantDiamantes - vetor_dias[i_dia], i_dia + 1, false, true), // Compra
                    forca_bruta(vetor_dias, quantDiamantes, i_dia + 1, false, false) // Não compra
                );
            } else {
                // Não pode comprar, descansa
                return forca_bruta(vetor_dias, quantDiamantes, i_dia + 1, false, false);
            }
        }
    }
}

int forca_bruta_otim(vector<int> vetor_dias, int quantDiamantes, int i_dia, bool temPasse){
    // Caso base
    if(i_dia >= vetor_dias.size()){
        return quantDiamantes;
    }

    // Árvore de decisão
    if(temPasse){
        return max(
            forca_bruta_otim(vetor_dias, quantDiamantes + vetor_dias[i_dia], i_dia + 2, false), // Usa o passe
            forca_bruta_otim(vetor_dias, quantDiamantes, i_dia + 1, true) // Não usa o passe
        );
    } else {
        if(quantDiamantes >= vetor_dias[i_dia]){
            // Pode comprar
            return max(
                forca_bruta_otim(vetor_dias, quantDiamantes - vetor_dias[i_dia], i_dia + 1, true), // Compra
                forca_bruta_otim(vetor_dias, quantDiamantes, i_dia + 1, false) // Não compra
            );
        } else {
            // Não pode comprar, descansa
            return forca_bruta_otim(vetor_dias, quantDiamantes, i_dia + 1, false);
        }
    }
}

int memoizacao(map<tuple<int, int, int>, int> &memoria, vector<int> vetor_dias, int quantDiamantes, int i_dia, int temPasse){
    // Caso base
    if(i_dia >= vetor_dias.size()){
        return quantDiamantes;
    }

    // Criando a chave para o estado atual
    tuple<int, int, int> chave = make_tuple(temPasse, i_dia, quantDiamantes);

    // Verificando a memória
    if(memoria.find(chave) != memoria.end()){
        return memoria[chave];
    }

    // Árvore de decisão
    if(temPasse){
        memoria[chave] = max(
            memoizacao(memoria, vetor_dias, quantDiamantes + vetor_dias[i_dia], i_dia + 2, 0), // Usa o passe
            memoizacao(memoria, vetor_dias, quantDiamantes, i_dia + 1, 1) // Não usa o passe
        );
    } else {
        if(quantDiamantes >= vetor_dias[i_dia]){
            // Pode comprar
            memoria[chave] = max(
                memoizacao(memoria, vetor_dias, quantDiamantes - vetor_dias[i_dia], i_dia + 1, 1), // Compra
                memoizacao(memoria, vetor_dias, quantDiamantes, i_dia + 1, 0) // Não compra
            );
        } else {
            // Não pode comprar, descansa
            memoria[chave] = memoizacao(memoria, vetor_dias, quantDiamantes, i_dia + 1, 0);
        }
    }

    return memoria[chave];
}