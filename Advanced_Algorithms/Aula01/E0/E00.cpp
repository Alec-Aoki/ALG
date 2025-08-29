#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
O que será necessário guardar?
O código do produto e seu $/kg
    -> 2 listas, pares de índices
    -> 1 lista de pares => map e pair

Algoritmo de cadastro:
    Ler código e $/kg
    Verificar se já existe
        Se sim: "Produto com código #XXXX já cadastrado."
        Senão: Incluir par na lista

Algoritmo de venda:
    Ler quantidade de itens
        Se -1: fechar programa
        Senão: continuar
    Ler código e peso
    Verificar se o código existe
        Se sim: calcular valor e adicionar no total
        Senão "Produto com código #XXXX não cadastrado."
*/

int main(void){
    int quantItenCadastrados = 0;
    int quantItensComprados = 0;

    cin >> quantItenCadastrados;
    if(quantItenCadastrados < 0) return 0;

    map<string, float> itensCadastrados;

    /* Cadastro dos itens */
    float precoItem = 0;
    string codigoItem = "";
    for(int i = 0; i < quantItenCadastrados; i++){
        cin >> codigoItem >> precoItem;

        if(itensCadastrados.find(codigoItem) == itensCadastrados.end()){
            // Código novo (cadastrando)
            itensCadastrados.insert({codigoItem, precoItem});
        } else {
            // Código já cadastrado
            cout << "Produto com código " << codigoItem << " já cadastrado." << endl;
        }        
    }

    /* Venda dos produtos */
    float pesoItem = 0;
    float valorTotal = 0;
    // Vamos reutilizar a string codigoItem!
    while(true){
        cin >> quantItensComprados;
        if(quantItensComprados == -1) break;

        for(int i = 0; i < quantItensComprados; i++){
            cin >> codigoItem >> pesoItem;
            map<string, float>::iterator it = itensCadastrados.find(codigoItem);

            if(it == itensCadastrados.end()){
                // Código não existe
                cout << "Produto com código " << codigoItem << " não cadastrado." << endl;
                
            } else {
                valorTotal += pesoItem*(it->second);
            }
        }

        printf("R$%.2f\n", valorTotal);
        valorTotal = 0;
    }
    
    return 0;
}