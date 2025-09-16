#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <map>
#include <queue>
#include <iomanip>
#include <limits>
using namespace std;

/*
Nível       | Produtividade | Descrição
--------------------------------------------
Aprendiz    | 0,75x        | Heróis em treinamento, levam mais tempo que o normal.
Aventureiro | 1x            | Experientes em combate, completam quests no tempo base (normal).
Cavaleiro   | 1,2x          | Heróis veteranos, completam quests 20% mais rápido.
Mestre      | 1,5x          | Mestres da aventura, completam quests 50% mais rápido.
Lenda       | 2x           | Heróis lendÃ¡rios, completam quests duas vezes mais rápido.
*/

/*
Algoritmo
1. Ordernar as quests de acordo com as dependências (topological sort)
2. Alocar cada tarefa para o melhor herói disponÃ­vel (guloso)
*/

/* Structs */
struct QUEST {
    int indice;
    int tempoBase;
    vector<int> id_dependencias; // Ids das quests da qual depende
};

struct HEROI {
    string nome;
    double produtividade;
    vector<int> id_quests;
};

/* FunÃ§Ãµes auxiliares */
QUEST ler_quest();
vector<vector<int>> constructadj(int quantQuests, vector<QUEST> &vetor_quests, map<int, int> &idToIndex);
vector<int> topologicalSort(int quantQuests, vector<QUEST> &vetor_quests);

