#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <set>
using namespace std;

/* Struct de comparação do set */
// Compara os segundo valor do set (double), ordenando
// em ordem DECRESCENTE
struct cmp_dias{
    bool operator ()(const pair<string, double> &a,
                    const pair<string, double> &b) const
    {
        return a.second > b.second;
    }
};

/* Struct de comparação da data */
// Compara duas datas por ano, mês e dia
struct cmp_datas{
    bool operator ()(const string &a,
                    const string &b) const
    {
        // Extrair dia, mês e ano da primeira data
        int dia_a = stoi(a.substr(0, 2));
        int mes_a = stoi(a.substr(3, 2));
        int ano_a = stoi(a.substr(6, 4));
        
        // Extrair dia, mês e ano da segunda data
        int dia_b = stoi(b.substr(0, 2));
        int mes_b = stoi(b.substr(3, 2));
        int ano_b = stoi(b.substr(6, 4));
        
        // Comparar por ano primeiro
        if(ano_a != ano_b) {
            return ano_a < ano_b;
        }
        
        // Se anos iguais, comparar por mês
        if(mes_a != mes_b) {
            return mes_a < mes_b;
        }
        
        // Se anos e meses iguais, comparar por dia
        return dia_a < dia_b;
    }
};

int main(void){
    int quantCasosTeste;
    cin >> quantCasosTeste;

    int quantDias = 0;
    string data = "";
    double valorDia = 0;
    double somaDias = 0;
    double somaRes = 0;
    set<pair<string, double>, cmp_dias> dias;
    set<string, cmp_datas> diasRes;

    for(int i = 0; i < quantCasosTeste; i++){
        cin >> quantDias;

        /* Entrada de cada dia */
        for(int j = 0; j < quantDias; j++){
            // Lendo data e valor
            cin >> data >> valorDia;

            // Inserindo par (data, valor) no set
            dias.insert(make_pair(data, valorDia));
            somaDias += valorDia;
        }

        /* Algoritmo guloso */
        // Percorremos o set (ordem descrescente), guardando as
        // informações do dia com maior lucro até que a soma
        // dos dias guardados ultrapasse o restante
        set<pair<string, double>>::iterator it = dias.begin();
        // (*it) é um pair
        while((somaDias >= somaRes) && (it != dias.end())){
            // Somando o valor do dia à resposta final
            somaRes += (*it).second;

            // Subtraindo o valor do dia à soma dos dias
            somaDias -= (*it).second;

            // Inserindo a data no set de respostas
            diasRes.insert((*it).first);

            // Indo para o próximo pair do set de dias
            it++;
        }

        /* Saída */
        cout << diasRes.size();
        if(diasRes.size() == 1){
            cout << " dia (";
        } else {
            cout << " dias (";
        }

        // Imprimindo as datas separadas por vírgula
        int k = 0;
        for(set<string>::iterator it2 = diasRes.begin();
            it2 != diasRes.end(); it2++)
        {
            cout << *it2;
            if(k < diasRes.size() - 1){
                cout << ", ";
            }
            k++;
        }
        cout << ") | soma=" << fixed << setprecision(2) << somaRes;

        // Calculando e imprimindo a porcentagem
        double porcentagem = (double)diasRes.size() / quantDias * 100.0;
        cout << " | " << fixed << setprecision(2) << porcentagem
            << "% dos dias totais" << endl;

        dias.clear();
        diasRes.clear();
        data.clear();
        valorDia = 0;
        somaDias = 0;
        somaRes = 0;
    }

    return 0;
}

