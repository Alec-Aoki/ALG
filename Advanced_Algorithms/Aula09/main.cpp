#include <iostream>
#include <vector>
using namespace std;

/*
Para cada relíquia i (de baixo para cima), guardamos dois valores:
    - batidasDiretas[i]: menor número de batidas para destruir essa relíquia manualmente
    - batidasPorQueda[i]: menor número de batidas se essa relíquia for destruída pela queda
*/

int main() {
    int quantidadeReliquias;
    cin >> quantidadeReliquias;

    vector<long long> estabilidade(quantidadeReliquias + 1);
    for (int i = 1; i <= quantidadeReliquias; i++) {
        cin >> estabilidade[i];
    }

    // Vetores da DP
    vector<long long> batidasDiretas(quantidadeReliquias + 1, 0);
    vector<long long> batidasPorQueda(quantidadeReliquias + 1, 0);

    // Casos base (pra iniciar a DP)
    batidasDiretas[0] = 0;
    batidasPorQueda[0] = 1;

    for (int i = 1; i <= quantidadeReliquias; i++) {
        // Caso 1: Destruimos a relíquia i manualmente
        // Pode vir de qualquer situação anterior (batida ou por queda)
        batidasDiretas[i] = min(batidasDiretas[i - 1], batidasPorQueda[i - 1]) + estabilidade[i];

        // Caso 2: A relíquia i será destruída pela queda
        // Existem duas possibilidades:
        // - A de baixo também caiu -> ela sofre 1 de dano pela queda
        // - A de baixo foi destruída manualmente -> ela sofre (i - 1) de dano, a altura da queda
        long long opcao1 = batidasPorQueda[i - 1] + (estabilidade[i] - 1);
        long long opcao2 = batidasDiretas[i - 1] + max(estabilidade[i] - (i - 1), 0LL);

        batidasPorQueda[i] = min(opcao1, opcao2);
    }

    long long respostaFinal = min(batidasDiretas[quantidadeReliquias], batidasPorQueda[quantidadeReliquias]);
    cout << respostaFinal << "\n";

    return 0;
}
