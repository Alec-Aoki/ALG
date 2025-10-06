#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

/* Struct para representar uma reliquia */
struct Reliquia {
    int hpAtual; // Estabilidade
    int alturaAnterior;

    // Construtor
    Reliquia(int hp, int alt){
        hpAtual = hp;
        alturaAnterior = alt;
    }

    // Função de comparação por hp para usar no map
    bool operator<(const Reliquia& outraReliquia) const {
        if (hpAtual != outraReliquia.hpAtual)
            return hpAtual < outraReliquia.hpAtual;
        return alturaAnterior < outraReliquia.alturaAnterior;
    }
};

// Como cada quebra de pedra gera 2 colunas, nosso estado
// será o conjunto dessas novas colunas, portanto, um
// vetor de vetores de reliquias
using Estado = vector<vector<Reliquia>>; // Alias

Estado bater_reliquia(const Estado &estadoAtual, int i_coluna, int i_reliqAtingida);
int resolver_DP(const Estado &estadoAtual, map<Estado, int> &memoria);

int main(void){
    /* Leitura da entrada */
    int quantReliquias = 0;
    cin >> quantReliquias;

    Estado estadoInicial;
    // Coluna de reliquias, [0] = base
    vector<Reliquia> colunaInicial;

    int hpPedra;
    for(int i = 0; i < quantReliquias; i++){
        cin >> hpPedra;
        colunaInicial.push_back(Reliquia(hpPedra, i)); 
    }

    estadoInicial.push_back(colunaInicial);

    /* Memoização */
    // Guarda a quantidade de golpes mínimos para resolver
    // cada estado
    map<Estado, int> memoria;

    int quantGolpesMin = resolver_DP(estadoInicial, memoria);
    cout << quantGolpesMin << endl;

    return 0;
}

int resolver_DP(const Estado &estadoAtual, map<Estado, int> &memoria){
    // Caso base
    if(estadoAtual.empty()){
        return 0;
    }

    // Memoização
    if(memoria.find(estadoAtual) != memoria.end()){
        return memoria[estadoAtual];
    }

    // "Infinito"
    int quantGolpesMin = INT_MAX;

    // Batendo em cada reliquia do estado atual e obtendo o estado
    // Indice da coluna dentro do estado
    for(int i = 0; i < estadoAtual.size(); i++){
        // Indice da reliquia dentro da coluna
        for(int j = 0; j < (estadoAtual[i]).size(); j++){
            Estado estadoNovo = bater_reliquia(estadoAtual, i, j);

            int quantGolpes = 1 + resolver_DP(estadoNovo, memoria);

            quantGolpesMin = min(quantGolpesMin, quantGolpes);
        }
    }

    // Guardando o estado gerado na memoria
    memoria[estadoAtual] = quantGolpesMin;
    
    return quantGolpesMin;
}

/* Simula um golpe em uma reliquia e cria o estado resultante */
Estado bater_reliquia(const Estado &estadoAtual, int i_coluna, int i_reliqAtingida){
    Estado estadoNovo = estadoAtual;

    // Decrementando o estado da reliquia atingida
    ((estadoNovo[i_coluna][i_reliqAtingida]).hpAtual)--;

    // Se a reliquia for destruida...
    if((estadoNovo[i_coluna][i_reliqAtingida]).hpAtual <= 0){
        // ..."todas as relíquias acima caem ao lado formando uma nova coluna"...

        /* Separando as colunas (abaixo e acima da reliquia quebrada) */
        vector<Reliquia> colunaAcima;
        vector<Reliquia> colunaAbaixo;

        // Coluna abaixo
        for(int i = 0; i < i_reliqAtingida; i++){
            colunaAbaixo.push_back((estadoNovo[i_coluna])[i]);
        }

        // Coluna acima
        for(int i = i_reliqAtingida + 1; i < (estadoNovo[i_coluna]).size(); i++){
            colunaAcima.push_back((estadoNovo[i_coluna])[i]);
        }

        // Salvando altura original da base antes de atualizar
        int alturaOriginalBase;
        if(colunaAcima.empty()){
            alturaOriginalBase = 0;
        }
        else {
            alturaOriginalBase = (colunaAcima[0]).alturaAnterior;
        }

        // Atualizando as alturas da coluna que cai (novas posições na nova coluna)
        for(int i = 0; i < colunaAcima.size(); i++){
            colunaAcima[i].alturaAnterior = i; 
        }

        // Atualizando a coluna atual (sem a reliquia destruida e as que cairam)
        estadoNovo[i_coluna] = colunaAbaixo;

        // ..."e a relíquia mais a baixo na nova coluna sofre dano de queda igual à 
        // sua altura anterior"
        /* Processando o dano de altura e criando nova coluna */
        if(!colunaAcima.empty()){
            // Aplicando dano de queda usando a altura anterior
            colunaAcima[0].hpAtual -= alturaOriginalBase;
            
            // Processando danos em cascata
            // Quando uma reliquia na posição 0 é destruída pela queda inicial,
            // a próxima reliquia (que estava na posição 1) sofre dano igual a 1
            // (a distância que caiu). Se essa também é destruída, a próxima
            // (que estava na posição 2) sofre dano igual a 2, assim por diante.
            int posicao = 0;
            while((posicao < colunaAcima.size()) && (colunaAcima[posicao].hpAtual <= 0)){
                colunaAcima.erase(colunaAcima.begin() + posicao);
                if(posicao < colunaAcima.size()){
                    // Dano = distância da queda = posição que ocupava na coluna que cai
                    colunaAcima[posicao].hpAtual -= posicao;
                }
            }

            // Se ainda sobrou alguma reliquia apos os danos de altura, add. como nova
            // coluna
            if(!colunaAcima.empty()){
                estadoNovo.push_back(colunaAcima);
            }
        }
    }

    // Removendo colunas vazias do estado
    estadoNovo.erase(
        remove_if(estadoNovo.begin(), estadoNovo.end(),
                  [](const vector<Reliquia> &coluna) { return coluna.empty(); }),
        estadoNovo.end()
    );

    // Ordenando as colunas para deixar estados equivalentes realmente iguais
    sort(estadoNovo.begin(), estadoNovo.end());

    return estadoNovo;
}