int main(void){
    int quantCasosTeste = 0;
    cin >> quantCasosTeste;

    int quantHerois = 0;
    int quantQuests = 0;

    HEROI heroi;
    string nivel;
    vector<HEROI> vetor_herois;

    vector<QUEST> vetor_quests; 
    QUEST quest;

    while(quantCasosTeste > 0){
        cin >> quantHerois >> quantQuests;
        cin.ignore();

        /* Leitura dos herÃ³is */
        for(int i = 0; i < quantHerois; i++){
            cin >> heroi.nome >> nivel;

            if(nivel == "Aprendiz") heroi.produtividade = 0.75;
            else if (nivel == "Aventureiro") heroi.produtividade = 1.0;
            else if (nivel == "Cavaleiro") heroi.produtividade = 1.2;
            else if (nivel == "Mestre") heroi.produtividade = 1.5;
            else if (nivel == "Lenda") heroi.produtividade = 2.0;

            // Inserindo num vetor
            vetor_herois.push_back(heroi);
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        /* Leitura das quests */
        for(int i = 0; i < quantQuests; i++){
            quest = ler_quest();
            
            // Inserindo cada quest no vetor
            vetor_quests.push_back(quest);
            
            quest.id_dependencias.clear();
        }

        /* Topological Sort */
        // Ordenando as quests por prioridade
        // Quanto mais quests dependerem de uma quest, maior sua prioridade
        vector<int> ordem_topologica = topologicalSort(quantQuests, vetor_quests);
        vector<QUEST> vetor_quests_ordenadas;
        for(int indice : ordem_topologica) {
            vetor_quests_ordenadas.push_back(vetor_quests[indice]);
        }

        /* Guloso - Alocação das quests aos heróis */
        vector<double> vetor_tempoHerois(quantHerois, 0); // Vetor que guarda o tempo de execução de cada herói
        map<int, double> map_tempo_completa; // Mapeia ID da quest para o tempo quando ela é concluída
        
        // Para cada quest na ordem topológica
        for(const QUEST &quest_atual : vetor_quests_ordenadas){
            double menorTempoTotal = -1;
            int indiceMelhorHeroi = 0;
            
            // Simular o tempo de execução para cada herói
            double tempoQuestHeroi = 0;
            double tempoTotalSim = 0;
            for(int i = 0; i < quantHerois; i++){
                tempoQuestHeroi = quest_atual.tempoBase / vetor_herois[i].produtividade;
                
                // Calcular quando este herói pode iniciar essa quest
                double tempoInicioMaisCedo = vetor_tempoHerois[i];
                
                // Verificar dependências
                for(int id_dependencia : quest_atual.id_dependencias) {
                    if(map_tempo_completa.find(id_dependencia) != map_tempo_completa.end()) {
                        tempoInicioMaisCedo = max(tempoInicioMaisCedo, map_tempo_completa[id_dependencia]);
                    }
                }
                
                tempoTotalSim = tempoInicioMaisCedo + tempoQuestHeroi;
                
                // Se esse herÃ³i resultaria em menor tempo total, escolhe ele
                if(menorTempoTotal == -1 || tempoTotalSim < menorTempoTotal){
                    menorTempoTotal = tempoTotalSim;
                    indiceMelhorHeroi = i;
                }

                tempoQuestHeroi = 0;
                tempoTotalSim = 0;
            }
            
            // Atribuir a quest ao melhor herói
            double tempoQuest = quest_atual.tempoBase / vetor_herois[indiceMelhorHeroi].produtividade;
            
            // Calcular quando este herói pode realmente iniciar
            double tempoInicioMaisCedo = vetor_tempoHerois[indiceMelhorHeroi];
            for(int id_dependencia : quest_atual.id_dependencias) {
                if(map_tempo_completa.find(id_dependencia) != map_tempo_completa.end()) {
                    tempoInicioMaisCedo = max(tempoInicioMaisCedo, map_tempo_completa[id_dependencia]);
                }
            }
            
            // Atualizar o tempo do herói e registrar quando a quest não concluída
            vetor_tempoHerois[indiceMelhorHeroi] = tempoInicioMaisCedo + tempoQuest;
            map_tempo_completa[quest_atual.indice] = tempoInicioMaisCedo + tempoQuest;
            vetor_herois[indiceMelhorHeroi].id_quests.push_back(quest_atual.indice);
        }

        /* Calcular e imprimir o tempo total máximo */
        double tempoTotalMax = 0;
        for(double tempo : vetor_tempoHerois){
            tempoTotalMax = max(tempoTotalMax, tempo);
        }

        for(int i = 0; i < quantHerois; i++){
            cout << vetor_herois[i].nome << " = {";
            for(int j = 0; j < vetor_herois[i].id_quests.size(); j++){
                cout << vetor_herois[i].id_quests[j];
                if(j != vetor_herois[i].id_quests.size() - 1) cout << ",";
            }
            cout << "}" << endl;
        }
        
        cout << fixed << setprecision(2) << "Tempo mínimo: " << tempoTotalMax << endl;
        if (quantCasosTeste != 1) cout << endl;

        /* Limpeza das variáveis */
        quest.indice = -1;
        quest.tempoBase = -1;
        quest.id_dependencias.clear();
        vetor_quests.clear();
        vetor_herois.clear();

        quantCasosTeste--;
    }

    return 0;
}

/* Função pra ler a linha de uma quest e separar seus campos */
QUEST ler_quest(){
    string linha = "";
    QUEST quest;

    getline(cin, linha); // Lendo a linha inteira
    stringstream ss(linha);
    
    // Separando os dois primeiros valores
    ss >> quest.indice >> quest.tempoBase;
    
    // Pegando os ids das dependencias da quest
    int dependencia;
    while(ss >> dependencia){
        if(dependencia != 0){  // 0 indica fim das dependências
            quest.id_dependencias.push_back(dependencia);
        }
    }

    return quest;
}

// Construir lista adjacente das dependências das quests
vector<vector<int>> constructadj(int quantQuests, vector<QUEST> &vetor_quests, map<int, int> &idToIndex){
    vector<vector<int>> adj(quantQuests);
    
    for (const QUEST &quest : vetor_quests){
        // Para cada dependência da quest, add. um vértice da dependência pra quest
        for (int dependencia : quest.id_dependencias){
            // Usar os Ã­ndices mapeados ao invÃ©s dos IDs diretos
            if(idToIndex.find(dependencia) != idToIndex.end() && 
               idToIndex.find(quest.indice) != idToIndex.end()) {
                int depIndex = idToIndex[dependencia];
                int questIndex = idToIndex[quest.indice];
                adj[depIndex].push_back(questIndex);
            }
        }
    }

    return adj;
}

// Topological Sort usando Kahn's Algorithm (BFS)
vector<int> topologicalSort(int quantQuests, vector<QUEST> &vetor_quests){
    // Criar mapeamento de ID para Ã­ndice
    map<int, int> idToIndex;
    for(int i = 0; i < vetor_quests.size(); i++) {
        idToIndex[vetor_quests[i].indice] = i;
    }
    
    vector<vector<int>> adj = constructadj(quantQuests, vetor_quests, idToIndex);
    vector<int> indegree(quantQuests, 0);
    
    // Calcular o indegree (número de dependências) de cada quest
    for(int i = 0; i < quantQuests; i++) {
        for(int vizinho : adj[i]) {
            indegree[vizinho]++;
        }
    }
    
    // Usar uma fila para processar as quests que não têm dependências
    // Para manter a ordem de entrada, vamos usar uma fila comum mas processar
    // as quests na ordem original quando têm o mesmo nível de dependência
    queue<int> q;
    
    // Adicionar todas as quests sem dependência na fila, 
    // mas na ordem que aparecem no input original
    for(int i = 0; i < quantQuests; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    
    while(!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);
        
        // Para cada quest que depende da atual
        for(int vizinho : adj[current]) {
            indegree[vizinho]--;
            if(indegree[vizinho] == 0) {
                q.push(vizinho);
            }
        }
    }
    
    return result;
}