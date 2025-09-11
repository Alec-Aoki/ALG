#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

/*
Dado o registro das solicitações de aluguel, o programa deve analisar cada modelo de
carro e determinar qual é a quantidade máxima de clientes que poderão alugá-lo sem
sobreposição de horários de retirada e devolução de maneira gulosa. Além disso, deve
indicar quais clientes terão suas solicitações atendidas, apresentando-os na ordem em que
o atendimento poderá ser realizado.
*/

/*
Algoritmo: pegar as reservas com o "menor" horário de devolução
1. Ordernar as structs RESERVA de acordo com o horarioDevolucao (set com comparação especial)
2. Criar um array resposta pra cada modelo que vai guardar as reservas incluídas para aquele modelo
3. Criar uma variável ultimaDevolucao que vai guardar o horarioDevolucao incluído por último (pra cada modelo)
4. Comparar o horario de inicio com a variável ultimaDevolucao (pra cada modelo)
*/

// Struct pra guardar cada reserva (input)
struct RESERVA {
    int idCliente;
    string horarioRetirada;
    string horarioDevolucao;
    int modeloCarro;
};

// Struct pra comparar reservas pelo horário de devolução (ordem crescente)
struct cmp_reservas{
    bool operator ()(const RESERVA &res1, const RESERVA &res2) const {
        if(res1.horarioDevolucao == res2.horarioDevolucao) {
            if (res1.horarioRetirada == res2.horarioRetirada) return res1.idCliente < res2.idCliente;
            // Else
            return res1.horarioRetirada < res2.horarioRetirada;
        }
        return res1.horarioDevolucao < res2.horarioDevolucao;
    }
};

int main(void){
    int quantCasosTeste = 0;
    cin >> quantCasosTeste;

    // Variáveis de cada caso teste
    int quantModelos = 0;
    int quantSolicitacoes = 0;

    set<RESERVA, cmp_reservas> setReservas;
    RESERVA reserva;

    // Vetor que vai guardar o setResposta de cada modelo
    map<int, set<RESERVA, cmp_reservas>> vetModelos;
    // Vetor que vai guardar a última devolução de cada modelo
    map<int, string> vetUltimaDevolucao;

    for(int i = 0; i < quantCasosTeste; i++){
        cin >> quantModelos;
        cin >> quantSolicitacoes;

        // Inicializando as estruturas de resposta
        for(int j = 1; j <= quantModelos; j++){
            vetUltimaDevolucao.insert({j, "00:00"}); // Inicializando as ultimasDevoluces de cada modelo como 00:00
            vetModelos.insert({j, set<RESERVA, cmp_reservas>()}); // Inicializando os sets de cada modelo
        }

        /*
        Cada uma das próximas M linhas descreve uma solicitação, composta por: um
        inteiro positivo identificando o cliente, um horário de retirada no formato HH:MM, um
        horário de devolução no formato HH:MM, e por fim um inteiro positivo representando
        o identificador do modelo de carro solicitado.
        */

        for(int j = 0; j < quantSolicitacoes; j++){
            // Leitura da entrada (direto na struct)
            cin >> reserva.idCliente >> reserva.horarioRetirada >> reserva.horarioDevolucao >> reserva.modeloCarro;

            // Inserindo struct no set
            setReservas.insert(reserva);
        }

        // 4. Comparar o horario de inicio com a variável ultimaDevolucao (pra cada modelo)
        for(int j = 1; j <= quantModelos; j++){
            // Pegando cada elemento de setReservas
            for(set<RESERVA>::iterator it = setReservas.begin(); it != setReservas.end(); it++){
                // Se o modelo do carro for o atual E
                // O horário de retirada do carro for maior que o a última devolução
                if(((*it).modeloCarro == j) && ((*it).horarioRetirada >= vetUltimaDevolucao.at(j))){
                    // Inserimos essa reserva como resposta pro modelo
                    (vetModelos.at(j)).insert((*it));

                    // Atualizamos o último horário de devolução do modelo
                    vetUltimaDevolucao.at(j) = (*it).horarioDevolucao;
                }

            }
        }

        /*
        O programa deve imprimir uma única linha para cada caso de teste. Em cada linha, para
        cada modelo de carro, deve-se exibir o identificador do modelo seguido de dois pontos,
        a quantidade máxima de clientes que conseguirão alugá-lo sem sobreposição de horários
        de retirada e devolução, seguido de um sinal de igual, e então os identificadores desses
        clientes apresentados em ordem cronológica, separados por vírgula. As informações de
        diferentes modelos devem ser separadas por uma barra vertical (|).
        */

        for(int j = 1; j <= quantModelos; j++){
            cout << j << ": " << vetModelos[j].size();
            if(vetModelos[j].size() > 0) cout << " =";
            
            bool primeiro = true;
            for(set<RESERVA>::iterator it = vetModelos[j].begin(); it != vetModelos[j].end(); it++){
                if(!primeiro) cout << ",";
                cout << " " << (*it).idCliente;
                primeiro = false;
            }
            
            if(j < quantModelos) cout << " | ";
        }

        cout << endl;

        // Limpando variáveis
        quantModelos = 0;
        quantSolicitacoes = 0;
        reserva.idCliente = -1;
        reserva.horarioRetirada = "";
        reserva.horarioDevolucao = "";
        reserva.modeloCarro = -1;
        setReservas.clear();
        vetModelos.clear();
        vetUltimaDevolucao.clear();
        vetModelos.clear();
    }

    return 0;
}