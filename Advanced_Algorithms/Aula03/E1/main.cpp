#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef struct{
    int id = -1;
    bool temDoenca = false;
    int idPai = -1;
    int idMae = -1;
} Pessoa;

Pessoa ler_pessoa(void){
    Pessoa pessoa;
    string temDoenca;

    cin >> pessoa.id >> temDoenca >> pessoa.idPai >> pessoa.idMae;

    if(temDoenca == "sim") pessoa.temDoenca = true;
    else pessoa.temDoenca = false;

    return pessoa;
}

bool herdeiro(Pessoa filho, Pessoa pai, Pessoa mae){
    if(filho.temDoenca && (pai.temDoenca || mae.temDoenca)) return true;

    return false;
}

int main(void){
    int quantCasosTeste = 0;
    cin >> quantCasosTeste;

    int quantPessoasArvore = 0;
    int quantHerdeiros = 0;
    map<int, Pessoa> arvore;
    for(int i = 0; i < quantCasosTeste; i++){
        cin >> quantPessoasArvore;
        for(int j = 0; j < quantPessoasArvore; j++){
            Pessoa novaPessoa = ler_pessoa();
            arvore.insert({novaPessoa.id, novaPessoa});
        }

        for(pair<int, Pessoa> par : arvore){
            Pessoa pessoa = par.second;

            if(pessoa.idPai != -1 && pessoa.idMae != -1){
                if(herdeiro(pessoa, arvore.at(pessoa.idPai), arvore.at(pessoa.idMae))) quantHerdeiros++;
            }
        }

        cout << quantHerdeiros << endl;

        arvore.clear();
        quantHerdeiros = 0;
    }

    return 0;
}