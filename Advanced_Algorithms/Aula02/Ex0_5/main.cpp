#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <utility>

using namespace std;

#define PI 3.14159265358979323851
#define R 6371 // km

/*
1. Calcular distância do palpite até o ponto correto utilizando
a FÓRMULA DE HAVERSINE;
2. Utilizar uma PRIORITY QUEUE para identificar o melhor palpite
e exibir um aviso;
    2.1 Em caso de empate, respeitar ordem de entrada;
3. Gerar ranking completo dos jogadores;
*/

/*TODO
- Como guardar os ngcs do ranking
*/

/* Distância segundo a fórmula de haversine */
long double haversine(double latC, double lonC, double lat, double lon){
    /* Conversão graus -> rad */
    lat = lat * PI / 180;
    lon = lon * PI / 180;

    long double p1 = sin((lat - latC)/2) * sin((lat - latC)/2);
    long double p2 = cos(lat) * cos(latC) * sin((lon - lonC)/2) * sin((lon - lonC)/2);
    long double d = 2 * R * asin(sqrt(p1 + p2));

    return d;
}

/* Print do ranking final (gambiarra kk) */
void print_rank(int posicao, string nome, long double distancia){
    /* Posição e nome */
    if (posicao < 10) cout << " ";
    cout << posicao << ". " << nome;

    /* Espaço */
    int numEspacos = 20;
    for(int i = 0; i < (numEspacos - nome.size()); i++) cout << " ";
    cout << " : ";

    /* Espaço */
    if (distancia < 10) cout << " ";
    
    /* Distância */
    printf("%.3Lf km", distancia);

    /* Fantástico */
    if(distancia < 0.05) cout << " [FANTASTICO]";

    return;
}

int main(void){
    int quantJogadores = 0; // 1 .. 100_000
    double latCorreta = 0; // -90 .. 90
    double lonCorreta = 0; // -180 .. 180

    cin >> quantJogadores;
    cin >> latCorreta >> lonCorreta;

    /* Conversão graus -> rad */
    latCorreta = latCorreta * PI / 180;
    lonCorreta = lonCorreta * PI / 180;
    string nickname = "";
    double lat = 0;
    double lon = 0;
    long double dist = 0;
    // Min-heap (top = menor valor) de pares (distância, nickname)
    priority_queue<pair<long double, string>, vector<pair<long double, string>>, greater<pair<long double, string>>> filaPrioridade;

    for(int i = 0; i < quantJogadores; i++){
        cin >> nickname >> lat >> lon;

        // Calculando distância via haversine
        dist = haversine(latCorreta, lonCorreta, lat, lon);

        // Add. na fila
        filaPrioridade.push({dist, nickname});

        printf("> [AVISO] MELHOR PALPITE: %.3Lfkm\n", (filaPrioridade.top()).first);
    }

    cout << endl << "RANKING" << endl << "-------" << endl;
    pair<long double, string> parTemporario;
    for(int i = 1; i <= quantJogadores; i++){
        parTemporario = filaPrioridade.top();
        print_rank(i, parTemporario.second, parTemporario.first);
        if(i != quantJogadores) cout << endl;

        filaPrioridade.pop();
    }
    
    return 0;
}
