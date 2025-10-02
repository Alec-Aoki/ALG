#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

/*
É dado um conjunto de pedras identificadas pelas propriedades:
    - Energia Arcana (E)
    - Vibração Mística (V)
Podendo ser interpretadas como um par de coordenadas num plano bidimensional.
O objetivo é definir o conjunto de pedras que formam o fecho convexo mínimo,
seguindo as regras:
    1. O fecho convexo deve ser percorrido no sentido anti-horário.
    2. O ponto inicial deve ser a pedra com menor valor de Ei.
    3. Em caso de empate no menor Ei, escolher a pedra com menor valor de Vi.
    4. Se houver colinearidade entre pedras na borda do fecho convexo, todas essas
    pedras devem ser incluídas na solução, respeitando a ordem crescente de Ei.
    5. Os valores de Ei e Vi devem ser considerados com até 4 casas decimais para fins de
    comparação.

Algoritmos para construção de fecho convexo:
    - Incremental
    - Gift wrapping
    - Varredura de Graham <----
    - Dividir e conquistar
*/

const double EPSILON = 1e-4;

double produtoVetorial(const pair<double, double>& p0, 
                    const pair<double, double>& p1, 
                    const pair<double, double>& p2);

double distanciaQuadrado(const pair<double, double>& p1, 
                        const pair<double, double>& p2);

int orientacao(const pair<double, double>& a, 
               const pair<double, double>& b, 
               const pair<double, double>& c);

vector<pair<double, double>> fecho_convexo(vector<pair<double,
                                        double>> vetor_pontos);


int main (void){  
    int quantCasosTeste = 0;
    int quantPedras = 0;
    vector<pair<double, double>> vetor_pedras;
    double E; // Energia Arcana (x)
    double V; // Vibração Mística (y)

    cin >> quantCasosTeste;
    for(int i = 0; i < quantCasosTeste; i++){
        cin >> quantPedras;

        /* Lendo os pares de coord. */
        for(int j = 0; j < quantPedras; j++){
            cin >> E >> V;
            // Inserindo cada par em vetor_pedras
            vetor_pedras.push_back(make_pair(E, V));
        }

        vector<pair<double, double>> vetor_res = fecho_convexo(vetor_pedras);

        cout << "Caso " << (i + 1) << ":" << endl;
        cout << "Tamanho do colar: " << vetor_res.size() << endl;
        cout << "Pedras ancestrais: ";
        cout << fixed << setprecision(4);
        for(int j = 0; j < vetor_res.size(); j++){
            cout << "(" << vetor_res[j].first << "," << vetor_res[j].second << ")";
            if(j < vetor_res.size() - 1){
                cout << ",";
            }
        }
        cout << endl << endl;

        /* Limpeza de variáveis */
        vetor_pedras.clear();
    }

    return 0;
}

/* Calcula o produto vetorial de vetores OA e OB onde O = p0, A = p1, B = p2 */
double produtoVetorial(const pair<double, double>& p0, 
                       const pair<double, double>& p1, 
                       const pair<double, double>& p2) {
    double dx1 = p1.first - p0.first;
    double dy1 = p1.second - p0.second;
    double dx2 = p2.first - p0.first;
    double dy2 = p2.second - p0.second;
    return dx1 * dy2 - dy1 * dx2;
}

/* Distância ao quadrado entre dois pontos */
double distanciaQuadrado(const pair<double, double>& p1, 
                         const pair<double, double>& p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return dx * dx + dy * dy;
}

/* Verifica orientação de três pontos */
// Retorna: > 0 se anti-horário, < 0 se horário, 0 se colinear
int orientacao(const pair<double, double>& a, 
               const pair<double, double>& b, 
               const pair<double, double>& c) {
    double val = produtoVetorial(a, b, c);
    if (abs(val) < EPSILON) return 0;
    return (val > 0) ? 1 : -1;
}

/* Constroi o fecho convexo usando Varredura de Graham */
vector<pair<double, double>> fecho_convexo(vector<pair<double, double>> vetor_pontos) {
    int quantPontos = vetor_pontos.size();
    if (quantPontos < 3) return vetor_pontos;
    
    // Encontrando o ponto com menor E (e menor V em caso de empate)
    int idx_pontoInicial = 0;
    for (int i = 1; i < quantPontos; i++) {
        if (vetor_pontos[i].first < vetor_pontos[idx_pontoInicial].first - EPSILON ||
            (abs(vetor_pontos[i].first - vetor_pontos[idx_pontoInicial].first) < EPSILON && 
             vetor_pontos[i].second < vetor_pontos[idx_pontoInicial].second - EPSILON)) {
            idx_pontoInicial = i;
        }
    }
    swap(vetor_pontos[0], vetor_pontos[idx_pontoInicial]);
    pair<double, double> ponto_pivo = vetor_pontos[0];
    
    // Ordenando pontos por ângulo polar em relação ao pivo
    sort(vetor_pontos.begin() + 1, vetor_pontos.end(), 
         [&ponto_pivo](const pair<double, double>& a, const pair<double, double>& b) {
        int o = orientacao(ponto_pivo, a, b);
        if (o == 0) {
            // Se colineares, ordenar por distância ao pivo
            return distanciaQuadrado(ponto_pivo, a) < distanciaQuadrado(ponto_pivo, b);
        }
        return o > 0;
    });
    
    // Incluindo todos os pontos colineares no final
    // Precisamos verificar se todos os pontos são colineares com o pivo
    bool todosColineares = true;
    for (int i = 1; i < quantPontos; i++) {
        if (orientacao(ponto_pivo, vetor_pontos[i], vetor_pontos[quantPontos-1]) != 0) {
            todosColineares = false;
            break;
        }
    }
    
    if (!todosColineares) {
        // Encontrando o último grupo de pontos colineares no final
        int idx_ultimoNaoColinear = quantPontos - 1;
        while (idx_ultimoNaoColinear > 0 && 
               orientacao(ponto_pivo, vetor_pontos[idx_ultimoNaoColinear], 
                         vetor_pontos[quantPontos-1]) == 0) {
            idx_ultimoNaoColinear--;
        }
        // Revertendo a ordem dos pontos colineares finais para manter ordem crescente de E
        reverse(vetor_pontos.begin() + idx_ultimoNaoColinear + 1, vetor_pontos.end());
    }
    // Se todos são colineares, já estão ordenados por distância (ordem crescente de E)
    
    // Construindo o fecho convexo
    vector<pair<double, double>> vetor_fecho;
    vetor_fecho.push_back(vetor_pontos[0]);
    
    for (int i = 1; i < quantPontos; i++) {
        // Removendo pontos que fazem curva à direita (sentido horário)
        while (vetor_fecho.size() > 1 && 
               orientacao(vetor_fecho[vetor_fecho.size()-2], 
                         vetor_fecho[vetor_fecho.size()-1], 
                         vetor_pontos[i]) < 0) {
            vetor_fecho.pop_back();
        }
        vetor_fecho.push_back(vetor_pontos[i]);
    }
    
    return vetor_fecho;
}