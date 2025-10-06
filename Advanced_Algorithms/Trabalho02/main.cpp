#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
Implementar uma função que receba a lista de sistemas estelares e se-
leciona as conexões para formar a Malha de Túneis com o menor custo total de tensão
subespacial. Você deve resolver este problema usando um algoritmo guloso.

Algoritmo Parte 1:
1. Calcular a distância entre cada par de pontos
2. Ordernar as conexões por distância -> O(E log(E))
3. Kruskal
    3.1 Percorrer as conexões da menor para a maior. Adicionamos ela
    se ela não criar ciclo (Union Find). OBS: Paramos ao acharmos
    n - 1 arestas, n a quantidade de sistemas importantes
*/

/*
Implementar uma função que encontre o par de sistemas estelares mais
próximo em todo o aglomerado. Você deve resolver este problema usando um algoritmo
de divisão e conquista.

Algoritmo Parte 2:
1. Calcular a distância entre cada par de pontos
2. Mergesort nas distâncias
*/

/* Struct pra representar um sistema */
struct Sistema {
    string id; // Nome
    double x;
    double y;

    // Construtores
    Sistema() : id(""), x(0), y(0) {}  // Padrão
    Sistema(string nome, double a, double b){
        id = nome;
        x = a;
        y = b;
    }
};

/* Struct pra representar um aglomerado de sistemas */
struct Aglomerado {
    int quantSistemas;
    int quantSistemasImportantes;
    int tensaoMax;
    vector<Sistema> sistemas;

    // Construtor
    Aglomerado(int qSist, int qSistImp, int tMax, vector<Sistema> sist){
        quantSistemas = qSist;
        quantSistemasImportantes =  qSistImp;
        tensaoMax =  tMax;
        sistemas = sist;
    }
};

/* Struct para representar uma conexao/aresta */
struct Tunel {
    // Índices (do vetor de entrada) dos sistemas que compõem o tunel
    int i_sistema1;
    int i_sistema2;
    double distancia;

    Tunel(int i, int j, double d){
        // Ordem de entrada
        i_sistema1 = i;
        i_sistema2 = j;
        
        // Armazenando a distancia entre os pontos
        distancia = d;
    }

    // Função de comparação entre tuneis por distancia
    bool operator<(const Tunel &outroTunel) const {
        return distancia < outroTunel.distancia;
    }
};

/* Struct para detectar ciclos */
struct UnionFind {
    vector<int> pai;
    vector<int> rank;

    // Construtor (inicializa cada elemento como seu proprio conjunto)
    UnionFind(int n){
        pai.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++){
            pai[i] = i;
        }
    }

    // Encontra o representante (raiz) do conjunto de x
    int encontrar_raiz(int x){
        if(pai[x] != x){
            pai[x] = encontrar_raiz(pai[x]); // Compressao de caminho
        }
        return pai[x];
    }

    // Une os conjuntos de x e y
    // Retorna true se uniu (nao formou ciclo), false se ja estavam unidos (ciclo)
    bool unir_conjuntos(int x, int y){
        int raizX = encontrar_raiz(x);
        int raizY = encontrar_raiz(y);

        // Ja estao no mesmo conjunto (criaria ciclo)
        if(raizX == raizY){
            return false;
        }

        // Uniao por rank: coloca arvore menor embaixo da maior
        if(rank[raizX] < rank[raizY]){
            pai[raizX] = raizY;
        }
        else if(rank[raizX] > rank[raizY]){
            pai[raizY] = raizX;
        }
        else {
            pai[raizY] = raizX;
            rank[raizX]++;
        }

        return true;
    }
};

/* Funções */
// Retorna um vetor de sistemas e as informacoes do problema
Aglomerado construir_malha();
// Retorna a malha de túneis com o menor custo total de tensão subespacial (guloso)
vector<Tunel> kruskal(Aglomerado aglomerado);
// Calcula a distância entre cada par de sistemas de um aglomerado
vector<Tunel> calcular_distancias(vector<Sistema> sistemas,
                                int tensaoMax, int quantSistemas);
// Mergesort
void mergeSort(vector<Tunel> &tuneis, int i_esq, int i_dir);
void merge(vector<Tunel> &tuneis, int i_esq, int i_meio, int i_dir);

int main(void){
    int quantProblemas = 0;
    cin >> quantProblemas;

    while(quantProblemas != 0){
        /* Parte 1 */
        // Lendo a entrada
        Aglomerado aglomerado = construir_malha();

        // Kruskal c/ Union-Find
        vector<Tunel> malha = kruskal(aglomerado);

        // Saída da Parte 1
        for(int i = 0; i < malha.size(); i++){
            cout << aglomerado.sistemas[(malha[i]).i_sistema1].id << ", "
                << aglomerado.sistemas[(malha[i]).i_sistema2].id << ", "
                << fixed << setprecision(2) << (malha[i]).distancia << endl;
        }

        /* Parte 2 */
        // Calculando as distância entre todos os sistemas
        vector<Tunel> distancias = calcular_distancias(aglomerado.sistemas,
                            aglomerado.tensaoMax, aglomerado.quantSistemas);

        // MergeSort
        mergeSort(distancias, 0, distancias.size() - 1);

        // Saída da Parte 2
        cout << "Ponto de Ressonância: " <<  (aglomerado.sistemas[(distancias[0]).i_sistema1]).id <<
            ", " << (aglomerado.sistemas[(distancias[0]).i_sistema2]).id << ", " << fixed <<
            setprecision(2) << distancias[0].distancia << endl;

        cout << endl;

        quantProblemas--;
    }

    return 0;
}

