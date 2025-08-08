#include <iostream>
#include <string> // Biblioteca para o uso de strings
#include <list>   // Listas LIGADAS (!)
#include <vector> // Vetores CONTÍNUOS (!)
#include <map> // Map
#include <algorithm> // Sort

using namespace std;

/* Templates */
// Funções que funcionam com qualquer tipo de dado
template <typename T>
T add(T a, T b){
    return (a + b);
}

/* Functor */
// Objeto que se comporta como uma função
struct ExFunctor{
    // Operator muda o que um operador faz dentro
    // do contexto.
    // ex: operator()+ muda o que o + faz
    bool operator()(string a, string b){
        return (b < a);
    }
};

int main(void){
    /* Entrada e saída */
    string nome = "Alec";
    // cin >> nome;
    cout << "Hello " << nome << "!" << endl;
    cout << endl;

    float a = 10, b = 20.5;
    cout << add(a, b) << endl;
    cout << endl;

    /* Listas */
    list<int> listaInt;
    listaInt.push_back(10);
    listaInt.push_front(3);
    // Insert
    // listaInt.insert(listaInt.begin()++, 1); // .begin() indica o ponteiro da lista
    // OBS: Iteradores não aceitam aritmética, só incrementadores

    /* Iteradores */
    // Ponteiros
    // https://www.w3schools.com/cpp/cpp_iterators.asp
    for(list<int>::iterator it = listaInt.begin(); it != listaInt.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    // Outra versão
    for(int x : listaInt){
        cout << x << " ";
    }
    cout << endl;
    // OBS: se o tipo for óbvio para o compilador, podemos definir o tipo da variável
    // como auto
    for(auto x : listaInt){
        cout << x << " ";
    }
    cout << endl << endl;

    /* Vetores */
    vector<string> vetStrings;
    vetStrings.push_back("Oi1");
    vetStrings.push_back("Oi2");
    cout << vetStrings[0] << " " << vetStrings[1] << endl;
    cout << vetStrings.capacity() << endl << endl;

    /* Mapas */
    // Ordenação automática (árvore)
    // Unordored map: sem ordenação (hash?)
    map<string, float> mapa;
    mapa.insert(pair<string, float>("Aula01", 1.0));
    mapa.insert(pair<string, float>("Aula02", 2.0));
    for(auto par : mapa){
        cout << par.first << endl;
        cout << par.second << endl;
    }
    cout << endl;

    /* Sort e Functor */
    sort(vetStrings.begin(), vetStrings.end(), ExFunctor());
    cout << vetStrings[0] << " " << vetStrings[1] << endl; // Oi2 Oi1
    // Mesma coisa
    sort(vetStrings.begin(), vetStrings.end(), [] (string a, string b){
        return (b < a);
    });
    cout << vetStrings[0] << " " << vetStrings[1] << endl; // Oi2 Oi1

    return 0;
}