/* Leitura da entrada */
// Retorna um vetor de sistemas e as informacoes do problema
Aglomerado construir_malha(){
    // Informações do aglomerado
    int quantSistemas, quantSistemasImportantes, tensaoMax;
    cin >> quantSistemas >> quantSistemasImportantes >> tensaoMax;

    vector<Sistema> aglomerado;

    // Informações da cada sistema
    string nome;
    double x, y;
    for(int i = 0; i < quantSistemas; i++){
        cin >> nome >> x >> y;

        // Inserindo sistema no aglomerado
        aglomerado.push_back(Sistema(nome, x, y));
    }

    return Aglomerado(quantSistemas, quantSistemasImportantes, tensaoMax, aglomerado);
}

/* Kruskal c/ Union-Find */
// Retorna a malha de túneis com o menor custo total de tensão subespacial (guloso)
vector<Tunel> kruskal(Aglomerado aglomerado){
    /* Cálculo das conexões entre os sistemas importantes */
    // Calculando as distâncias dos sistemas importantes
    vector<Tunel> tuneis = calcular_distancias(aglomerado.sistemas, aglomerado.tensaoMax,
                                            aglomerado.quantSistemasImportantes);

    // Ordenando as conexões pelas distâncias (crescente)
    stable_sort(tuneis.begin(), tuneis.end());
    
    /* Montando a malha dos tuneis com menores distâncias */
    vector<Tunel> malha;
    UnionFind unionFind(aglomerado.quantSistemasImportantes);
    int quantTuneis = 0;

    // Percorre as conexões em ordem crescente de distância
    for(int i = 0; i < tuneis.size(); i++){
        int sistema1 = tuneis[i].i_sistema1;
        int sistema2 = tuneis[i].i_sistema2;
        
        // Tenta unir os dois sistemas
        if(unionFind.unir_conjuntos(sistema1, sistema2)){
            // Não formou ciclo, adiciona à malha essencial
            malha.push_back(tuneis[i]);
            quantTuneis++;
            
            // Árvore geradora tem n-1 arestas
            if(quantTuneis == aglomerado.quantSistemasImportantes - 1){
                break;
            }
        }
    }
    
    return malha;  
}

/* Calcula a distância entre cada par de sistemas de um aglomerado */
vector<Tunel> calcular_distancias(vector<Sistema> sistemas, int tensaoMax, int quantSistemas){
    vector<Tunel> tuneis;

    // Distâncias dos sistemas importantes
    double distancia;
    for(int i = 0; i < quantSistemas; i++){
        for(int j = i + 1; j < quantSistemas; j++){
            distancia = sqrt(pow(sistemas[i].x - sistemas[j].x, 2) +
                            pow(sistemas[i].y - sistemas[j].y, 2));
            
            // Só consideramos as conexões com valor menor que a tensão máxima
            if(distancia <= tensaoMax){
                tuneis.push_back(Tunel(i, j, distancia));
            }
        }
    }

    return tuneis;
}

void mergeSort(vector<Tunel> &tuneis, int i_esq, int i_dir){
    // Caso base
    if(i_esq >= i_dir){
        return;
    }

    int i_meio = i_esq + ((i_dir - i_esq) / 2);
    // Divisão
    mergeSort(tuneis, i_esq, i_meio);
    mergeSort(tuneis, i_meio + 1, i_dir);
    // Conquista
    merge(tuneis, i_esq, i_meio, i_dir);

    return;
}

/* Junta dois vetores de tuneis, ordenando-os pela distância (crescente) */
void merge(vector<Tunel> &tuneis, int i_esq, int i_meio, int i_dir){
    /* Vetores auxiliares temporários */
    int tam_esq = i_meio - i_esq + 1;
    int tam_dir = i_dir - i_meio;
    vector<Tunel> vetor_esq, vetor_dir;

    // Copiando o vetor original pros temporários
    for(int i = 0; i < tam_esq; i++){
        vetor_esq.push_back(tuneis[i_esq + i]);
    }
    for(int i = 0; i < tam_dir; i++){
        vetor_dir.push_back(tuneis[i_meio + 1 + i]);
    }

    // Indices para percorrer o vetor
    int i = 0, j = 0;
    int k = i_esq;

    // Juntando os vetores temporarios no principal
    while((i < tam_esq) && (j < tam_dir)){
        if(vetor_esq[i].distancia <= vetor_dir[j].distancia){
            tuneis[k] = vetor_esq[i];
            i++;
        }
        else{
            tuneis[k] = vetor_dir[j];
            j++;
        }
        
        k++;
    }

    // Copia os elementos restantes de vetor_esq
    while(i < tam_esq){
        tuneis[k] = vetor_esq[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de vetor_dir
    while(j < tam_dir){
        tuneis[k] = vetor_dir[j];
        j++;
        k++;
    }

    return;
}